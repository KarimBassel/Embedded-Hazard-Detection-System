#include "types.h"
#include <stdio.h>

void SysTickDisable(void);
void SysTickEnable(void);
uint32 SysTickPeriodGet(void);
void SysTickPeriodSet(float32 ui32Period);
uint32 SysTickValueGet(void);
int SysTick_Is_Time_out(void);
void EnableSysTickInt();
