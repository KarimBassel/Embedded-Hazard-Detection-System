#include <stdio.h>
#include "types.h"

void Delay2(unsigned long counter);
void HC05_init(void); 
char Bluetooth_Read(void); 
void Bluetooth_Write(unsigned char data); 
void Bluetooth_Write_String(char *str); 