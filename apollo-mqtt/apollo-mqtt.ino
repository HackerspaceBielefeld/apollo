#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <PubSubClient.h>
#include <VirtualWire.h>
#include <string.h>

byte mac[] = { 0x00 , 0x00 , 0x00 , 0x82 , 0xB1 , 0x73 }; // macadresse

int maintain = 30; //checke renew alle x sekunden

char server[] = "172.23.45.5";

String devName = "apollo";
char* topicDebug = "debug/apollo";
int topicCount = 1;
char* topicInput[] = {"apollo/?"};

int pin446 = 11;




// --------------------------------------------------------------------------

int m = 0;

Adafruit_MCP23017 mcp; //port extender
EthernetClient ethClient;
PubSubClient mqtt;

void callback(char* topic, byte* pl, unsigned int length) {
	char payload[length];
  uint8_t id = 0;
	for (int i=0;i<length;i++) {
		payload[i] = (char)pl[i];  
	}
	payload[length] ='\0';
	Serial.print(payload);
  
	if(topic == "apollo/funk") {
		vWireSendStr(payload,length);
	}

 if(topic == "apollo/0") {
    id = 0;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/1") {
    id = 1;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/2") {
    id = 2;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/3") {
    id = 3;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/4") {
    id = 4;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/5") {
    id = 5;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/6") {
    id = 6;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/7") {
    id = 7;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/8") {
    id = 8;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/9") {
    id = 9;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/10") {
    id = 10;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/11") {
    id = 11;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/12") {
    id = 12;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/13") {
    id = 13;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/14") {
    id = 14;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
    }
  }

 if(topic == "apollo/15") {
    id = 15;
    if(payload == "TOGGLE") {
      if(mcp.digitalRead(id) == HIGH) {
        mcp.digitalWrite(id,LOW);
      }else{
        mcp.digitalWrite(id,HIGH);
      }
    }else if(payload == "ON") {
      mcp.digitalWrite(id, HIGH);
    }else{
      mcp.digitalWrite(id, LOW);
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

void vWireInit() {
    vw_set_tx_pin(transmit_pin);
    vw_setup(2000);       // Bits per sec
}

void vWireSendStr(char* msg,int length) {
	vw_send((uint8_t *)msg, length);
	vw_wait_tx(); // Wait until the whole message is gone
	delay(1000)
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
	
	vWireInit();
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
