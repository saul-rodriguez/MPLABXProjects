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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16LF18456
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

#include "mcc_generated_files/mcc.h"
#include "bio3.h"
#include "tester.h"

/*
                         Main application
 */
void main(void)
{
    unsigned char aux;
    VIN asic;
    
    // initialize the device
    SYSTEM_Initialize();

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

    aux = 0;
    
     // Add your application code
    
    //Reset ASIC
    CFG_RES_SetLow();
    __delay_ms(150);
    CFG_RES_SetHigh();
    
    //Start up hello
    LED_SetHigh();        
    __delay_ms(200);
    LED_SetLow();
    
    //config asic to lowest gain, lowest freq, setup filter
    tester_initialize();
    
    //TEST SERIAL
    /*
    while (1)
    {
        if(EUSART1_is_rx_ready()) {
            aux = EUSART1_Read();
            
            EUSART1_Write(aux);
            
            LED_SetHigh();        
            __delay_ms(200);
            LED_SetLow();
            __delay_ms(200);
        }       
    }
     */
    
    //TEST Config ASIC
    /*
    asic.data[0] = 0xaa;
    asic.data[1] = 0xc0;
    asic.data[2] = 0x55;
    asic.data[3] = 0x03;
    asic.data[3] = 0x01;
    
    
    while (1) {
        
        config(asic);
        __delay_ms(10);
    }
    */
    
    while (1) {
        CLRWDT();
        if(EUSART1_is_rx_ready()) {
            mess_handler();
        }
    }
    
}
/**
 End of File
*/