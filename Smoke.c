#include "Smoke.h"
#include "TM4c123gh6pm.h"
#include "Systick.h"
void Smoke_init(){
  unsigned int adc_value;
	
    SYSCTL_RCGCGPIO_R |= (1<<4);   
    SYSCTL_RCGCADC_R |= (1<<0);    
    
    /* initialize PE3 for AIN0 input  */
    GPIO_PORTE_AFSEL_R |= (1<<3);       
    GPIO_PORTE_DEN_R &= ~(1<<3);        
    GPIO_PORTE_AMSEL_R |= (1<<3);     
   
    /* initialize sample sequencer3 */
    ADC0_ACTSS_R &= ~(1<<3);
    ADC0_EMUX_R &= ~0xF000;    
    ADC0_SSMUX3_R = 0;        
    ADC0_SSCTL3_R |= (1<<1)|(1<<2);        
    ADC0_ACTSS_R |= (1<<3);       
    
	  /*Iniitialize PF3 as a digital output pin */
	  	 
   SYSCTL_RCGCGPIO_R |= 0x20;
   GPIO_PORTF_DIR_R       |= 0x08; 
   GPIO_PORTF_DEN_R       |= 0x08; 

}

void Detect_Smoke(){
  
    SysTickPeriodSet(1000);
    SysTickEnable();
    int counter=0;   
    GPIO_PORTB_DATA_R = 0x10;
    while(counter!=2){
      if(SysTick_Is_Time_out()==1) counter++;
    }
    counter=0;
    GPIO_PORTB_DATA_R &= ~(0x10);
}