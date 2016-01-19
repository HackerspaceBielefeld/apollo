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
			if(digitalWrite(pin,val)) {
				return 2;
			}
		}else{
			return 3;
		}
	}else{
		if(isIn(dPinI,pin) || isIN(dPinO,pin)) {
			return digitalRead(pin);
		}
	}
	return 4;
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
		String req = "";
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
					client.println(4);
					// content ende
					break;
				}
				if (c == '\n') {
					// TODO hier zeile analysieren
					if(req.startwith("GET")){
						int index = req.indexOf("/");
						req = req.substring(index);
						index = req.indexOf("/");
						if(index >= 0) {
							pin = isInt(req.substring(0,index));
							req = req.substring(index);
							index = req.indexOf(" ");
							if(index >= 0) {
								val = req.substring(0,index);
								client.println(dPin(true,pin,val));
							}else{
								client.println(dPin(false,pin));
							}
						}else{
							index = req.indexOf(" ");
							pin = toInt(req.substring(0,index));
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
