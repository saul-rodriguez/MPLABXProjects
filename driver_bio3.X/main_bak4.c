/*
 * File:   main.c
 * Author: saul
 *
 * Created on September 15, 2016, 3:22 PM
 */
#include "mcc_generated_files/mcc.h"

#include <xc.h>
#include "bio3.h"
#include "RCM1823.h"
#include "TMR0.h"
#include "USART1823.h"

void main(void) {
    
    BIO3 mybits;
    VIN myVin;
         
    unsigned short i;
    
    SYSTEM_Initialize();
    start_RCM();
           
    RESET_BIO = 0;
    __delay_ms(250);
    RESET_BIO = 1;
    __delay_ms(250);
     
    //RESET_BIO = 0; // Hold the chip on reset
    
    
    
     // IMPLANTABLE TEST
    /*
         mybits.datashort = 0x0000;
         
         mybits.data_bits.F3 = 0;
         mybits.data_bits.F2 = 0;
         mybits.data_bits.F1 = 0;
         mybits.data_bits.F0 = 0;
         
         mybits.data_bits.IQ = 0; //I ref
         mybits.data_bits.NS = 0; //32 steps         
         mybits.data_bits.CE = 1; //Enable signal generator
         
         mybits.data_bits.GS3 = 1;
         mybits.data_bits.GS2 = 1;
         mybits.data_bits.GS1 = 1;
         mybits.data_bits.GS0 = 1;
         
         mybits.data_bits.GD2 = 1;
         mybits.data_bits.GD1 = 0;
         mybits.data_bits.GD0 = 0;    
         
       // mybits.datashort = 0xA7CC; 
        BIO_config(mybits);    
      */
    
    
         myVin.datas[0] = 0x0000;
         myVin.datas[1] = 0x0000;
         myVin.datas[2] = 0x0000;
        // myVin.data[3] = 0x00;
        // myVin.data[4] = 0x00;
         
         //IQ options
         myVin.data_bits.F3 = 1;
         myVin.data_bits.F2 = 0;
         myVin.data_bits.F1 = 1;
         myVin.data_bits.F0 = 0;
         
         myVin.data_bits.IQ = 0; //I ref
         myVin.data_bits.NS = 0; //32 steps         
         myVin.data_bits.CE = 1; //Enable signal generator
         
         myVin.data_bits.GS3 = 1;
         myVin.data_bits.GS2 = 1;
         myVin.data_bits.GS1 = 1;
         myVin.data_bits.GS0 = 1;
         
         myVin.data_bits.GD2 = 1;
         myVin.data_bits.GD1 = 0;
         myVin.data_bits.GD0 = 0;    
    
         //Filter options
         
         myVin.data_bits.EnLF = 0;
         myVin.data_bits.EnMF = 0;
         myVin.data_bits.EnHF = 1;
         
         myVin.data_bits.DN1 = 0;
         myVin.data_bits.DN0 = 0;
         
         myVin.data_bits.DP2 = 0;
         myVin.data_bits.DP1 = 0;
         myVin.data_bits.DP0 = 0;
         
         myVin.data_bits.EnRdeg = 0;
         myVin.data_bits.EnRdegHF1 = 1;
         myVin.data_bits.EnRdegHF0 = 1;
         
         myVin.data_bits.CcompSel1 = 0;
         myVin.data_bits.CcompSel0 = 0;
         
         myVin.data_bits.CapSel3 = 0;
         myVin.data_bits.CapSel2 = 0;
         myVin.data_bits.CapSel1 = 1;
         myVin.data_bits.CapSel0 = 1;
      
         //myVin.datas[0] = 0xAAF3;
         //myVin.datas[1] = 0x55C3;         
         //myVin.datas[2] = 0x0001;
                          
         
         VIN_config(myVin);
              
         i = 0;
     while(1) {   
   /*
         i++;
    RESET_BIO = 0;
    __delay_ms(100);
    RESET_BIO = 1;
    __delay_ms(100);   
     */   
        
         
       //  myVin.data[0] = 0xCCAA;
       //  myVin.data[1] = 0x55FF;
       //  myVin.data[2] = 0x0001;
        /// VIN_config(myVin);
         
      //   __delay_ms(2);
         
         //mybits.datashort = 0xCCF0;
         //BIO_config(mybits);         
         //VIN_config(myVin);
         //__delay_ms(250);
         //__delay_ms(250);
         //__delay_ms(250);
         //__delay_ms(250);
         //__delay_ms(250);
     }
}
