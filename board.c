#include"board_test.h"

void drawBoard(void){
	lcdConfiguration();
	drawRectangle(0, 0, 240, 320, LCDWhite);
	
	/* obrys*/
	drawRectangle(5, 5, 155, 155, LCDBlack);
	drawRectangle(6, 6, 154, 154, LCDWhite);
	
	drawRectangle(5, 165, 155, 315, LCDBlack);
	drawRectangle(6, 166, 154, 314, LCDWhite);
	
	/* linie pionowe*/
    writeSign(157, 16, 'A', LCDBlack); //dodane opisy pol - od A do E na kolumnach
	drawRectangle(5, 34, 155, 35, LCDBlack);
    writeSign(157, 46, 'B', LCDBlack);
	drawRectangle(5, 64, 155, 65, LCDBlack);
    writeSign(157, 76, 'C', LCDBlack);
	drawRectangle(5, 94, 155, 95, LCDBlack);
    writeSign(157, 106, 'D', LCDBlack);
	drawRectangle(5, 124, 155, 125, LCDBlack);
    writeSign(157, 136, 'E', LCDBlack);

    writeSign(157, 176, 'A', LCDBlack);
	drawRectangle(5, 194, 155, 195, LCDBlack);
    writeSign(157, 206, 'B', LCDBlack);
	drawRectangle(5, 224, 155, 225, LCDBlack);
    writeSign(157, 236, 'C', LCDBlack);
	drawRectangle(5, 254, 155, 255, LCDBlack);
    writeSign(157, 266, 'D', LCDBlack);
	drawRectangle(5, 284, 155, 285, LCDBlack);
    writeSign(157, 296, 'E', LCDBlack);
	
	/*linie poziome*/
	writeSign(12, 156, '5', LCDBlack); //i dodane od 1 do 5 na wierszach
	drawRectangle(34, 5, 35, 155, LCDBlack);
	writeSign(42, 156, '4', LCDBlack);
	drawRectangle(64, 5, 65, 155, LCDBlack);
	writeSign(72, 156, '3', LCDBlack);
	drawRectangle(94, 5, 95, 155, LCDBlack);
	writeSign(102, 156, '2', LCDBlack);
	drawRectangle(124, 5, 125, 155, LCDBlack);
	writeSign(132, 156, '1', LCDBlack);
		
	drawRectangle(34, 165, 35, 315, LCDBlack);
	drawRectangle(64, 165, 65, 315, LCDBlack);
	drawRectangle(94, 165, 95, 315, LCDBlack);
	drawRectangle(124, 165, 125, 315, LCDBlack);
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

void drawX(int xy){
	int x = (xy)/10;
	int y = xy - y;
	
	int x_0, y_0, x_1, y_1;
	
	x_0 = 5 + 30 * (x-1);
	y_0 = 165 + 30 * (y-1);
	
	x_1 = 5 + 30 * x;
	y_1 = 165 + 30 * y;
	
	for(int i=x_0; i<x_1; i++){
		for(int j=y_0; j<y_1; j++){
			if(i==j){
				drawRectangle(j-1,j+1,j-1,j+1, LCDRed);
			}
		}
	}
	
}
