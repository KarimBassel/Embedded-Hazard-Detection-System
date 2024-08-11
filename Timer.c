
#include "Timer.h"
#include "TM4c123gh6pm.h"


void Timer0A_Init(){
  SYSCTL_RCGCTIMER_R |= 0x01;   
  TIMER0_CTL_R = 0x00000000;    
  TIMER0_CFG_R = 0x00000000;    
  TIMER0_TAMR_R = 0x00000001; 
  NVIC_EN0_R = (1<<19);
  TIMER0_TAILR_R = 0xF42400;    
  TIMER0_ICR_R = 0x00000001;    
  TIMER0_IMR_R = 0x00000001;   
  TIMER0_CTL_R = 0x00000003;   
}