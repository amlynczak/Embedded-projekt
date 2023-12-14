#include"lcd.h"
#include"tp_lib/TP_Open1768.h"

void calibrate(double *arr);

int calc(int xy, double a, double b);

/*void getXY(int *y, int *x){
	int px = 10; //trzeba bylo cos takiego bo tam krzyczal pozniej
	int py = 10;
	x = &px;
	y = &py;
	while(1){
		touchpanelGetXY(x, y);
		if(*x<4000 && *y > 200){
			x* = calc(*y , tab[0], tab[1])
			break;
		}
	
	}
}*/


/*tego nie chcemy docelowo*/

int calX(int x);
int calcY(int y);
