#include"lcd.h"

void drawRectangle(int x1, int y1, int x2, int y2, uint16_t color){
    for(int i=x1; i<x2; i++){
        for(int j=y1; j<y2; j++){
            lcdWriteReg(ADRY_RAM, j);
            lcdWriteReg(ADRX_RAM, i);
            lcdWriteReg(DATA_RAM, color);
        }
    }
}

void writeSign(int x_0, int y_0, unsigned char sign, uint16_t color){
    unsigned char tab[16];

    GetASCIICode(0, tab, sign);

    for(int i=0; i<16; i++){
        for(int j=0; j<8; j++){
            lcdWriteReg(ADRY_RAM, y_0 + (8-j));
            lcdWriteReg(ADRX_RAM, x_0 + (16-i));
            unsigned char tmp = tab[i];
            if(tmp>>j & 1){
                lcdWriteReg(DATA_RAM, color);
            }else{
                lcdWriteReg(DATA_RAM, LCDWhite);
            }
        }
    }
}

void writeString(int x_0, int y_0, char *napis, uint16_t color){
    int x = x_0;
    int y = y_0;
    for(int i=0; i<strlen(napis); i++){
        writeSign(x, y, napis[i], color);
        y = y+10;
    }
}
