#include "usart.h"
#include "lcd.h"
#include "game.h"

int main(){
	
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
	start(tab);
	bool gameOn = true;
	
	while(gameOn){
		gameOn = shoot(tab, &player);
	}
	
	end(&player, tab);
}
