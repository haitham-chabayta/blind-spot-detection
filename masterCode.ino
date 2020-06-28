#include <Wire.h>
#define unused 0xEE

enum {Header,CommandType,CommandArg1,CommandArg2,Checksum1,Checksum2};
enum {oneTime1Req,oneTime1Res,oneTime2Req,oneTime2Res};

enum {Master,Slave0,Slave1};
uint8_t addresses [3] = {20,30,40}; 

const int protocolLength = 6; 

byte messageIn[protocolLength],messageOut[protocolLength];
byte cmdType, cmdArg1, cmdArg2, cs1, cs2; 
bool newMsg = false;

enum {Idle, WaitForHost, ValidateMessage, DetermineReceiver, RelayHostCommand,ActOnSlaveMessage};
int current = Idle; 


void setup()
{
  Serial.begin(115200); 
  Wire.begin(20); 
  Wire.onReceive(receiveEvent);
  Wire.setClock(10000);
  
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
        newMsg = true; 
         
    }
    
}
void loop()
{
  switch(current)
  {
    case Idle:
      delay(100);
      current = WaitForHost;
  break;

    case WaitForHost:
      if(newMsg) 
      {
        newMsg = false;
        current = ValidateMessage; 
      }
    break;
    case ValidateMessage:
      if(checksum())
      {
    decodeProtocolMessage();
        current = DetermineReceiver;    
      }
      else
      {
        Serial.println("Invalid Message Received"); 
        current = Idle;
         
      }
    break;
    
    //------------------
    
    
    case DetermineReceiver:
      switch(cmdType)
      {
          case oneTime1Req:
            receiverNumber = Slave0;
            current = ActOnSlaveMessage;
          break;
          case oneTime2Req:
            receiverNumber = Slave1;
            current = ActOnSlaveMessage;
          break;
          case oneTime1Res:
          case oneTime2Res:
            receiverNumber = Host;
            current = ActOnSlaveMessage;
          break;
      }
      
      
    break;

    
    case RelayHostCommand:
      buildProtocolMessage();
      sendProtocolMessage();
      delay(500);
      current = Idle; 
    break;
    

    
    case ActOnSlaveMessage:
      buildProtocolMessage();
      sendUsartProtocolMessage();
      delay(500);
      current = Idle; 
    break;
    
    //------------------
    
    
  } 
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

void printMessageOut()
{
  Serial.println("__________________________________");
  for (int i = 0 ; i < protocolLength; i++)
  {
    
    Serial.print("master out: "); 
    Serial.println((int)messageOut[i]);
  }
  Serial.flush(); 
}

void printMessageIn()
{
  Serial.println("__________________________________");
  for (int i = 0 ; i < protocolLength; i++)
  {
    
    Serial.print("master in: "); 
    Serial.println((int)messageIn[i]);
  }
  Serial.flush(); 
}


void sendProtocolMessage(){
  
    printMessageOut();
  Wire.beginTransmission(addresses[receiverNumber]); 
  Wire.write(messageOut,protocolLength); 
  Wire.endTransmission(); 
}

void sendUsartProtocolMessage(){
  printMessageOut();
  for (int i = 0 ; i < protocolLength; i++)
  Serial.write(messageOut[i]); 
}

void decodeProtocolMessage()
{
  cmdType = messageIn[CommandType];
  cmdArg1 = messageIn[CommandArg1];
  cmdArg2 = messageIn[CommandArg2];
  cs1 = messageIn[Checksum1];
  cs2 = messageIn[Checksum2];
}
int calcChecksum()
{
   return ((int)cmdType) + cmdArg1 + cmdArg2;
  
}
bool checksum()
{
  
  int checksum = messageIn[Checksum1]; 
  checksum  = (checksum<<8) + messageIn[Checksum2]; 
  int recalchecksum = (int)  messageIn[CommandType]
                +messageIn[CommandArg1]
                +messageIn[CommandArg2];
  return recalchecksum == checksum;
}
