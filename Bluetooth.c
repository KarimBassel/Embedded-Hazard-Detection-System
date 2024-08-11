#include "Bluetooth.h"
#include "TM4c123gh6pm.h"

void HC05_init(void)
{
	SYSCTL_RCGCUART_R |= 0x20; 
    SYSCTL_RCGCGPIO_R |= 0x10; 
    Delay(1);
    /* UART0 initialization */
    UART5_CTL_R = 0;         
    UART5_IBRD_R = 104;     
    UART5_FBRD_R = 11;       
    UART5_CC_R = 0;          
    UART5_LCRH_R = 0x60;     
    UART5_CTL_R = 0x301;     

    /* UART5 TX5 and RX5 use PE4 and PE5. Configure them digital and enable alternate function */
    GPIO_PORTE_DEN_R = 0x30;     
    GPIO_PORTE_AFSEL_R = 0x30;   
    GPIO_PORTE_AMSEL_R = 0;    
    GPIO_PORTE_PCTL_R = 0x00110000;    
}
char Bluetooth_Read(void)  
{
    char data;
	  while((UART5_FR_R & (1<<4)) != 0); 
    data = UART5_DR_R ;  	
    return (unsigned char) data; 
}

void Bluetooth_Write(unsigned char data)  
{
    while((UART5_FR_R & (1<<5)) != 0);
    UART5_DR_R = data;
}

void Bluetooth_Write_String(char *str)
{
  while(*str)
	{
		Bluetooth_Write(*(str++));
	}
}

void Delay2(unsigned long counter)
{
	unsigned long i = 0;
	
	for(i=0; i< counter; i++);
}