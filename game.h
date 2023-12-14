#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "calibration.h"
#include "Driver_USART.h"

extern ARM_DRIVER_USART Driver_USART0;
static bool startFlag;


void start(double *tab);
