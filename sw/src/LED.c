#include <stdio.h>
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../src/Lab3Main.c"
void LED_Blink(void);

void LED_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x10;
	while((SYSCTL_RCGCGPIO_R&0x10)==0){}
  GPIO_PORTE_DIR_R |= 0x04;      
	GPIO_PORTE_DEN_R |= 0x04;
}

void LED_Blink(void){
	GPIO_PORTE_DATA_R ^= 0x04;
}

int main(void){
	LED_Init();
	LED_Blink();
	Delay1ms(1000);
	LED_Blink();
	Delay1ms(1000);
	return 0;
	
}