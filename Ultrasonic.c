#include "Ultrasonic.h"
#include "TM4c123gh6pm.h"
#include "Systick.h"
uint32 Measure_distance(void)
{
    int lastEdge, thisEdge;
	
	  DIO_WritePin(&GPIO_PORTA_DATA_R, 4, 0);
	  Delay_MicroSecond(10); 
	  DIO_WritePin(&GPIO_PORTA_DATA_R, 4, 1);  
	  Delay_MicroSecond(10); 
	  DIO_WritePin(&GPIO_PORTA_DATA_R, 4, 0);

 	while(1)
	{
    TIMER0_ICR_R = 4;           
    while((TIMER0_RIS_R & 0x4) == 0) ;    
	  if(GPIO_PORTB_DATA_R & (1<<6)) 
		{
    lastEdge = TIMER0_TAR_R;     
    TIMER0_ICR_R = 4;            
    while((TIMER0_RIS_R & 0x4) == 0) ;    
    thisEdge = TIMER0_TAR_R;     
		return (thisEdge - lastEdge); 
		}
	}
}


void Timer0ACapture_init(void)
{
    SYSCTL_RCGCTIMER_R |= 1;     
    SYSCTL_RCGCGPIO_R |= 2;
    
    GPIO_PORTB_DIR_R &= ~0x40;       
    GPIO_PORTB_DEN_R|= 0x40;         
    GPIO_PORTB_AFSEL_R |= 0x40;      
    GPIO_PORTB_PCTL_R &= ~0x0F000000;  
    GPIO_PORTB_PCTL_R |= 0x07000000;
    

	  SYSCTL_RCGCGPIO_R |= 1;      
	  GPIO_PORTA_DIR_R |=(1<<4);        
	  GPIO_PORTA_DEN_R |=(1<<4);        

    TIMER0_CTL_R &= ~1;        
    TIMER0_CFG_R = 4;          
    TIMER0_TAMR_R = 0x17;        
    TIMER0_CTL_R |=0x0C;        
    TIMER0_CTL_R |= (1<<0);           
}





void Delay_MicroSecond(int time)
{
    int i;
    SYSCTL_RCGCTIMER_R |= 2;
    TIMER1_CTL_R = 0;           
    TIMER1_CFG_R = 0x04;         
    TIMER1_TAMR_R = 0x02;       
    TIMER1_TAILR_R = 16 - 1;  
    TIMER1_ICR_R = 0x1;         
    TIMER1_CTL_R |= 0x01;      

    for(i = 0; i < time; i++)
    {
        while ((TIMER1_RIS_R & 0x1) == 0) ;      
        TIMER1_ICR_R = 0x1;      
    }
}


void printstring(char *str)
{
  while(*str)
	{
		printf("%c" , *(str++) ) ;
	}
}
void Delay(unsigned long counter)
{
	unsigned long i = 0;
	
	for(i=0; i< counter*1000; i++);
}
void Detect_Motion(){
  
    SysTickPeriodSet(1000);
    SysTickEnable();
    int counter=0;   
    //GPIO_PORTF_DATA_R = 0x4;
    GPIO_PORTB_DATA_R = 0x10;
    while(counter!=7){
      if(SysTick_Is_Time_out()==1) counter++;
    }
    counter=0;
    //GPIO_PORTF_DATA_R &= ~(0x4);
    GPIO_PORTB_DATA_R &= ~(0x10);
}