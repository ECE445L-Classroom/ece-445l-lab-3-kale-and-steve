// Lab3Main.c
// Runs on LM4F120/TM4C123
// Uses ST7735.c to display the clock
// patterns to the LCD.
//    16-bit color, 128 wide by 160 high LCD
// Mark McDermott, Daniel Valvano and Jonathan Valvano
// Lab solution, do not post
// August 3,2024

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2024

 Copyright 2024 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// Specify your hardware connections, feel free to change
// PD0 is squarewave output to speaker
// PE0 is mode select
// PE1 is left
// PE2 is right 
// PE3 is up
// PE4 is down
// if alarm is sounding, any button will quiet the alarm

#include <stdio.h>
#include <stdint.h>
#include "../inc/ST7735.h"
#include "../inc/PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "../inc/Timer0A.h"
#include "../src/LED.h"
#include "../src/LCD.h"
#include "../src/Switch.h"
#include "Lab3.h"
#include <stdbool.h>
// ---------- Prototypes   -------------------------
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode
void Switch_Init(void);
void LCD_Init(void);
void LED_Init(void);
void Sound_Init(void);
void Clock(void);
uint32_t seconds = 0;
uint32_t minutes = 0;
uint32_t hours = 0;
uint32_t time;
uint32_t alarmMinute = 0;
uint32_t alarmHour = 0;
bool alarmAM = true;

bool am = true;
bool menu = false;
bool alarmSound = false;

int main(void){
  DisableInterrupts();
  PLL_Init(Bus80MHz);    // bus clock at 80 MHz
  Switch_Init();
	LCD_Init();
	LED_Init();
	Sound_Init();
	Output_Init(); //initialize ST7735
	Timer0A_Init(Clock, 80000000, 1);
	EnableInterrupts();
	time = 1200;
  while(1){
		if (menu == false){
			PrintTime();
		}
		else{PrintAlarmTime();}
		}
		if (alarmMinute == minutes && alarmHour == hours){
		for(int i = 0; i <10000000; i++){
			Sound_Out();
			alarmSound = true;
		}
	}
}

void Clock(void){
	seconds++;
	if(seconds == 60){
		minutes++;
		seconds = 0;
		if(minutes >= 60){
			minutes = 0;
			hours++;
			if (hours > 12){
				hours = 1;
				am = !am;
			}
		}
	}
	time = 100 * hours + minutes;
	LED_Blink();
}
	
