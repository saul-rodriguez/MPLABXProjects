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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16LF18426
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10	
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

// get/set CURRENT_OUT aliases
#define CURRENT_OUT_TRIS                 TRISCbits.TRISC2
#define CURRENT_OUT_LAT                  LATCbits.LATC2
#define CURRENT_OUT_PORT                 PORTCbits.RC2
#define CURRENT_OUT_WPU                  WPUCbits.WPUC2
#define CURRENT_OUT_OD                   ODCONCbits.ODCC2
#define CURRENT_OUT_ANS                  ANSELCbits.ANSC2
#define CURRENT_OUT_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define CURRENT_OUT_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define CURRENT_OUT_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define CURRENT_OUT_GetValue()           PORTCbits.RC2
#define CURRENT_OUT_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define CURRENT_OUT_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define CURRENT_OUT_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define CURRENT_OUT_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define CURRENT_OUT_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define CURRENT_OUT_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define CURRENT_OUT_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define CURRENT_OUT_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

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