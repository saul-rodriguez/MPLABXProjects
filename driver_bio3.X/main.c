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
    VIN myVin;
    
    
    
    SYSTEM_Initialize();
       
    
    RESET_BIO = 0;
    __delay_ms(250);
    RESET_BIO = 1;
    __delay_ms(250);
     
     while(1) {   
                 
         
         mybits.data = 0xF055;
         BIO_config(mybits);    
         
       //  myVin.data[0] = 0xCCAA;
       //  myVin.data[1] = 0x55FF;
       //  myVin.data[2] = 0x00F1;
       //  VIN_config(myVin);
         
         __delay_ms(250);
         
         mybits.data = 0xAA0F;
         BIO_config(mybits);         
         //VIN_config(myVin);
         __delay_ms(250);
     }
}
