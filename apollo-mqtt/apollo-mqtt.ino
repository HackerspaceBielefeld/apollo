#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <PubSubClient.h>

byte mac[] = { 0x00 , 0x00 , 0x00 , 0x82 , 0xB1 , 0x73 }; // macadresse

int maintain = 30; //checke renew alle x sekunden

char server[] = "172.23.45.5";

String devName = "apollo";
char* topicDebug = "debug/apollo";
int topicCount = 1;
char* topicInput[] = {"apollo/?"};



// --------------------------------------------------------------------------

int m = 0;

Adafruit_MCP23017 mcp; //port extender
EthernetClient ethClient;
PubSubClient mqtt;

void callback(char* topic, byte* pl, unsigned int length) {
	char payload[length];
	for (int i=0;i<length;i++) {
    payload[i] = (char)pl[i];  
	}
  Serial.print(payload);

  if(topic == "apollo/0") {
    if(payload == "ON") {
      mcp.digitalWrite(0, HIGH);
    }else{
      mcp.digitalWrite(0, LOW);
    }
  }

  if(topic == "apollo/1") {
    if(payload == "ON") {
      mcp.digitalWrite(1, HIGH);
    }else{
      mcp.digitalWrite(1, LOW);
    }
  }

  if(topic == "apollo/2") {
    if(payload == "ON") {
      mcp.digitalWrite(2, HIGH);
    }else{
      mcp.digitalWrite(2, LOW);
    }
  }

  if(topic == "apollo/3") {
    if(payload == "ON") {
      mcp.digitalWrite(3, HIGH);
    }else{
      mcp.digitalWrite(3, LOW);
    }
  }

  if(topic == "apollo/4") {
    if(payload == "ON") {
      mcp.digitalWrite(4, HIGH);
    }else{
      mcp.digitalWrite(4, LOW);
    }
  }

  if(topic == "apollo/5") {
    if(payload == "ON") {
      mcp.digitalWrite(5, HIGH);
    }else{
      mcp.digitalWrite(5, LOW);
    }
  }

  if(topic == "apollo/6") {
    if(payload == "ON") {
      mcp.digitalWrite(6, HIGH);
    }else{
      mcp.digitalWrite(6, LOW);
    }
  }

  if(topic == "apollo/7") {
    if(payload == "ON") {
      mcp.digitalWrite(7, HIGH);
    }else{
      mcp.digitalWrite(7, LOW);
    }
  }

  if(topic == "apollo/8") {
    if(payload == "ON") {
      mcp.digitalWrite(8, HIGH);
    }else{
      mcp.digitalWrite(8, LOW);
    }
  }

  if(topic == "apollo/9") {
    if(payload == "ON") {
      mcp.digitalWrite(9, HIGH);
    }else{
      mcp.digitalWrite(9, LOW);
    }
  }

  if(topic == "apollo/10") {
    if(payload == "ON") {
      mcp.digitalWrite(10, HIGH);
    }else{
      mcp.digitalWrite(10, LOW);
    }
  }

  if(topic == "apollo/11") {
    if(payload == "ON") {
      mcp.digitalWrite(11, HIGH);
    }else{
      mcp.digitalWrite(11, LOW);
    }
  }

  if(topic == "apollo/12") {
    if(payload == "ON") {
      mcp.digitalWrite(12, HIGH);
    }else{
      mcp.digitalWrite(12, LOW);
    }
  }

  if(topic == "apollo/13") {
    if(payload == "ON") {
      mcp.digitalWrite(13, HIGH);
    }else{
      mcp.digitalWrite(13, LOW);
    }
  }

  if(topic == "apollo/14") {
    if(payload == "ON") {
      mcp.digitalWrite(14, HIGH);
    }else{
      mcp.digitalWrite(14, LOW);
    }
  }

  if(topic == "apollo/15") {
    if(payload == "ON") {
      mcp.digitalWrite(15, HIGH);
    }else{
      mcp.digitalWrite(15, LOW);
    }
  }
  
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	
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
	
	mqtt.publish(topicDebug,ip);
	Serial.println("");
}


//verbindet mqtt neu zum broker
//ungetestet
void reconnect() {
	while (!mqtt.connected()) {
		Serial.print("Attempting MQTT connection...");
		if (mqtt.connect("arduinoClient")) {
			Serial.println("connected");
			mqtt.publish(topicDebug,"reconnected");
      for(int i=0; i<topicCount; i++) {
        mqtt.subscribe(topicInput[i]);
      }
		} else {
			Serial.print("failed, rc=");
			Serial.print(mqtt.state());
			Serial.println(" try again in 5 seconds");
			//mqtt.publish(topicDebug,"connection lost");
			delay(5000);
		}
	}
}

void setup() {
	Serial.begin(9600); // Serial starten
	while (!Serial) {
		;
	}
	Serial.println("Apollo start ...");
	
	mqtt.setClient(ethClient);
  mqtt.setServer(server, 1883); //mqtt starten
	mqtt.setCallback(callback);
	delay(1500);

	mcp.begin(); // port extender starten
  mcp.pinMode(0, OUTPUT);
  mcp.pinMode(1, OUTPUT);
  mcp.pinMode(2, OUTPUT);
  mcp.pinMode(3, OUTPUT);
  mcp.pinMode(4, OUTPUT);
  mcp.pinMode(5, OUTPUT);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(7, OUTPUT);
  mcp.pinMode(8, OUTPUT);
  mcp.pinMode(9, OUTPUT);
  mcp.pinMode(10, OUTPUT);
  mcp.pinMode(11, OUTPUT);
  mcp.pinMode(12, OUTPUT);
  mcp.pinMode(13, OUTPUT);
  mcp.pinMode(14, OUTPUT);
  mcp.pinMode(15, OUTPUT);

	// dhcp holen
	Serial.println("DHCP anfrage.");
	while(Ethernet.begin(mac) == 0) {
		delay(1000);
	}
	printIPAddress();
}

void loop() {
	if(maintain > m) {
		m++;
	}else{
		// renew falls nötig
		Ethernet.maintain();
		m = 0;
	}

	if (!mqtt.connected()) {
		reconnect();
	}
	mqtt.loop();
}
