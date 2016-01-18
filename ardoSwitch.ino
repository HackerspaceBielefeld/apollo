#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0x00 , 0xAA , 0xBB , 0xCC , 0xDE , 0x02 }; // macadresse

int maintain = 30; //checke renew alle x sekunden

int m = 0;
EthernetClient client;

void setup() {
	// dhcp holen
	while(Ethernet.begin(mac) == 0) {
		delay(1000);
	}
}

void loop() {
	if(maintain > m) {
		m++;
	}else{
		// renew falls nötig
		Ethernet.maintain();
		m = 0;
	}
	
	
  
	// etwas bremsen
	delay(1000);
}
