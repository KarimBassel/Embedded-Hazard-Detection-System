#include "TM4c123gh6pm.h"
#include "bitwise_operation.h"
#include "DIO.h"


void DIO_Init() {
  // initialize the clock for port F
  SYSCTL_RCGCGPIO_R |= 0x00000020;
  
  // wait for the clock
  while ((SYSCTL_PRGPIO_R & 0x00000020) == 0) {};
  
  // unlock port F
  GPIO_PORTF_LOCK_R = 0x4C4F434B;
  
  // set commit register
  GPIO_PORTF_CR_R = 0x1F;
  
  // set pins direction
  GPIO_PORTF_DIR_R = 0x0E;
  
  // set PUR for input pins
  GPIO_PORTF_PUR_R = 0x11;
  // enable pins using digital enable register
  GPIO_PORTF_DEN_R = 0x1F;
}
void PortA_Init(){
  SYSCTL_RCGCGPIO_R |= 0x1;
  while ((SYSCTL_PRGPIO_R & 0x1) == 0) {};
  
  // unlock port F
  GPIO_PORTA_LOCK_R = 0x4C4F434B;
  
  // set commit register
  GPIO_PORTA_CR_R |= (1<<4) ;
  
  // set pins direction
  GPIO_PORTA_DIR_R |= (1<<4);
  
  // enable pins using digi0tal enable register
  GPIO_PORTA_DEN_R |= (1<<4);
}
void PortB_Init(){
  SYSCTL_RCGCGPIO_R |= 0x2;
  while ((SYSCTL_PRGPIO_R & 0x0000002) == 0) {};
  
  // unlock port F
  GPIO_PORTB_LOCK_R = 0x4C4F434B;
  
  // set commit register
  GPIO_PORTB_CR_R |= (1 << 6);
  
  // set pins direction
  GPIO_PORTB_DIR_R |= 0x00;
  GPIO_PORTB_PDR_R = (1<<6);
  // enable pins using digi0tal enable register
  GPIO_PORTB_DEN_R |= (1 << 6);
}
void DIO_WritePin(vulong32_ptr port, uint8 pin, uint8 value) {
  if (value == 1) Set_Bit(*port, pin);
  else Clear_Bit(*port, pin);
}
uint32 DIO_ReadPin(vulong32_ptr port, uint8 pin){
  return Get_Bit(*port,pin);
}
void DIO_WritePort(vulong32_ptr port, uint32 value) {
  *port = value;
}
void DIO_TogglePin(vulong32_ptr port,uint8 pin){
  Toggle_Bit(*port, pin)  ;
}