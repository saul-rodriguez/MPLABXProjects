/*
 * File:   main.c
 * Author: saul
 *
 * Created on September 15, 2016, 3:22 PM
 */
#include "mcc_generated_files/mcc.h"
#include "ADC1823.h"

#include <xc.h>


void main(void) {
    
    unsigned short adc;
    unsigned char del;    
    
    SYSTEM_Initialize();
    setup_ADC();
        
    
    LED = 0;
    __delay_ms(250);
    LED = 1;
    __delay_ms(250);
     
     while(1) {   
          LED = 0;
          __delay_ms(250);
          __delay_ms(250);
          LED = 1;
          __delay_ms(250);
          __delay_ms(250);
         
     }
         //adc = ADC_2();                    
         //adc = ADC_4();           

      //   adc = ADC_5(); 
      //   del = adc >> 2;
         
        /* 
         LED = 0;
         for (int i = 0; i < del; i++)
            __delay_ms(1);
         
         
         LED = 1;
         for (int i = 0; i < del; i++)
            __delay_ms(1);
     
         */
         
         
}
