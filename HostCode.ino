#include <ArduinoJson.h>
#include <Wire.h>

// Protocol Management Data 
enum {Host, Master,Slave0,Slave1};
uint8_t addresses [4] = {10, 20, 30, 40}; 
enum {Header,CommandType,CommandArg1,CommandArg2,Checksum1,Checksum2};
enum {oneTime1Req, oneTime1Res, oneTime2Req, oneTime2Res};
#define unused 0xEE
const int protocolLength = 6; 
byte messageIn[protocolLength],messageOut[protocolLength];;
byte cmdType, cmdArg1, cmdArg2, cs1, cs2, receiverNumber;
int receivedByte;
bool requestOneTime1Made = false;
bool requestOneTime2Made = false;

enum {GetControls, RequestOneTime1, UpdateOneTime1, RequestOneTime2, UpdateOneTime2};
int current = GetControls;



// Communications Details 
String ssid       = "Open-Acess"; 
String password   = ""; 

void setup() {

  Wire.begin(23,22);
  Wire.setClock(10000);
  Serial.begin(115200);
  
  delay(4000);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}

String extract(String fromResponse, String extractWhat, int digits, int occurence){
  
  int index = fromResponse.indexOf(extractWhat, fromResponse.indexOf(extractWhat)*(occurence-1) + 1);
  int from  = index+extractWhat.length()+3; 
  int to = from + 2 + digits;  
  return fromResponse.substring(from+1,to-1);
                 
}

void loop() {

  switch(current){

  case GetControls:
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin("https://firestore.googleapis.com/v1/projects/cenproject450/databases/(default)/documents/controls/turnoff"); //Specify the URL
    int httpCode = http.GET();                                      
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
        int turnOffState = extract(payload,"stringValue",1,1);
        Serial.println(id.toInt());
      }
 
    else {
      Serial.println("Error on GET HTTP request");
    }
 
    http.end(); //Free the resources
  }
 
    if(turnOffState == 1){
      delay(500);
    }

    else 
      current = RequestOneTime1;

      break;

      case RequestOneTime1:
      if(!requestOneTime1Made)
        {
          cmdType = oneTime1Req;
          cmdArg1 = unused;
          cmdArg2 = unused; 
          buildI2cProtocolMessage();
          sendI2cProtocolMessage();
          
        }
      if(Serial.available > 0){
        requestOneTime1Made = false;
        current = updateOneTime1;
      }
    break;
    
    case UpdateOneTime1:
    
   int distance = cmdArg1*256ul+cmdArg2;;

  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;   


   http.begin("https://firestore.googleapis.com/v1/projects/blindspotaduezz/databases/(default)/documents/monitoring/leftSensor");  //Specify destination for HTTP request

   http.addHeader("Content-Type", "text/plain"); //Specify content-type header

   String x = String("{\n\"fields\": {\n \"distance\": {\n \"stringValue\": \" ") + distance +  "\"\n }\n }\n}\n";
 
   int httpResponseCode = http.PATCH(x);   //Send the actual POST request
 
   if(httpResponseCode>0){
    String response = http.getString();                       //Get the response to the request
 
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
 
   }else{
 
    Serial.print("Error on sending PATCH: ");
    Serial.println(httpResponseCode);
 
   }
 
   http.end();  //Free resources
 
 }

  }

  else{
    Serial.println("not recieving");
  }

  Serial.flush();
    current = RequestOneTime2;
    break;
    
    
    case RequestOneTime2:
       if(!requestOneTime2Made)
        {
          cmdType = oneTim21Req;
          cmdArg1 = unused;
          cmdArg2 = unused; 
          buildI2cProtocolMessage();
          sendI2cProtocolMessage();
          
        }
      if(Serial.available > 0){
        requestOneTime2Made = false;
        current = updateOneTime2;
      }
    break;
    
    case UpdateOneTime2:
           int distance = cmdArg1*256ul+cmdArg2;;

  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;   


   http.begin("https://firestore.googleapis.com/v1/projects/blindspotaduezz/databases/(default)/documents/monitoring/rightSensor");  //Specify destination for HTTP request

   http.addHeader("Content-Type", "text/plain"); //Specify content-type header

   String x = String("{\n\"fields\": {\n \"distance\": {\n \"stringValue\": \" ") + distance +  "\"\n }\n }\n}\n";
 
   int httpResponseCode = http.PATCH(x);   //Send the actual POST request
 
   if(httpResponseCode>0){
    String response = http.getString();                       //Get the response to the request
 
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
 
   }else{
 
    Serial.print("Error on sending PATCH: ");
    Serial.println(httpResponseCode);
 
   }
 
   http.end();  //Free resources
 
 }

  }

  else{
    Serial.println("not recieving");
  }

  Serial.flush();
    current = getControls;
    break;
 
  }
 
}


void buildI2cProtocolMessage(){
    messageOut[Header] = 0x7E;
    messageOut[CommandType] = cmdType;
    messageOut[CommandArg1] = cmdArg1;
    messageOut[CommandArg2] = cmdArg2;
    int cs = calcChecksum(); 
  messageOut[Checksum1] = (cs>>8);
    messageOut[Checksum2] =  cs & 0xFF;
}
  
void sendI2cProtocolMessage(){
  
  Wire.beginTransmission(addresses[Master]); 
  Wire.write(messageOut,protocolLength); 
  Wire.endTransmission(); 
}

int calcChecksum()
{
   return ((int)cmdType) + cmdArg1 + cmdArg2;
  
}
