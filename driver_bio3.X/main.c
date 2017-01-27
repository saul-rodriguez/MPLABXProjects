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
#include "comm.h"
#include "ADC1823.h"

void main(void) {
    
    unsigned char i;
    
    BIO3 mybits;
    VIN myVin;    
    
    SYSTEM_Initialize();
    setup_TMR0(); 
    start_TX_USART_ISR(); 
    start_RX_USART_ISR(); 
    start_RCM();
    setup_ADC();       
    
    RESET_BIO = 0;
    __delay_ms(250);
    RESET_BIO = 1;
    __delay_ms(250);
     
    //RESET_BIO = 0; // Hold the chip on reset
    
     while(1) {
                       
    
      //   __delay_ms(250);
          if (TIMER0_flag) { // Serial RX data received
              TIMER0_flag = 0;
              
              if (USART_rx_index > BUFF_SIZE) { // packet with wrong size, discard the data and continue                  
                USART_rx_index = 0;
                continue;
              }  
              
              if(USART_rx_index == 0) // catches possible faulty rx timemout
                  continue;
              
              //Rx packet is valid. Copy data from USART buffer and send it to the message handler
              mess_rec_size = USART_rx_index;
              
              for (i = 0; i < mess_rec_size; i++)
                  mess_rec[i] = USART_rx_data[i];
              
              //__delay_ms(50);  //Possible needed if harvester is used
              mess_handler();    
              //lputs_ISR(USART_rx_data,USART_rx_index);              
              
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
            __delay_ms(25);
            start_RX_USART_ISR();
        }
        return;
    }
    
}