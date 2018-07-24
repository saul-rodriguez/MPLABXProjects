/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16F1823
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/
#include <xc.h>
#include <stdio.h>
#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */

typedef enum 
{
 ADC_IDLE = 0,
 ADC_BUSY = 1
} adc_state;

void main(void)
{
    unsigned char data;
    unsigned short adc_val;
    char mess[9];
    unsigned long val_l;
    unsigned char ADC_state; // 0 idle, 1 conversion
    
    // initialize the device
    SYSTEM_Initialize();
    
    ADC_SelectChannel(channel_AN4);
    ADC_state = ADC_IDLE;

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
 //   data = 'a';
 //   EUSART_Write(data);
    
    
    //RXDTSEL = 0; //USART Rx on pin RC5
    //TXCKSEL = 0; //USART Tx on pin RC4
    
    
    
    while (1)
    {
        // Add your application code
        
        /*
        //Test of USART using interrupts. It echoes received bytes
        if(EUSART_is_rx_ready()) {
            data = EUSART_Read();          
          
            if(EUSART_is_tx_ready()) {
                EUSART_Write(data++);
            }
        }
        */
        
        // Process control commands 
        if(EUSART_is_rx_ready()) {
            data = EUSART_Read();          
          
            if(data == 'c') { //Read converter by polling the conversion flag
                
                //This code locks the thread until conversion is done
                adc_val = ADC_GetConversion(channel_AN4);
                                                
                /*
                // This code sends AN4 in binary format LSB first
                data = (unsigned char)(adc_val & 0xff);
            
                  
                if(EUSART_is_tx_ready()) {
                   EUSART_Write(data);
                }
            
                data = (unsigned char)((adc_val >> 8 ) & 0xff);
           
                if(EUSART_is_tx_ready()) {
                    EUSART_Write(data);
                } */
                
                // This code send AN4 digital value in text format 
               // sprintf(mess,"%u\n",adc_val);
                
                // This code converts AN4 to mV
                val_l = ((unsigned long)adc_val*3300UL/1024UL);   //VREF = VDD = 3.3V             
                sprintf(mess,"%u mV\n",val_l);
                
                data = 0;
                while(mess[data]) {
                    while(!EUSART_is_tx_ready()); // This will lock the thread until bytes in the tx buffer are available
                    
                    EUSART_Write(mess[data++]);
                }                
                  
            }    
            
            if (data == 'i') { // Activates the ADC interrupt
                if(ADC_state == ADC_IDLE) { // check if a conversion is already been triggered
                    ADC_StartConversion();
                    ADC_state = ADC_BUSY;
                }            
            }
        }
        
        if (ADC_state == ADC_BUSY) {
            if (ADC_IsConversionDone()) {
                ADC_state = ADC_IDLE;
                adc_val = ADC_GetConversionResult();   
                                            
                // This code converts AN4 to mV
                val_l = ((unsigned long)adc_val*3300UL/1024UL);   //VREF = VDD = 3.3V             
                sprintf(mess,"%u mV\n",val_l);
                
                data = 0;
                while(mess[data]) {
                    while(!EUSART_is_tx_ready()); // This will lock the thread until bytes in the tx buffer are available
                    
                    EUSART_Write(mess[data++]);
                }  
                
            }
        }
        
    }
}
/**
 End of File
*/