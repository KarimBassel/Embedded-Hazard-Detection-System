#include "DIO.h"
#include "TM4c123gh6pm.h"
#include <stdio.h>
#include "Timer.h"
#include "Ultrasonic.h"
#include "Magnetic.h"
#include "Laser.h"
#include "Bluetooth.h"
volatile uint32 counter=0;
uint32 time; 
uint32 distance; 
char mesg[20];  
unsigned int adc_value;
int main()
{
  HC05_init();
  Laser_Init();
  Magnetic_Init();
  Smoke_init();
  Timer0ACapture_init();
  while(1){ 
    //Code for magnetic sensor
   if((DIO_ReadPin(&GPIO_PORTC_DATA_R ,6)) == 0x0){
    }
    else{
     Bluetooth_Write_String("Intrusion Detect\n");
     Detect_Magnet();
   }  
   // end code magnetic sensor
   // Ultrasonic sensor code
      time = Measure_distance();
      distance = (time * 10625)/10000000; 
      if (distance <20){
        Bluetooth_Write_String("Motion Detected\n");
        Detect_Motion();
      }
      sprintf(mesg, "\r\nDistance = %d cm", distance); 
      printstring(mesg); 
      Delay(2000);
      // end code ultrasonic sensor
      
      //smoke sensor code
      ADC0_PSSI_R |= (1<<3);       
        while((ADC0_RIS_R & 8) == 0) ;   
        adc_value = ADC0_SSFIFO3_R; 
        ADC0_ISC_R = 8;         
			
	if(adc_value >= 1500){
        Bluetooth_Write_String("Smoke Detected\n");
        Detect_Smoke(); 
        }
	else if(adc_value < 1500){
        sprintf(mesg, "\r\nFume = %d", adc_value);
        printstring(mesg); 
        }
        // end code smoke sensor
      
  }
  return 0;
}

