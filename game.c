#include "lcd.h"
#include "usart.h"
#include "game.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



bool isLegal(int x, int y, Board *b){
	if(b->squares[x][y] == 1){
			return false;
	}
	
	for(int i=x-1; i<=x+1; i++){
		for(int j=y-1; j<=y+1; j++){
			if(i>=0 && i<=5 && j>=0 && j<=5){
				if(i != x || j!= y){
					if(b->squares[i][j] == 1){
						return false;
					}
				}
			}
		}
	}
	return true;
}

int przelicz(int x, int y){
    int coordinates = 0; //skonstruowane tak, ze liczba dziesiatek to kolumny, liczba jednosci to wiersze
		for(int i=0; i<5; i++){
			if(x>= 5 + 30 * i && x< 5 + 30 * (i+1)){
				coordinates += (5-i);
			}
		}
		
		for(int i=0; i<5; i++){
			if(y>= 165 + 30 * i && y< 165 + 30 * (i+1)){
				coordinates += 10 * (i+1);
			}
		}

    return coordinates;
}

void ustawStatkiRand(Player *p){
	srand(msTicks);
	
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			p->boardPlayer.squares[i][j] = 0; 
		}
	}

	int randX;
	int randY;
	
	if(rand()%2==0){
		randX = rand()%3;
		randY = rand()%5;
		
		p->boardPlayer.squares[randX][randY] = 1;
		p->boardPlayer.squares[randX+1][randY] = 1;
		p->boardPlayer.squares[randX+2][randY] = 1;
	}else{
		randX = rand()%5;
		randY = rand()%3;
		
		p->boardPlayer.squares[randX][randY] = 1;
		p->boardPlayer.squares[randX][randY+1] = 1;
		p->boardPlayer.squares[randX][randY+1] = 1;
	}
	
	if(rand()%2==0){
		do{
			randX = rand()%4;
			randY = rand()%5;
		}while(!isLegal(randX, randY, &p->boardPlayer) || !isLegal(randX+1, randY, &p->boardPlayer));
		p->boardPlayer.squares[randX][randY] = 1;
		p->boardPlayer.squares[randX+1][randY] = 1;
	}else{
		do{
			randX = rand()%5;
			randY = rand()%4;
		}while(!isLegal(randX, randY, &p->boardPlayer) || !isLegal(randX, randY+1, &p->boardPlayer));
		p->boardPlayer.squares[randX][randY] = 1;
		p->boardPlayer.squares[randX][randY+1] = 1;
	}
	
	do{
		randX = rand()%5;
		randY = rand()%5;
	}while(!isLegal(randX, randY, &p->boardPlayer));
	
	p->boardPlayer.squares[randX][randY] = 1;
	
}

void start(float *tab){
	USART_Init(USARTdrv, 9600);
	USART_Init(USARTdrv1, 115200);
	drawRectangle(190,95, 220, 225, LCDBlack);
	drawRectangle(191,96,219,224,LCDWhite);
	writeString(196, 135, "READY", LCDBlack);
	
	int px = 10; //trzeba bylo cos takiego bo tam krzyczal pozniej
	int py = 10;
	int *x = &px;
	int *y = &py;
	char text[1];
	
	while(1){
		touchpanelGetXY(x, y);
		if(calc(*y , tab[0], tab[1]) < 220 && calc(*y , tab[0], tab[1]) > 190 && calc(*x , tab[2], tab[3]) > 95 && calc(*x , tab[2], tab[3]) < 225){
			startFlag = true;
			USARTdrv->Send("R", 1);
			break;
		}
		USARTdrv->Receive(text, 1);
		//USARTdrv1->Send(text, 1);
			
		if(text[0] == 'R'){
					startFlag = false;
					break;
			}
	}
	drawRectangle(190,95, 220, 225, LCDWhite);
	USART_DeInit(USARTdrv);
	USART_DeInit(USARTdrv1);
}

