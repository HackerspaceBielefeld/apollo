#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0x00 , 0xAA , 0xBB , 0xCC , 0xDE , 0x02 }; // macadresse

int maintain = 30; //checke renew alle x sekunden

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
		//TODO
		// an http request ends with a blank line
		boolean currentLineIsBlank = true;
		while (client.connected()) {
			if (client.available()) {
				char c = client.read();
				Serial.write(c);
				// if you've gotten to the end of the line (received a newline
				// character) and the line is blank, the http request has ended,
				// so you can send a reply
				if (c == '\n' && currentLineIsBlank) {
					// send a standard http response header
					client.println("HTTP/1.1 200 OK");
					client.println("Content-Type: text/html");
					client.println("Connection: close");  // the connection will be closed after completion of the response
					client.println("Refresh: 5");  // refresh the page automatically every 5 sec
					client.println();
					client.println("<!DOCTYPE HTML>");
					client.println("<html>");
					// output the value of each analog input pin
					for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
						int sensorReading = analogRead(analogChannel);
						client.print("analog input ");
						client.print(analogChannel);
						client.print(" is ");
						client.print(sensorReading);
						client.println("<br />");
					}
					client.println("</html>");
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
	// TODO End

	// etwas bremsen
	delay(1000);
}
