#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0x00 , 0xAA , 0xBB , 0xCC , 0xDE , 0x02 }; // macadresse
int dPinO[] = {13}; //digitale Ausgänge
int dPinI[] = {11}; //digitale Eingänge

int aPinO[] = {}; //analoge Ausgänge (PWM)
int aPinI[] = {}; //analoge Eingänge

int maintain = 30; //checke renew alle x sekunden

// --------------------------------------------------------------------------

int m = 0;
EthernetServer server(80);

bool isIn(int arr[],int needle) {
	for(int i=0;i<sizeof(arr);i++) {
		if(arr[i] == needle) return true;
	}
	return false;
}

int dPin(bool mode,int pin,bool val=false) {
	//return 0 pin = false; 1 pin = true; 2 chance succeded; 3 pin not listed; 4 error
	//mode false getPin; true changePin
	if(mode) {
		if(isIn(dPinO,pin)){
			digitalWrite(pin,val);
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
			return digitalRead(pin);
		}
	}
	return 4;
}

//TODO
int aPin() {
	
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
  
	// IOs definieren
	for(int i = 0;i<sizeof(dPinI);i++) {
		pinMode(dPinI[i],INPUT_PULLUP);
    Serial.print(dPinI[i]);
    Serial.println(" wird als Eingang definiert.");
	}
	for(int i = 0;i<sizeof(dPinO);i++) {
		pinMode(dPinO[i],OUTPUT);
    Serial.print(dPinO[i]);
    Serial.println(" wird als Ausgang definiert.");
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
					client.println(4);
					// content ende
					break;
				}
				if (c == '\n') {
					if(req.substring(0,3) == "GET"){
						int index = req.indexOf("/");
						req = req.substring(index+1);
						index = req.indexOf("/");
            int index2 = req.indexOf(" ");
						if(index < index2) {
							int pin = req.substring(0,index).toInt();
							req = req.substring(index);
              Serial.println(req);
							index = req.indexOf(" ");
							if(index >= 0) {
                Serial.print("ind: ");
                Serial.println(index);
								int val = req.substring(1,index).toInt();
                Serial.print("Val: ");
                Serial.println(val);
								client.println(dPin(true,pin,val));
							}else{
								client.println(dPin(false,pin));
							}
						}else{
							int pin = req.substring(0,index2).toInt();
							client.println(dPin(false,pin));
						}
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