bool shoot(float *tab, Player *player){
	int px = 0; 
	int py = 0;
	int *x = &px;
	int *y = &py;
	int result = 0;
	char coor[2] = {'0', '0'};
	char info[1] = {'0'};
	
	USART_Init(USARTdrv, 9600);
	USART_Init(USARTdrv1, 115200);
	
	while(1){
		if(startFlag){
			USARTdrv->Receive(info, 1);
			writeString(196, 140, "wait", LCDBlack);
			delay(100);
			USARTdrv1->Send(info, 1);
			if(info[0] == 'R'){
				startFlag = true;
				drawRectangle(190,95, 220, 225, LCDWhite);

				break;
			}
		} else{
			delay(100);
			startFlag = false;
			USARTdrv->Send("R", 1);
			USARTdrv1->Send("R", 1);
			break;
		}
	}
	drawRectangle(190,95, 220, 225, LCDWhite);
	writeString(196, 140, "sent", LCDBlack);
	
	USART_DeInit(USARTdrv);
	USART_DeInit(USARTdrv1);
	
	USART_Init(USARTdrv, 9600);
	USART_Init(USARTdrv1, 115200);
	
	while(1){
		if(!startFlag){
			USARTdrv->Receive(coor, 2);
			writeString(196, 140, "op. turn!!", LCDBlack);
			result = atoi(coor);
			if(result>0){
				writeString(196, 50, coor, LCDBlack);
				break;
			}
		}else{
			delay(100);
			writeString(196, 140, "shoot!", LCDBlack);
			while(1){
				touchpanelGetXY(x, y);
				if(calc(*y , tab[0], tab[1]) <= 155 && calc(*y , tab[0], tab[1]) >= 5 && calc(*x , tab[2], tab[3]) <= 315 && calc(*x , tab[2], tab[3]) >= 165){
					delay(10);
					result = przelicz(calc(*y , tab[0], tab[1]), calc(*x , tab[2], tab[3]));
					sprintf(coor, "%d", result);
					writeString(196, 100, coor, LCDBlack);
					break;
				}
			}
			USARTdrv->Send(coor, 2);
			writeString(196, 140, "sent", LCDBlack);
			break;
		}
	}
	
	USART_DeInit(USARTdrv);
	USART_DeInit(USARTdrv1);
	
	int y_b = result/10;
	int x_b = 5-(result - y_b*10);
	y_b = y_b -1;
	
	USART_Init(USARTdrv, 9600);
	USART_Init(USARTdrv1, 115200);
	
	while(1){
		if(startFlag){
			USARTdrv->Receive(info, 1);
			writeString(196, 140, "waitng for check", LCDBlack);
			if(info[0] == 'h' || info[0] == 'm') break;
		}else{
			writeString(196, 140, "checking...     ", LCDBlack);
			if(player->boardPlayer.squares[x_b][y_b] == 1){
				info[0] = 'h';
				player->boardPlayer.hits++;
				writeString(196, 140, "ship hit!      ", LCDRed);
			}
			if(player->boardPlayer.squares[x_b][y_b] == 0){
				info[0] = 'm';
				writeString(196, 140, "miss!         ", LCDGreen);
			}
			USARTdrv->Send(info, 1);
			delay(100);
			break;
		}
	}
	writeString(196, 140, "checked", LCDBlack);
	
	USART_DeInit(USARTdrv);
	USART_DeInit(USARTdrv1);
	
	if(startFlag){
		if(info[0] == 'h'){
			player->boardOpponent.squares[x_b][y_b] = 1;
			player->boardOpponent.hits++;
			writeString(196, 135, "ship hit!", LCDRed);
			drawX(result);
		}else if(info[0] == 'm'){
			player->boardOpponent.squares[x_b][y_b] = 0; // tutaj wartosc dla nietrafionego
			writeString(196, 135, "missed!", LCDBlack);
			drawVoid(result);
		}
	}
	
	if(info[0] == 'm'){
		startFlag = !startFlag;
	}
	
	
	
	return checkWin(player);
}

bool checkWin(Player *player) {
    if((player->boardOpponent.hits < player->boardOpponent.max_hits) && (player->boardPlayer.hits < player->boardPlayer.max_hits)){
			return true;
		}
		
		if(player->boardOpponent.hits == player->boardOpponent.max_hits){
			player->win = true;
			return false;
		}
		
		if(player->boardPlayer.hits == player->boardPlayer.max_hits){
			player->win = false;
			return false;
		}
		
		return true;
}

void end(Player *player, float *tab){
	drawRectangle(0, 0, 240, 320, LCDWhite);
	if(player->win){
		writeString(100, 100, "YOU WIN!", LCDBlack);
	}else{
		writeString(100, 100, "YOU LOST :(", LCDBlack);
	}
}

//z board

