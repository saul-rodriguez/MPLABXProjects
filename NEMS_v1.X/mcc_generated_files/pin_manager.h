/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.0
        Device            :  PIC16LF18426
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.35	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 procedures
#define RA0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define RA0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define RA0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define RA0_GetValue()              PORTAbits.RA0
#define RA0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define RA0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define RA0_SetPullup()             do { WPUAbits.WPUA0 = 1; } while(0)
#define RA0_ResetPullup()           do { WPUAbits.WPUA0 = 0; } while(0)
#define RA0_SetAnalogMode()         do { ANSELAbits.ANSA0 = 1; } while(0)
#define RA0_SetDigitalMode()        do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set LED aliases
#define LED_TRIS                 TRISAbits.TRISA5
#define LED_LAT                  LATAbits.LATA5
#define LED_PORT                 PORTAbits.RA5
#define LED_WPU                  WPUAbits.WPUA5
#define LED_OD                   ODCONAbits.ODCA5
#define LED_ANS                  ANSELAbits.ANSA5
#define LED_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define LED_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define LED_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define LED_GetValue()           PORTAbits.RA5
#define LED_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define LED_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define LED_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define LED_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define LED_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define LED_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set NMES_PLUS aliases
#define NMES_PLUS_TRIS                 TRISCbits.TRISC1
#define NMES_PLUS_LAT                  LATCbits.LATC1
#define NMES_PLUS_PORT                 PORTCbits.RC1
#define NMES_PLUS_WPU                  WPUCbits.WPUC1
#define NMES_PLUS_OD                   ODCONCbits.ODCC1
#define NMES_PLUS_ANS                  ANSELCbits.ANSC1
#define NMES_PLUS_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define NMES_PLUS_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define NMES_PLUS_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define NMES_PLUS_GetValue()           PORTCbits.RC1
#define NMES_PLUS_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define NMES_PLUS_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define NMES_PLUS_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define NMES_PLUS_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define NMES_PLUS_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define NMES_PLUS_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define NMES_PLUS_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define NMES_PLUS_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set NMES_MINUS aliases
#define NMES_MINUS_TRIS                 TRISCbits.TRISC2
#define NMES_MINUS_LAT                  LATCbits.LATC2
#define NMES_MINUS_PORT                 PORTCbits.RC2
#define NMES_MINUS_WPU                  WPUCbits.WPUC2
#define NMES_MINUS_OD                   ODCONCbits.ODCC2
#define NMES_MINUS_ANS                  ANSELCbits.ANSC2
#define NMES_MINUS_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define NMES_MINUS_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define NMES_MINUS_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define NMES_MINUS_GetValue()           PORTCbits.RC2
#define NMES_MINUS_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define NMES_MINUS_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define NMES_MINUS_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define NMES_MINUS_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define NMES_MINUS_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define NMES_MINUS_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define NMES_MINUS_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define NMES_MINUS_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/