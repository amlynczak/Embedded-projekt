#include"headers.h"

#include "Driver_USART.h"

extern ARM_DRIVER_USART Driver_USART0;

int main(){
	
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
	
	uint32_t returnCode;
	returnCode = SysTick_Config(SystemCoreClock/100);//zmiana mianownika->zmiana czasu delay
	if(returnCode!=0){/*obsluga errorow*/}
	
   lcdConfiguration(); //konfiguracja leda, trzeba wrzucic tak o
	
	touchpanelInit(); //inicjalizacja  touchpada
	
	// ILI9328 jest ukladem sterujacym

	init_ILI9325(); //do tego ukladu cos takiego
	
	
	double tab[4];
	
	calibrate(tab);
	drawBoard();
	start(tab);
		
	int px = 10; //trzeba bylo cos takiego bo tam krzyczal pozniej
	int py = 10;
	int *x = &px;
	int *y = &py;
	char coor[16];


    while(1){
		touchpanelGetXY(x, y); //z liba, przekazujemy te wskazniki
			
		if(calc(*y , tab[0], tab[1]) <= 155 && calc(*y , tab[0], tab[1]) >= 5 && calc(*x , tab[2], tab[3]) <= 315 && calc(*x , tab[2], tab[3]) >= 165){
				delay(10);
				int result = przelicz(calc(*y , tab[0], tab[1]), calc(*x , tab[2], tab[3]));
				sprintf(coor, "%d", result);
				writeString(100, 100, coor, LCDBlack);

				drawX(result);
			
		}
		USARTdrv->Receive(coor, 2);
		writeString(100, 100, coor, LCDBlack);

		drawRectangle(calc(*y, tab[0], tab[1]), calc(*x, tab[2], tab[3]), calc(*y, tab[0], tab[1]) +2 , calc(*x, tab[2], tab[3]) +2,  LCDBlue); //narysowanie gdzie sie klika
    }
}
