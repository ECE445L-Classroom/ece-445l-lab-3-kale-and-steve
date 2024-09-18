#include <stdio.h>
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../src/Lab3Main.c"

int data;
int switchHold;

void Switch_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x04; //Activate Clock for Port C
	while((SYSCTL_RCGCGPIO_R&0x04)==0){}	//Allow time for clock 
	GPIO_PORTC_PCTL_R &= ~0x0F; //Regular GPIO
	GPIO_PORTC_AMSEL_R &= ~0x0F; //Disable Analog Function
	GPIO_PORTC_DIR_R &= ~0x0F; //input on PC1, PC2, PC3, and PC4
	GPIO_PORTC_AMSEL_R &=0x0F; //regular port function
	GPIO_PORTC_PUR_R = 0x0F; //enable pull up on PC1, PC2, PC3, and PC4
	GPIO_PORTC_DEN_R |= 0x0F; //enable digital port
	GPIO_PORTC_IS_R &= ~0x1E; // Configure PC1–PC4 for edge-sensitive interrupts GPIO_PORTC_IBE_R &= ~0x1E; // Configure PC1–PC4 for single-edge interrupts GPIO_PORTC_IEV_R |= 0x1E; // Set PC1–PC4 to trigger on rising edge GPIO_PORTC_ICR_R = 0x1E; // Clear any pending interrupts on PC1–PC4 NVIC_EN0_R = 0x04;
	}

void GPIOPortC_Handler(void){
	switchHold = 0;
	GPIO_PORTC_ICR_R = 0x1E; //clears interrupt bits for PC1-4
	data = GPIO_PORTC_DATA_R & 0x1E;
	if (alarmSound == true){
		alarmSound = false;
		return;
	}
	if (menu && (data & 0x08 != 0)){ // if menu enabled and PC3 pressed, exit menu
		menu = !menu;
		return;
	}
	else if (data & 0x08 != 0){ // PC3 hold enables the timer menu page
		while (data & 0x08 != 0){count++; data = GPIO_PORTC_DATA_R & 0x1E;}
		if (count > 1000){
			menu = !menu;
			return;
		}
	}
	if (menu){ // if timer menu enabled:
		if (data & 0x02 != 0){ //PC1 for alarm time up 
			alarmMinutes++;
			if (alarmMinutes == 60){
				alarmMinutes == 0;
				alarmHours++;
				if (alarmHours > 12){
					alarmHours = 1;
					alarmAM = !alarmAM;
				}
			}
		}
		if (data & 0x04 != 0){ //PC2 for alarm time down 
			alarmMinutes--;
			if (alarmMinutes == -1){
				alarmMinutes == 59;
				alarmHours--;
				if (alarmHours < 1){
					alarmHours = 12;
					alarmAM = !alarmAM;
				}
			}
		}
	}
	if (!menu){
		if (data & 0x02 != 0){ //PC1 for time up 
			minutes++;
		}
		if (data & 0x04 != 0){ //PC2 for time down 
			minutes--;
		}
	}
		
}


int main(void){
	GPIOPortC_Handler();
	ST7735_OutString(hours);
	ST7735_OutString(minutes);
}