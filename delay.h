#include<stdio.h>
#include"LPC17xx.h"

volatile uint32_t msTicks = 0;

void SysTick_Handler(void){
    msTicks++;
}

void delay(int t){
    msTicks = 0;
    while(msTicks<t);
}

/*
w main umiescic:

uint32_t returnCode;
return Code = SysTick_Config(SystemCoreClock/100); //mianownik zmienic w zaleznosci od potrzeby
if(returnCode!=0){obsuga error} */
