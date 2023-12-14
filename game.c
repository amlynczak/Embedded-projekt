#include"game.h"

void start(double *tab){
	static ARM_DRIVER_USART * USARTdrv = &Driver_USART0;
  USARTdrv->Initialize(NULL);   
	USARTdrv->PowerControl(ARM_POWER_FULL);  
	USARTdrv->Control(ARM_USART_MODE_ASYNCHRONOUS |
		ARM_USART_DATA_BITS_8 |
		ARM_USART_PARITY_NONE |                      
		ARM_USART_STOP_BITS_1 |                      
		ARM_USART_FLOW_CONTROL_NONE, 4800);  
	USARTdrv->Control (ARM_USART_CONTROL_TX, 1);    
	USARTdrv->Control (ARM_USART_CONTROL_RX, 1);
	
	drawRectangle(190,95, 220, 225, LCDBlack);
	drawRectangle(191,96,219,224,LCDWhite);
	writeString(196, 135, "READY", LCDBlack);
	
	int px = 10; //trzeba bylo cos takiego bo tam krzyczal pozniej
	int py = 10;
	int *x = &px;
	int *y = &py;
	char text[5];
	
	while(1){
		touchpanelGetXY(x, y);
		if(calc(*y , tab[0], tab[1]) < 220 && calc(*y , tab[0], tab[1]) > 190 && calc(*x , tab[2], tab[3]) > 95 && calc(*x , tab[2], tab[3]) < 225){
			startFlag = true;
			USARTdrv->Send("READY", 5);
			break;
		}
			USARTdrv->Receive(text, 5);
			writeString(196, 135, text, LCDBlack);
			if(!strcmp(text, "READY")){
				startFlag = false;
				break;
		}
	}
	drawRectangle(190,95, 220, 225, LCDWhite);
}