#include "usart.h"
#include "lcd.h"
#include "game.h"
#include "Board_Buttons.h"
#include "Board_Joystick.h"

int main(){
	Joystick_Initialize();
	uint32_t returnCode;
	returnCode = SysTick_Config(SystemCoreClock/100);
	if(returnCode!=0){}
	
  lcdConfiguration();
	
	touchpanelInit();
	init_ILI9325();
	
	float tab[4]; //coordinates
	
	calibrate(tab);
	
	Player player;
	player.win = false;
	player.boardOpponent.max_hits = 6;
	player.boardOpponent.hits = 0;
	player.boardPlayer.max_hits = 6;
	player.boardPlayer.hits = 0;
	
	ustawStatkiRand(&player);
	drawBoard(&player.boardPlayer);
		
	
	while(1){
		int px = 0;
		int py = 0;
		int *x = &px;
		int *y = &py;
			
		touchpanelGetXY(x, y);
		
		if(calc(*y , tab[0], tab[1]) < 220 && calc(*y , tab[0], tab[1]) > 190 && calc(*x , tab[2], tab[3]) > 95 && calc(*x , tab[2], tab[3]) < 225){
				break;
		}
		 
		if(Buttons_GetState() == 1){
			ustawStatkiRand(&player);
			drawBoard(&player.boardPlayer);
			drawRectangle(190,95, 220, 225, LCDBlack);
			drawRectangle(191,96,219,224,LCDWhite);
			writeString(196, 135, "SUBMIT", LCDBlack);
			
		}
	}
	Joystick_Uninitialize();


	start(tab);
	bool gameOn = true;
	
	while(gameOn){
		gameOn = shoot(tab, &player);
	}
	
	end(&player, tab);
}
