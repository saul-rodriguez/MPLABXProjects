/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
*/

/*
� [2025] Microchip Technology Inc. and its subsidiaries.

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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RB5 aliases
#define LED_TRIS                 TRISBbits.TRISB5
#define LED_LAT                  LATBbits.LATB5
#define LED_PORT                 PORTBbits.RB5
#define LED_WPU                  WPUBbits.WPUB5
#define LED_OD                   ODCONBbits.ODCB5
#define LED_ANS                  ANSELBbits.ANSB5
#define LED_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define LED_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define LED_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define LED_GetValue()           PORTBbits.RB5
#define LED_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define LED_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define LED_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define LED_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define LED_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define LED_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)
// get/set IO_RC2 aliases
#define CS_TRIS                 TRISCbits.TRISC2
#define CS_LAT                  LATCbits.LATC2
#define CS_PORT                 PORTCbits.RC2
#define CS_WPU                  WPUCbits.WPUC2
#define CS_OD                   ODCONCbits.ODCC2
#define CS_ANS                  ANSELCbits.ANSC2
#define CS_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define CS_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define CS_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define CS_GetValue()           PORTCbits.RC2
#define CS_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define CS_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define CS_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define CS_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define CS_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define CS_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define CS_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define CS_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)
// get/set IO_RC3 aliases
#define IO_RC3_TRIS                 TRISCbits.TRISC3
#define IO_RC3_LAT                  LATCbits.LATC3
#define IO_RC3_PORT                 PORTCbits.RC3
#define IO_RC3_WPU                  WPUCbits.WPUC3
#define IO_RC3_OD                   ODCONCbits.ODCC3
#define IO_RC3_ANS                  ANSELCbits.ANSC3
#define IO_RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define IO_RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define IO_RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define IO_RC3_GetValue()           PORTCbits.RC3
#define IO_RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define IO_RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define IO_RC3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define IO_RC3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define IO_RC3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define IO_RC3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define IO_RC3_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define IO_RC3_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)
// get/set IO_RC4 aliases
#define IO_RC4_TRIS                 TRISCbits.TRISC4
#define IO_RC4_LAT                  LATCbits.LATC4
#define IO_RC4_PORT                 PORTCbits.RC4
#define IO_RC4_WPU                  WPUCbits.WPUC4
#define IO_RC4_OD                   ODCONCbits.ODCC4
#define IO_RC4_ANS                  ANSELCbits.ANSC4
#define IO_RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define IO_RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define IO_RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define IO_RC4_GetValue()           PORTCbits.RC4
#define IO_RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define IO_RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define IO_RC4_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define IO_RC4_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define IO_RC4_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define IO_RC4_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define IO_RC4_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define IO_RC4_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)
// get/set IO_RC5 aliases
#define IO_RC5_TRIS                 TRISCbits.TRISC5
#define IO_RC5_LAT                  LATCbits.LATC5
#define IO_RC5_PORT                 PORTCbits.RC5
#define IO_RC5_WPU                  WPUCbits.WPUC5
#define IO_RC5_OD                   ODCONCbits.ODCC5
#define IO_RC5_ANS                  ANSELCbits.ANSC5
#define IO_RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define IO_RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define IO_RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define IO_RC5_GetValue()           PORTCbits.RC5
#define IO_RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define IO_RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define IO_RC5_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define IO_RC5_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define IO_RC5_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define IO_RC5_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define IO_RC5_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define IO_RC5_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/