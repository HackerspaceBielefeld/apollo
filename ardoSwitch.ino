#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0x00 , 0xAA , 0xBB , 0xCC , 0xDE , 0x02 }; // macadresse
int dPinO[] = {} //digitale Ausgänge
int dPinI[] = {} //digitale Eingänge

int aPinO[] = {} //analoge Ausgänge (PWM)
int aPinI[] = {} //analoge Eingänge

int maintain = 30; //checke renew alle x sekunden

// --------------------------------------------------------------------------

int m = 0;
EthernetServer server(80);

bool isIn(arr,needle) {
	for(int i=0;i<sizeof(arr);i++) {
		if(arr[i] == needle) return true;
	}
	return false;
}

int dPin(mode,pin,val=false) {
	//return 0 pin = false; 1 pin = true; 2 chance succeded; 3 pin not listed; 4 error
	//mode false getPin; true changePin
	if(mode) {
		if(isIn(dPinO,pin)){
			//TODO
			if(digitalWrite(pin,val)) {
				return 2;
			}else{
				return 4;
			}
		}else{
			return 3;
		}
	}else{
		if(isIn(dPinI,pin) || isIN(dPinO,pin)) {
			return digitalRead(pin);
		}else{
			return 4;
		}
	}
	
}

//TODO
int aPin() {
	
}

void setup() {
	// IOs definieren
	for(int i = 0;i<sizeof(dPinI):i++) {
		pinMode(dPinI[i],INPUT_PULLUP);
	}
	for(int i = 0;i<sizeof(dPinO):i++) {
		pinMode(dPinO[i],OUTPUT);
	}
	
	// dhcp holen
	while(Ethernet.begin(mac) == 0) {
		delay(1000);
	}
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
		boolean currentLineIsBlank = true;
		while (client.connected()) {
			if (client.available()) {
				char c = client.read();
				//TODO verstehen wie ich get var oder path lese
				if (c == '\n' && currentLineIsBlank) {
					// standard antwort header
					client.println("HTTP/1.1 200 OK");
					client.println("Content-Type: text/html");
					client.println("Connection: close");
					client.println();
					// content
					int pin = ; //pin wird aus c errechnet
					int val = ; //value die dem pin gegeben werden soll
					//TODO hier kommt die daten verarbeitung hin
					// wert vorhanden dann ändere status und gib neuen status aus
					// wert nicht vorhanden nur status angeben
					if(true) { //TODO dv kontrollieren
						// wert gändert
						client.println("OK");
					}else{
						// wert nicht geändert, weil wert zb gleich
						client.println("FAIL");
					}
					
					// content ende
					client.println();
					break;
				}
				if (c == '\n') {
					// you're starting a new line
					currentLineIsBlank = true;
				} else if (c != '\r') {
					// you've gotten a character on the current line
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
