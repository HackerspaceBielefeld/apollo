#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"

byte mac[] = { 0x00 , 0x00 , 0x00 , 0x82 , 0xB1 , 0x73 }; // macadresse

Adafruit_MCP23017 mcp;
int maintain = 30; //checke renew alle x sekunden
uint8_t pinsO[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; // pin adressen
uint8_t statO[] = {0,0,0,0,0,0,0,0,0,0,0 ,0 ,0 ,0 ,0 ,0 }; //start zustand

// --------------------------------------------------------------------------

int m = 0;
EthernetServer server(80);

bool isIn(int arr[],int needle) {
  for(int i=0;i<sizeof(arr);i++) {
    if(arr[i] == needle) return true;
  }
  return false;
}

int dPin(bool mode,int pin,int val=false) {
  //return 0 pin = false; 1 pin = true; 2 chance succeded; 3 pin not listed; 4 error
  //mode false getPin; true changePin
  if(mode) {
    if(isIn(dPinO,pin)){
      mcp.digitalWrite(pin,val);
      Serial.print(pin);
      Serial.print(" auf ");
      Serial.print(val);
      Serial.println(" schalten.");
      return 2;
    }else{
      Serial.print(pin);
      Serial.println(" Nicht in der Liste.");
      return 3;
    }
  }else{
    if(isIn(dPinI,pin) || isIn(dPinO,pin)) {
      Serial.print(pin);
      Serial.println(" wird abgefragt.");
      return mcp.digitalRead(pin);
    }
  }
  return 4;
}

void printIPAddress() {
  Serial.print("IP: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println("");
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Apollo start ...");

  mcp.begin();
  
  for(int j = 0;j<sizeof(pinsO);j++) {
    mcp.pinMode(pins[j],OUTPUT);
    mcp.digitalWrite(pinO[j],statO[j]);
    Serial.print(pinsO[j]);
    Serial.print(" wird als Ausgang ");
    Serial.print(statO[j]);
    Serial.println(" definiert.");
  }
  
  // dhcp holen
 
  Serial.println("DHCP anfrage.");
  while(Ethernet.begin(mac) == 0) {
    delay(1000);
  }
  printIPAddress();
  // server starten
  server.begin();
}

void loop() {
  if(maintain > m) {
    m++;
  }else{
    // renew falls nötig
    Ethernet.maintain();
    m = 0;
  }

  // auf anfrage Prüfen
  EthernetClient client = server.available();

  if (client) {
    String req = "";
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n' && currentLineIsBlank) {
          // standard antwort header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          // content
          client.print(4);
          // content ende
          break;
        }
        if (c == '\n') {
          if(req.substring(0,3).compareTo("GET") == 0){
            int index = req.indexOf("/");
            int index2;
            int pin;
            int val;
            req = req.substring(index+1);
            index = req.indexOf("/");
            index2 = req.indexOf(" ");

            if(index < index2) {
              // kanal ändern
              //Serial.println(req.substring(0,index));
              pin = req.substring(0,index).toInt();
              if(isIn(dPinO,pin)) { 
                client.println(3);
                break;
                // nicht listed
              }
              req = req.substring(index+1);
              index = req.indexOf("/");
              index2 = req.indexOf(" ");
              if(index > index2) {
                index = index2;
              }
              //Serial.print("Index: ");
              //Serial.println(index);
              //Serial.println(req);
              //Serial.println(req.substring(0,index));
              val = req.substring(0,index).toInt();
              
              if(val == 0) {
                // ausschalten
                digitalWrite(pin,LOW);
                client.println(2);
                Serial.print(pin);
                Serial.println(" schaltet LOW.");
                break; 
              }else if(val == 1) {
                // einschalten
                digitalWrite(pin,HIGH);
                client.println(2);
                Serial.print(pin);
                Serial.println(" schaltet HIGH.");
                break;
              }else if(val == 2) {
                // toggle 
                int tmp = digitalRead(pin);
                if(tmp == HIGH) {
                  digitalWrite(pin,LOW);
                  client.println(2);
                  Serial.print(pin);
                  Serial.println(" toggelt LOW.");
                }else{
                  digitalWrite(pin,HIGH);
                  client.println(2);
                  Serial.print(pin);
                  Serial.println(" toggelt HIGH.");
                }
              }else if(val > 99 && val <=1000) {
                // 0.2sek toggle
                int tmp = digitalRead(pin);
                if(tmp == HIGH) {
                  digitalWrite(pin,LOW);
                  delay(val);
                  digitalWrite(pin,HIGH);
                  client.println(2);
                  Serial.print(pin);
                  Serial.println(" toggelt LOW.");
                }else{
                  digitalWrite(pin,HIGH);
                  delay(val);
                  digitalWrite(pin,LOW);
                  client.println(2);
                  Serial.print(pin);
                  Serial.println(" toggelt HIGH.");
                }
              }else{
                client.println(4);
                Serial.print(val);
                Serial.println(" ist ungültig");
                break; 
              }
              
            }else{
              // kanal auslesen
              if(isIn(dPinO,pin)) { 
                client.println(3);
                break;
                // nicht listed
              }
              pin = req.substring(0,index2).toInt();
              if(digitalRead(pin) == HIGH) {
                client.println(1);
                Serial.print(pin);
                Serial.println(" gelesen als HIGH.");
              }else{
                client.println(0);
                Serial.print(pin);
                Serial.println(" gelesen als LOW.");
              
              }
            }
            Serial.print("Pin: ");
            Serial.println(pin);
            Serial.print("Val: ");
            Serial.println(val);
            
            break;
          }
          req = "";
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // buchstabe sammeln
          req.concat(c);
          currentLineIsBlank = false;
        }
      }
    }

    delay(1);
    // close the connection:
    client.stop();
  }

  // etwas bremsen
  delay(999);
}
