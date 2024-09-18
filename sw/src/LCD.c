#include <stdio.h>
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/ST7735.h"
#include "../src/Lab3Main.c"

void LCD_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x01;
	while((SYSCTL_RCGCGPIO_R&0x01)==0){}
  GPIO_PORTE_DIR_R |= 0xEC;      
	GPIO_PORTE_DEN_R |= 0xEC;
	ST7735_InitR(1);
}

void PrintTime(){
	ST7735_OutUDec(time/100);
	ST7735_OutString(":");
	ST7735_OutUDec(time%100);
	if (am == true){
		ST7735_OutString(" AM");
	}
	else {
		ST7735_OutString(" PM");
	}
}
void PrintAlarmTime(){
	ST7735_OutUDec(alarmTime/100);
	ST7735_OutString(":");
	ST7735_OutUDec(alarmTime%100);
	if (alarmAm == true){
		ST7735_OutString(" AM");
	}
	else {
		ST7735_OutString(" PM");
	}
}

int main2(void){
	ST7735_OutString("Hello");
}



/*
	int length = snprintf( NULL, 0, "%d", x );
	char* str = malloc( length + 1 );
	snprintf( str, length + 1, "%d", x );
	ST7735_OutString(str);
*/