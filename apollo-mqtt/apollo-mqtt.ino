#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include <PubSubClient.h>

byte mac[] = { 0x00 , 0x00 , 0x00 , 0x82 , 0xB1 , 0x73 }; // macadresse

int maintain = 30; //checke renew alle x sekunden
String devName = "apollo";
String topicDebug "debug/apollo";

// --------------------------------------------------------------------------

int m = 0;
Adafruit_MCP23017 mcp; //port extender

EthernetClient ethClient;
PubSubClient client(ethClient);

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

void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i=0;i<length;i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();
}

//versendet ip adresse per uart und mqtt
//ungetestet
void printIPAddress() {
	Serial.print("IP: ");
	for (byte thisByte = 0; thisByte < 4; thisByte++) {
		// print the value of each byte of the IP address:
		
		Serial.print(Ethernet.localIP()[thisByte], DEC);
		Serial.print(".");
	}
	
	char ip[15];
	strcpy(ip,(int)Ethernet.localIP()[0]);
	strcat(ip,".");
	strcpy(ip,(int)Ethernet.localIP()[1]);
	strcat(ip,".");
	strcpy(ip,(int)Ethernet.localIP()[2]);
	strcat(ip,".");
	strcpy(ip,(int)Ethernet.localIP()[3]);
	
	client.publish(topicDebug,ip)
	Serial.println("");
}

void reconnect() {
	// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (client.connect("arduinoClient")) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			client.publish("outTopic","hello world");
			// ... and resubscribe
			client.subscribe("inTopic");
		} else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void setup() {
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
	Serial.println("Apollo start ...");
	
	client.setServer(server, 1883);
	client.setCallback(callback);
	delay(1500);

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
}