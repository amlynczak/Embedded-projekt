#ifndef GAME_H
#define GAME_H

#include "usart.h"
#include "tp_lib/TP_Open1768.h"

static bool startFlag;
static ARM_DRIVER_USART * USARTdrv = &Driver_USART0;

typedef struct{
	int squares[5][5]; //0 - nic nie ma na polu, 1 - postawiony statek, -1 - trafiony statek
	int max_hits;
	int hits;
}Board;

typedef struct{
	Board boardPlayer;
	Board boardOpponent;
	bool win;
}Player;

bool isLegal(int x, int y, Board *b);

int przelicz(int x, int y);

void ustawStatkiRand(Player *p);

void start(float *tab);

bool shoot(float *tab, Player *player);

bool checkWin(Player *player);

void end(Player *player, float *tab);

void drawBoard(Board *board);

void drawX(int xy);

void drawVoid(int xy);

void calibrate(float *arr);

int calc(int xy, float a, float b);

void drawHit(int xy);

#endif
