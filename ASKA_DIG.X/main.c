 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "aska.h"

/*
    Main application
*/

int main(void)
{
    unsigned char data;
    
    uint8_t ic_add;
    uint32_t tx_data;
       
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    //INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 

    //SPI
    CS_SetHigh();
    
    SPI1_Open(HOST_CONFIG);

    data = 0;
    
    LED_SetLow();
    __delay_ms(250);
    LED_SetHigh();
    
    
    //Reset all ICs
    ASKA_write_reg(IC_ADDRESS_0, ASKA_CONF1,0x00000000); 
    ASKA_write_reg(IC_ADDRESS_1, ASKA_CONF1,0x00000000); 
    ASKA_write_reg(IC_ADDRESS_2, ASKA_CONF1,0x00000000); 
    ASKA_write_reg(IC_ADDRESS_3, ASKA_CONF1,0x00000000); 
    
    ic_add = IC_ADDRESS_0;
    
    while(1)
    {
        
   // ASKA_write_reg(IC_ADDRESS_3, ASKA_CONF0, 0xaabbccdd);    
   // __delay_ms(10);
        
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