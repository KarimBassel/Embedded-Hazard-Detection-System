#include <stdio.h>
#include "types.h"


uint32 Measure_distance(void);
void Timer0ACapture_init(void);
void Delay_MicroSecond(int time);
void UART5_init(void);
void UART5_Transmitter(unsigned char data);
void printstring(char *str);
void Delay(unsigned long counter);
void Detect_Motion();
