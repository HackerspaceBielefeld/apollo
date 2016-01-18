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

void setup() {
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
	delay(1000);
}
