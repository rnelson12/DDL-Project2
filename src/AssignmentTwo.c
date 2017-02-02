/*
===============================================================================
 Name        : assignment2.c
 Author      : $Fleagle, Nelson
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here
#define FIO0DIR (*(volatile unsigned int *)0x2009c000)
#define FIO1DIR (*(volatile unsigned int *)0x2009c020)
#define FIO2DIR (*(volatile unsigned int *)0x2009c040)
#define FIO0PIN (*(volatile unsigned int *)0x2009c014)
#define FIO1PIN (*(volatile unsigned int *)0x2009c034)
#define FIO2PIN (*(volatile unsigned int *)0x2009c054)
#define PINMODE0 (*(volatile unsigned int *)0x4002c040)
#define PINMODE1 (*(volatile unsigned int *)0x4002c044)
#define PINMODE2 (*(volatile unsigned int *)0x4002c048)

int numRedLEDsOn = 7;
int numGreenLEDsOn = 5;
int numBlueLEDsOn = 3;


void Setup();
void input_setup();
void AllOn();
void AllOff();
void reset();

void BluePressed();
void GreenPressed();
void RedPressed();
void p1_switch_pressed();
void p2_switch_pressed();

void p1_red();
void p1_blue();
void p1_green();
void p2_red();
void p2_blue();
void p2_green();

void disable_blue();
void disable_green();
void disable_red();

void wait_ticks(int count);
void wait(float count);


int main(void) {

	Setup();
	input_setup();
	AllOff();
	AllOn();
    while(1) {
/*    	AllOn();
    	wait_ticks(400000);
    	for(int j = 7; j>0;j--){
    		BluePressed();
    		GreenPressed();
    		RedPressed();
    		wait_ticks(400000);
    	}

    	//wait_ticks(400000);
    	 *
    	if(numBlueLEDsOn == 0){
    		wait_ticks(400000);
    		AllOn();
    	}
*/
    	p1_switch_pressed();
    	p2_switch_pressed();
    	reset();
    }

    return 0 ;
}

void Setup() {
	//FIO0DIR |= (7<<7);//P0.7,8, and 9 are output
	//FIO0DIR |= (3)|(1<<6)|(3<<17);//P0.0,1,6,17,18,and 19 are output
	//FIO0DIR |= (3<<15)|(31<<21);//P0.15,16,21,22,23,24,25
	FIO0DIR |= (66028483);
}

void input_setup() {
    FIO1DIR &= ~(1<<30); //p1.30 input
    FIO1DIR &= ~(1<<31); //p1.31 input
    FIO0DIR &= ~(1<<2);  //p0.2  input
    FIO2DIR &= ~(1<<4);  //p2.4  input
    FIO2DIR &= ~(1<<5);  //p2.5  input
    FIO2DIR &= ~(1<<6);  //p2.6  input
}

void AllOn() {
	//FIO0PIN |= (7<<7);//turn on blue
	//FIO0PIN |= (3)|(1<<6)|(3<<17);//turn on green
	//FIO0PIN |= (3<<15)|(31<<21);//turn on red
	FIO0PIN |= (66028483);
	numRedLEDsOn = 7;
	numGreenLEDsOn = 5;
	numBlueLEDsOn = 3;
}

void AllOff(){
	//FIO0PIN &= ~(7<<7);//turn off blue
	//FIO0PIN &= ~(3)&~(1<<6)&~(3<<17);//turn off green
	//FIO0PIN &= ~(3<<15)&~(31<<21);//turn off red
	FIO0PIN &= ~(66028483);
	numRedLEDsOn = 0;
	numGreenLEDsOn = 0;
	numBlueLEDsOn = 0;
}

void reset(){
	if ((numRedLEDsOn == 0)&&(numGreenLEDsOn == 0)&&(numBlueLEDsOn == 0)){
		wait_ticks(405000*2.5);
		AllOn();
	}
}

void BluePressed(){
	if(numBlueLEDsOn > 0){
		switch(numBlueLEDsOn){
		case 3:
			FIO0PIN &= ~(1<<7);
			break;
		case 2:
			FIO0PIN &= ~(1<<8);
			break;
		case 1:
			FIO0PIN &= ~(1<<9);
			break;
		//default :
			//break;
		}
		numBlueLEDsOn--;
	}
}

void GreenPressed(){
	if(numGreenLEDsOn > 0){
		switch(numGreenLEDsOn){
		case 5:
			FIO0PIN &= ~(1<<17);
			break;
		case 4:
			FIO0PIN &= ~(1<<18);
			break;
		case 3:
			FIO0PIN &= ~(1<<1);
			break;
		case 2:
			FIO0PIN &= ~(1);
			break;
		case 1:
			FIO0PIN &= ~(1<<6);
			break;
		//default :
			//break;
		}
		numGreenLEDsOn--;
	}
}
void RedPressed(){
	if(numRedLEDsOn > 0){
		switch(numRedLEDsOn){
				case 7:
					FIO0PIN &= ~(1<<22);
					break;
				case 6:
					FIO0PIN &= ~(1<<21);
					break;
				case 5:
					FIO0PIN &= ~(1<<25);
					break;
				case 4:
					FIO0PIN &= ~(1<<24);
					break;
				case 3:
					FIO0PIN &= ~(1<<23);
					break;
				case 2:
					FIO0PIN &= ~(1<<16);
					break;
				case 1:
					FIO0PIN &= ~(1<<15);
					break;
				//default :
					//break;
				}
				numRedLEDsOn--;
	}
}
void p1_switch_pressed(){
	p1_blue();
	p1_green();
	p1_red();
	wait_ticks(80000);
}

void p2_switch_pressed(){
	p2_blue();
	p2_green();
	p2_red();
	wait_ticks(80000);
}

void p1_blue() {
    if(~(FIO1PIN >> 30) &1){
        BluePressed();
    }
}

void p1_green(){
    if(~(FIO1PIN >> 31) &1){
        GreenPressed();
    }
}

void p1_red(){
    if(~(FIO0PIN >> 2) &1){
        RedPressed();
    }
}

void p2_blue() {
    if(~(FIO2PIN >> 4) &1){
        BluePressed();
    }
}

void p2_green(){
    if(~(FIO2PIN >> 5) &1){
        GreenPressed();
    }
}

void p2_red(){
    if(~(FIO2PIN >> 6) &1){
        RedPressed();
    }
}

void disable_blue(){

}

void disable_green(){

}

void disable_red(){

}

void wait_ticks(int count)
{
	volatile int ticks = count;
	while (ticks>0)
		ticks--;
}

//COPY ALL OF THE FOLLOWING TO ALL FUTURE PROGRAMS
/*void wait(float count) //wait, in seconds
{
	volatile float ticks = count;
	ticks = ticks * 405000;
	while (ticks>0)
		ticks = ticks - 1.0;
}*/
