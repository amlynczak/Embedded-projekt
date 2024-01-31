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

/*KALIBRACJA*/

void calibrate(float *arr);

int calc(int xy, float a, float b);

/*PLANSZA (ustawienie + rysowanie)*/

void ustawStatkiRand(Player *p);

bool isLegal(int x, int y, Board *b);

void drawBoard(Board *board);

/*ROZPOCZECIE GRY*/

void start(float *tab);

/*ROZGRYWKA*/

bool shoot(float *tab, Player *player);

int przelicz(int x, int y);

void drawHit(int xy);

void drawX(int xy);

void drawVoid(int xy);

bool checkWin(Player *player);

/*ZAKONCZENIE*/

void end(Player *player, float *tab);

#endif
