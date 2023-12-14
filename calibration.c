#include"calibration.h"

void calibrate(double *arr){
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
	
	double a1 = 200.0/ (*y2 -*y1);
	double b1 = 20.0 - a1*(*y1);
	int a2mian = *x3 - *x1;
	double a2 = 280.0/(a2mian);
	double b2 = 20.0 - a2*(*x1);
	
	arr[0] = a1;
	arr[1] = b1;
	arr[2] = a2;
	arr[3] = b2;
	
	sprintf(coor, "%d , %d", (int)((a1)*1000), (int)((b1)*1000));
	writeString(100, 100, coor, LCDBlack);
	
	sprintf(coor, "%d , %d", (int)((a2)*1000), (int)((b2)*1000));
	writeString(200, 200, coor, LCDBlack);
	
	delay(100);
}

int calc(int xy, double a, double b){
    return (int)(a * (double)xy + b);
}


/*tego nie chcemy docelowo*/

int calX(int x){
    return (int)(0,0667 * (double)x - 17.16);
}
int calcY(int y){
    return (int)(0.0885 * (double)y - 12.71);
}