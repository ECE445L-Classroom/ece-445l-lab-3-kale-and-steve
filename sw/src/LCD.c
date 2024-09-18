#include <stdio.h>
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/ST7735.h"

void LCD_Out(time){
	char time = hours + ":" + minutes;
	ST7735_OutString(time);
}

int main(void){
	char word = "Hello";
	ST7735_OutString(word);
}