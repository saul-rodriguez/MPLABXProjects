/*
 * File:   main.c
 * Author: saul
 *
 * Created on September 15, 2016, 3:22 PM
 * 
 * CONFIGURATION:
 * 
 * - To select between BIO_ASIC and VIN_ASIC, comment/uncomment one of the following lines in bio3.h
 * //#define BIOASIC
*  //#define VINASIC  
 * 
 * - if inductive coupling is used for power and communications (only BIO_ASIC) uncomment the following line in in comm.h
 * //#define INDUCTIVE_POW 
 * 

 */
#include "mcc_generated_files/mcc.h"

#include <xc.h>
#include "bio3.h"
#include "RCM1823.h"
#include "TMR0.h"
#include "USART1823.h"
#include "comm.h"
#include "ADC1823.h"

void main(void) {
    
    unsigned char i;
    
    SYSTEM_Initialize();
    #ifdef INDUCTIVE_POW
        USARTX_change_pol();
    #endif
    setup_TMR0(); 
    start_TX_USART_ISR(); 
    start_RX_USART_ISR(); 
    start_RCM();
    setup_ADC();       
    
    
    RESET_BIO = 0;
    __delay_ms(150);
    RESET_BIO = 1;
   
    //TEST FOR SIMULATION
 //   sweep();
    
    //TEST USART INDUCTIVE STARTS HERE
    
    //TEST SIMPLE TX SUCCESSFUL
    /*
   i = 'a';
   while(1) {
       CLRWDT();
       __delay_ms(250);
       putch(i);
       i++;       
   } */
    
    /*
    //TEST TX TO CALIBRATE READER
    i = 0;
    mess_rec[0] = 'h';
    mess_rec[1] = 'o';
    mess_rec[2] = 'l';
    mess_rec[3] = 'a';
    mess_rec[4] = 0x00;
    mess_rec[5] = 0xaa;
    mess_rec[6] = 0xfe;
    mess_rec[7] = '@';
    
    while (1) {
        CLRWDT();
         __delay_ms(250);
         lputs_ISR(mess_rec,8);
        
    }
    */
    
    //TEST TX AND RX 
    /*
    i = 0;    
    while(1) {
       CLRWDT();
       
       if (TIMER0_flag) { // Serial RX data received
           TIMER0_flag = 0;
              
            if (USART_rx_index > BUFF_SIZE) { // packet with wrong size, discard the data and continue                  
                USART_rx_index = 0;
                continue;
            }  
              
            if(USART_rx_index == 0) // catches possible faulty rx timemout
                continue;       
           
            mess_rec_size = USART_rx_index;
            USART_rx_index = 0;
            
                 
            for (i = 0; i < mess_rec_size; i++)
               mess_rec[i] = USART_rx_data[i];  
            
            __delay_ms(250);
            lputs_ISR(mess_rec,mess_rec_size);
               
       } 
       
    } 
    */
    
    //TEST USART INDUCTIVE STOPS HERE
        
      
     while(1) {
           CLRWDT();       
    
  
          if (TIMER0_flag) { // Serial RX data received
              TIMER0_flag = 0;
              
              if (USART_rx_index > BUFF_SIZE) { // packet with wrong size, discard the data and continue                  
                USART_rx_index = 0;
                continue;
              }  
              
              if(USART_rx_index == 0) // catches possible faulty rx timemout
                  continue;
              
              //Rx packet is valid. Copy data from USART buffer, reset USART_rx_index, and send it to the message handler
              mess_rec_size = USART_rx_index;
              USART_rx_index = 0;              
              
              for (i = 0; i < mess_rec_size; i++)
                  mess_rec[i] = USART_rx_data[i];
              
              //__delay_ms(50);  //Possible needed if harvester is used            
              mess_handler();                  
              
          }
                 
     }
     
        
}


void interrupt isr(void)
{

     //TMR0 ISRservice routine
    if (TMR0IF && TMR0IE) { //Important to && TMR0IE since TMR0IF may be set!

        TMR0IF = 0;  //Reset interrupt flag
        TMR0 = TIMER0_timeout;  // re-load timer register

        // Flag the event
        TIMER0_flag = 1;
        // The TMR0 is attached to the USART, so the USART_rx_flag is used
        //USART_rx_flag = RX_RECEIVED;
        
        // Stop the timer
        stop_TMR0_ISR();

        return;
    }
  

    //USART RX ISR routine
    if (RCIF) {
        stop_TMR0_ISR();
        
        //Reset the RX usart if an overrun error is detected
       if (OERR) {           
            
            CREN = 0;
            CREN = 1;
            USART_rx_index = 0;
            return;
        }
      
        //USART_rx_flag = RX_RECEIVED;
        if (USART_rx_index >= RX_BUF_SIZE) { //  buffer overflow. Reset the index
            USART_rx_index = 0;
        }
    
        USART_rx_data[USART_rx_index++] = RCREG;

        start_TMR0_ISR(98); // 98 -> Start timer0, timeout in 10ms (500kHz oscillator freq)
        
        return;
    }


    //USART RX ISR routine
    if (TXIF && TXIE) { //TXIF IS ALWAYS 1 when txbuf is empty!!!!!!
        //USART_tx_isr;
        TXREG = USART_tx_data[USART_tx_index++];

        if (USART_tx_index >= USART_tx_length) {
            TXIE = 0;
            USART_tx_flag = TX_FREE;

            //Uncomment these lines if re-enabling of Rx circuitry is needed
            //#ifdef INDUCTIVE_POW
            __delay_ms(3);
          //#endif            
            start_RX_USART_ISR();
        }
        return;
    }
    
}