void drawBoard(Board *board){
	lcdConfiguration();
	drawRectangle(0, 0, 240, 320, LCDWhite);
	
	/* obrys*/
	drawRectangle(5, 5, 155, 155, LCDBlack);
	drawRectangle(6, 6, 154, 154, LCDWhite);
	
	drawRectangle(5, 165, 155, 315, LCDBlack);
	drawRectangle(6, 166, 154, 314, LCDWhite);
	
	/* linie pionowe*/
	for(int i=1; i<5; i++){
		drawRectangle(5, 4 + 30*i, 155, 5+30*i, LCDBlack);
	}
  writeSign(157, 16, 'A', LCDBlack); //dodane opisy pol - od A do E na kolumnach
  writeSign(157, 46, 'B', LCDBlack);
  writeSign(157, 76, 'C', LCDBlack);
  writeSign(157, 106, 'D', LCDBlack);
  writeSign(157, 136, 'E', LCDBlack);
	
	for(int i=1; i<5; i++){
		drawRectangle(5, 164+i*30, 155, 165+i*30, LCDBlack);
	}
  writeSign(157, 176, 'A', LCDBlack);
  writeSign(157, 206, 'B', LCDBlack);
  writeSign(157, 236, 'C', LCDBlack);
  writeSign(157, 266, 'D', LCDBlack);
  writeSign(157, 296, 'E', LCDBlack);
	
	
	/*linie poziome*/
	for(int i=1; i<5; i++){
		drawRectangle(4+i*30, 5, 5+30*i, 155, LCDBlack);
		drawRectangle(4+i*30, 165, 5+30*i, 315, LCDBlack);
	}
	writeSign(12, 156, '5', LCDBlack); //i dodane od 1 do 5 na wierszach
	writeSign(42, 156, '4', LCDBlack);
	writeSign(72, 156, '3', LCDBlack);
	writeSign(102, 156, '2', LCDBlack);
	writeSign(132, 156, '1', LCDBlack);
	
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			if(board->squares[i][j] == 1){
				drawRectangle(7+30*i, 7+30*j, 2+30*(i+1), 2+30*(j+1), LCDGrey);
			}
		}
	}
}

void drawX(int xy){
	int y = (xy)/10;
	int x = 6-(xy - 10*y);
	
	int x_0, y_0, x_1, y_1;
	
	x_0 = 5 + 30 * (x-1);
	y_0 = 165 + 30 * (y-1);
	
	x_1 = 5 + 30 * x;
	y_1 = 165 + 30 * y;
	
	drawRectangle(x_0, y_0, x_1, y_1, LCDRed);
}

void drawVoid(int xy){
	int y = (xy)/10;
	int x = 6-(xy - 10*y);
	
	int x_0, y_0, x_1, y_1;
	
	x_0 = 5 + 30 * (x-1);
	y_0 = 165 + 30 * (y-1);
	
	x_1 = 5 + 30 * x;
	y_1 = 165 + 30 * y;
	
	drawRectangle(x_0, y_0, x_1, y_1, LCDBlueSea);
}

void calibrate(float *arr){
  int px1 = 4095;
	int py1 = 0;
	int px2 = 4095;
	int py2 = 0;
	int px3 = 4095;
	int py3 = 0;
	int *x1 = &px1, *y1 = &py1;
	int *x2 = &px2, *y2 = &py2;
	int *x3 = &px3, *y3 = &py3;

  char coor[16];

  /*rysowanie krzyzykow do kalibracji/wyliczenia przelicznika miedzy tp a lcd*/
	drawRectangle(0, 0, 240, 320, LCDWhite);
	//lewy dolny
	drawRectangle(20, 11, 21, 30, LCDBlack);
	drawRectangle(11, 20, 30, 21, LCDBlack);	
	
	while(1){
		touchpanelGetXY(x1, y1);
		sprintf(coor, "%d , %d", *x1, *y1);
		writeString(100, 100, coor, LCDBlack);
		if(*x1<4000 && *y1 > 200){
			break;
		}
	}
	delay(100);

	//lewy gorny
	drawRectangle(0, 0, 240, 320, LCDWhite);
	drawRectangle(219, 10, 220, 30, LCDBlack);
	drawRectangle(210, 20, 229, 21, LCDBlack);
	
	while(1){
		touchpanelGetXY(x2, y2);
		sprintf(coor, "%d , %d", *x2, *y2);
		writeString(100, 100, coor, LCDBlack);
		if(*x2<4095 && *y2 > 200){
			break;
		}
	}
	delay(100);
		
	//prawy dolny
	drawRectangle(0, 0, 240, 320, LCDWhite);
	drawRectangle(20, 290, 21, 309, LCDBlack);
	drawRectangle(11, 300, 30, 301, LCDBlack);
	
	while(1){
		touchpanelGetXY(x3, y3);
		sprintf(coor, "%d , %d", *x3, *y3);
		writeString(100, 100, coor, LCDBlack);
		if(*x3<4000 && *y3 > 200){
			break;
		}
	}
	delay(100);
	
	float a1 = 200.0/ (*y2 -*y1);
	float b1 = 20.0 - a1*(*y1);
	float a2 = 280.0/(*x3 - *x1);
	float b2 = 20.0 - a2*(*x1);
	
	arr[0] = a1;
	arr[1] = b1;
	arr[2] = a2;
	arr[3] = b2;
	
	delay(100);
}

int calc(int xy, float a, float b){
    return (int)(a * (float)xy + b);
}
