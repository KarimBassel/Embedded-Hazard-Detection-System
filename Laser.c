#include "Laser.h"
#include "TM4c123gh6pm.h"

void Laser_Init(){
  // initialize the clock for port F
  SYSCTL_RCGCGPIO_R |= 0x2;
  
  // wait for the clock
  while ((SYSCTL_PRGPIO_R & 0x2) == 0) {};
  
  // unlock port F
  GPIO_PORTB_LOCK_R = 0x4C4F434B;
  
  // set commit register
  GPIO_PORTB_CR_R = 0x10;
  
  // set pins direction
  GPIO_PORTB_DIR_R = 0x10;
 // GPIO_PORTB_PUR_R = 0x40;
  // set PUR for input pins
  // enable pins using digital enable register
  GPIO_PORTB_DEN_R = 0x10;
}