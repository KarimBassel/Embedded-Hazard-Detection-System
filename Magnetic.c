#include "Magnetic.h"
#include "TM4c123gh6pm.h"
#include "Systick.h"
void Magnetic_Init(){
  
   // initialize the clock for port F
  SYSCTL_RCGCGPIO_R |= 0x00000020;
  
  // wait for the clock
  while ((SYSCTL_PRGPIO_R & 0x00000020) == 0) {};
  
  // unlock port F
  GPIO_PORTF_LOCK_R = 0x4C4F434B;
  
  // set commit register
  GPIO_PORTF_CR_R = 0x02;
  
  // set pins direction
  GPIO_PORTF_DIR_R = 0x02;
  
  // set PUR for input pins
  // enable pins using digital enable register
  GPIO_PORTF_DEN_R = 0x2;
  
  // initialize the clock for port F
  SYSCTL_RCGCGPIO_R |= 0x4;
  
  // wait for the clock
  while ((SYSCTL_PRGPIO_R & 0x4) == 0) {};
  
  // unlock port F
  GPIO_PORTC_LOCK_R = 0x4C4F434B;
  
  // set commit register
  GPIO_PORTC_CR_R = 0x40;
  
  // set pins direction
  GPIO_PORTC_DIR_R = 0x00;
  GPIO_PORTC_PUR_R = 0x40;
  // set PUR for input pins
  // enable pins using digital enable register
  GPIO_PORTC_DEN_R = 0x40;
}
void Detect_Magnet(){
    SysTickPeriodSet(1000);
    SysTickEnable();
    int counter=0;
    //GPIO_PORTF_DATA_R = 0x8;
    GPIO_PORTB_DATA_R = 0x10;
    while(counter!=4){
      if(SysTick_Is_Time_out()==1) counter++;
    }
    counter=0;
    //GPIO_PORTF_DATA_R &= ~(0x8);
    GPIO_PORTB_DATA_R &= ~(0x10);
}