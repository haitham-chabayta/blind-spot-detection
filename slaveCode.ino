#include <Wire.h>
#define unused 0xEE
#define trigger 13
#define echo 11
enum {Header,CommandType,CommandArg1,CommandArg2,Checksum1,Checksum2};
enum { oneTime1Req,oneTime1Res,oneTime2Req,oneTime2Res};
enum {Idle, Recieving, Decoding, Validating, ReportingError, Executing, Replying};
int current = Idle; 

enum {Master,Slave0,Slave1};
uint8_t addresses [3] = {20,30,40}; 

const int protocolLength = 6; 

byte messageIn[protocolLength],messageOut[protocolLength];
byte cmdType, cmdArg1, cmdArg2, cs1, cs2; 


void setup()
{
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  Wire.begin(40);
  Wire.onReceive(receiveEvent); 
  Serial.begin(115200); 
  Wire.setClock(10000);
}

float calculateDistance()
{
   digitalWrite(trigger, LOW);
   delayMicroseconds(2);
   digitalWrite(trigger, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigger, LOW);
   float duration = pulseIn(echo, HIGH);
   float distanceCal= duration*0.034/2;
   return distanceCal;
 }


void buildProtocolMessage()
{
    messageOut[Header] = 0x7E;
    messageOut[CommandType] = cmdType;
    messageOut[CommandArg1] = cmdArg1;
    messageOut[CommandArg2] = cmdArg2;
    int cs = calcChecksum(); 
  messageOut[Checksum1] = (cs>>8);
    messageOut[Checksum2] =  cs & 0xFF;
}




void sendProtocolMessage(){
  printMessageOut();
  Wire.beginTransmission(addresses[Master]); 
  Wire.write(messageOut,protocolLength); 
  Wire.endTransmission(); 
}


void receiveEvent(int howMany)
{
  if(Wire.available()>0)
    {

        messageIn[Header] = Wire.read(); 
        messageIn[CommandType] = Wire.read();
        messageIn[CommandArg1] = Wire.read();
        messageIn[CommandArg2] = Wire.read();
        messageIn[Checksum1] = Wire.read();
        messageIn[Checksum2] = Wire.read();
        printMessageIn();
        current = Validating;
         
    }
    
}
    
void loop()
{
  switch(current)
  {
    case Idle: 
    delay(100);
    current = Recieving;
    break;
    
    case Recieving:
    break; 
    
    case Decoding:
    decodeProtocolMessage();
    current = Executing;
    break;
    
    
    case Validating:
      if(checksum())
          current = Decoding;  
      else
          current = ReportingError;
    break;
     
    case ReportingError:
    Serial.print("Error: Message Invalid"); 
    current = Idle; 
    break; 
    
    case Executing:
      int distance = calculateDistance();
      cmdType = overTime1Res;
      cmdArg1 = distance>>8;
      cmdArg2 = distance;
      current = Replying;
    break;
      
    case Replying:
      buildProtocolMessage();
      sendProtocolMessage();
      delay(500);
      current = Idle;
    break;
 
    
  }
}

int calcChecksum()
{
   return ((int)cmdType) + cmdArg1 + cmdArg2;
  
}

void printMessageOut()
{
  Serial.println("__________________________________");
  for (int i = 0 ; i < protocolLength; i++)
  {
    
    Serial.print("slave out: "); 
    Serial.println((int)messageOut[i]);
  }
  Serial.flush(); 
}

void printMessageIn()
{
  Serial.println("__________________________________");
  for (int i = 0 ; i < protocolLength; i++)
  {
    
    Serial.print("slave in: "); 
    Serial.println((int)messageIn[i]);
  }
  Serial.flush(); 
}

void decodeProtocolMessage()
{
    cmdType = messageIn[CommandType];
    cmdArg1 = messageIn[CommandArg1];
    cmdArg2 = messageIn[CommandArg2];
    cs1 = messageIn[Checksum1];
    cs2 = messageIn[Checksum2];    

  
}
bool checksum()
{
  
  int checksum = messageIn[Checksum1]; 
  checksum  = (checksum<<8) + messageIn[Checksum2]; 
  int recalchecksum = (int)messageIn[CommandType]+messageIn[CommandArg1]+messageIn[CommandArg2];
  return recalchecksum == checksum;
}
