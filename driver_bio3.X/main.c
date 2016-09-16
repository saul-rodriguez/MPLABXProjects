/*
 * File:   main.c
 * Author: saul
 *
 * Created on September 15, 2016, 3:22 PM
 */
#include "mcc_generated_files/mcc.h"

#include <xc.h>
#include "bio3.h"

void main(void) {
    
    BIO3 mybits;
    
    
    
    SYSTEM_Initialize();
       
    
    DATA = 0;
    __delay_ms(250);
    DATA = 1;
    __delay_ms(250);
     
     while(1) {   
                 
         
         mybits.data = 0xF055;
         BIO_config((unsigned long)mybits.data,BIO3_LENGTH);         
         __delay_ms(250);
         
         mybits.data = 0xAA0F;
         BIO_config((unsigned long)mybits.data,BIO3_LENGTH);         
         __delay_ms(250);
     }
}
