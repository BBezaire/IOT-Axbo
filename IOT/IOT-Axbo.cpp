/*
 Copyright (C) 2016 Brandon Bezaire
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 
 Code graciously borrowed from the Channel scanner example 
 
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>
 03/17/2013 : Charles-Henri Hallard (http://hallard.me)
 
 */

/**
 * IOT Axbo
 *
 * Listens for Axbo wristband signals
 * Runs system command if button is pressed
 * 
 * Still a WIP
 * 
 * 
 */

#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <RF24/RF24.h>

using namespace std;

//
// Hardware configuration
//

// CE Pin, CSN Pin, SPI Speed

// Setup for GPIO 22 CE and GPIO 25 CSN with SPI Speed @ 1Mhz
//RF24 radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_18, BCM2835_SPI_SPEED_1MHZ);

// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 4Mhz
//RF24 radio(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_4MHZ); 

// Setup for GPIO 22 CE and CE1 CSN with SPI Speed @ 8Mhz
RF24 radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_1MHZ);  

//RF24 radio(22,0);

//
// Channel info
//
const uint8_t num_channels = 126;
uint8_t values[num_channels];


const int num_reps = 100;
int reset_array=0;


int main(int argc, char** argv)
{
  //
  // Print preamble
  //

  //Serial.begin(115200);
  //printf_begin();
  printf("RF24/examples/scanner/\n");

  //
  // Setup and configure rf radio
  //
  uint8_t len;
  len = 4;
  uint64_t address = 0xBBBBBBBBBB;
  
  radio.begin();
//  radio.powerDown();
 // radio.powerUp();	
  radio.setAutoAck(false);
  radio.setAddressWidth(0);
  radio.setPayloadSize(4);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(49);
  
  radio.openReadingPipe(0,address);

  // Get into standby mode
  radio.startListening();
  radio.stopListening();

  radio.startListening();
  radio.printDetails();
  //write_register(EN_RXADDR,0x01);
  char receivePayload[4];
  while(1)
  {
	
	  
	radio.startListening();
	usleep(1000);
			
	//radio.stopListening();
	while (radio.available()) {
	radio.read( receivePayload, len );
	
	
printf("Recv: size=%i payload=%x",len,receivePayload[0]);
printf("\n");
if (receivePayload[0] == 0x44){
	printf("Button Pressed \n");
	//Needs a config file
	system("curl http://192.168.1.102:8083/ZAutomation/api/v1/devices/ZWayVDev_zway_2-0-37/command/on");
}
	//for (int i = 0; i < 4; i++) {
		//printf("0x%x ", receivePayload[i]);
	//}
	//printf("\n");
	}
		
  }

}
  

// vim:ai:cin:sts=2 sw=2 ft=cpp
