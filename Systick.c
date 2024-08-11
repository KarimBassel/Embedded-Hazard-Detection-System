#include "Systick.h"
#include "TM4c123gh6pm.h"


void SysTickDisable(void){
   NVIC_ST_CTRL_R = 0x0;
}
void SysTickEnable(void){
  NVIC_ST_CTRL_R = 0x5;
}
void EnableSysTickInt(){
  NVIC_ST_CTRL_R |= 0x2;
}
void SysTickPeriodSet(float32 ui32Period)
{ 
  ui32Period/=1000;
  NVIC_ST_RELOAD_R = ui32Period*16000000;
}
uint32 SysTickPeriodGet(void){
  return ((NVIC_ST_RELOAD_R/16000000)*1000);
}
uint32 SysTickValueGet(void){
  return NVIC_ST_CURRENT_R ;
}
int SysTick_Is_Time_out(void){
  if(((NVIC_ST_CTRL_R & 0x10000) == 0x10000)){
    return 1;
  }
  else{
    return 0;
  }
}