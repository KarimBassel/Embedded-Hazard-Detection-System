#include <math.h>
#include "TM4c123gh6pm.h"
#include "DIO.h"
#include "Keypad.h"

unsigned char Arr[5][4]={{'F' , 'G' ,'#', '*'}
,{'1','2','3','u'}
,{'4','5','6','d'}
,{'7','8','9','x'}
,{'l','0','r','e'}};

void Keypad_Init(){
  SYSCTL_RCGCGPIO_R |= 0x00000014;
  
  while ((SYSCTL_PRGPIO_R & 0x00000014) == 0) {};
  
  GPIO_PORTE_LOCK_R = 0x4C4F434B;
  GPIO_PORTC_LOCK_R = 0x4C4F434B;
  
  GPIO_PORTE_CR_R = 0x1F;
  GPIO_PORTC_CR_R = 0xF0;
  // PORT C 4 INPUTS FROM TIVA
  //PORT E 5 OUTPUTS TO TIVA
  GPIO_PORTE_DIR_R = 0x1F;
  GPIO_PORTC_DIR_R = 0x00;
  
  
  GPIO_PORTE_DEN_R = 0x1F;
  GPIO_PORTC_DEN_R = 0xF0;
  
  GPIO_PORTC_PDR_R = 0xF0;
  
  GPIO_PORTE_ODR_R = 0x1F;
}
unsigned char Keypad_Read(){
  for(int i=0;i<4;i++){
      GPIO_PORTC_DATA_R=pow(2,i);
      uint32 k= DIO_ReadPort(&GPIO_PORTE_DATA_R);
      switch(k){
      case 0: continue;
        break;
      case 1: k=0;
        break;
      case 2: k=1;
        break;
      case 4: k=2;
        break;
      case 8: k=3;
        break;
      case 16: k=4;
      break;
      }
      i--;
      return Arr[i][k];
  }
  
}