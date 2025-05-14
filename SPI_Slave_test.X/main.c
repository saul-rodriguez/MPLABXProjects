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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F18456
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
#include "aska.h"
/*
                         Main application
 */


/*

void ASKA_write_reg(uint8_t IC_addr ,uint8_t add, uint32_t value)
{
    uint8_t tx_buffer[5];
	
    tx_buffer[0] = add | IC_addr;
    
    tx_buffer[1] = (uint8_t)(value >> 24) & 0xff;
    tx_buffer[2] = (uint8_t)(value >> 16) & 0xff;
    tx_buffer[3] = (uint8_t)(value >> 8) & 0xff;
    tx_buffer[4] = (uint8_t)(value >> 0) & 0xff;

	//SPI_transaction(tx_buffer,5);
    CS_SetLow();    
    SPI1_WriteBlock(tx_buffer,5);
    CS_SetHigh();

}

*/

void main(void)
{
    unsigned char data;
    
    uint8_t ic_add;
    uint32_t tx_data;
    
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    //SPI
    CS_SetHigh();
    SPI1_Open(SPI1_DEFAULT);

    data = 0;
    
    
    
    //tx_data = 0xaaf0cc77;
    
    CS_SetLow();
    __delay_ms(100);
    CS_SetHigh();
    
    
    //Reset all ICs
    ASKA_write_reg(IC_ADDRESS_0, ASKA_CONF1,0x00000000); 
    ASKA_write_reg(IC_ADDRESS_1, ASKA_CONF1,0x00000000); 
    ASKA_write_reg(IC_ADDRESS_2, ASKA_CONF1,0x00000000); 
    ASKA_write_reg(IC_ADDRESS_3, ASKA_CONF1,0x00000000); 
    
    ic_add = IC_ADDRESS_0;
    
    while (1)
    {
        // Add your application code
        LED_SetLow();
        __delay_ms(100);
        LED_SetHigh();
        
        
        ASKA_test1(ic_add);
        __delay_ms(20000);
        ASKA_test2(ic_add);
        __delay_ms(20000);
        ASKA_test3(ic_add);
        __delay_ms(20000);
        ASKA_test4(ic_add);
        __delay_ms(20000);
        
    }
}
/**
 End of File
*/