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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16LF18456
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
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

// get/set LED aliases
#define LED_TRIS                 TRISAbits.TRISA0
#define LED_LAT                  LATAbits.LATA0
#define LED_PORT                 PORTAbits.RA0
#define LED_WPU                  WPUAbits.WPUA0
#define LED_OD                   ODCONAbits.ODCA0
#define LED_ANS                  ANSELAbits.ANSA0
#define LED_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define LED_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define LED_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define LED_GetValue()           PORTAbits.RA0
#define LED_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define LED_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define LED_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define LED_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define LED_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define LED_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set VOUT_SE aliases
#define VOUT_SE_TRIS                 TRISCbits.TRISC0
#define VOUT_SE_LAT                  LATCbits.LATC0
#define VOUT_SE_PORT                 PORTCbits.RC0
#define VOUT_SE_WPU                  WPUCbits.WPUC0
#define VOUT_SE_OD                   ODCONCbits.ODCC0
#define VOUT_SE_ANS                  ANSELCbits.ANSC0
#define VOUT_SE_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define VOUT_SE_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define VOUT_SE_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define VOUT_SE_GetValue()           PORTCbits.RC0
#define VOUT_SE_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define VOUT_SE_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define VOUT_SE_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define VOUT_SE_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define VOUT_SE_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define VOUT_SE_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define VOUT_SE_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define VOUT_SE_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set CFG_CLK aliases
#define CFG_CLK_TRIS                 TRISCbits.TRISC1
#define CFG_CLK_LAT                  LATCbits.LATC1
#define CFG_CLK_PORT                 PORTCbits.RC1
#define CFG_CLK_WPU                  WPUCbits.WPUC1
#define CFG_CLK_OD                   ODCONCbits.ODCC1
#define CFG_CLK_ANS                  ANSELCbits.ANSC1
#define CFG_CLK_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define CFG_CLK_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define CFG_CLK_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define CFG_CLK_GetValue()           PORTCbits.RC1
#define CFG_CLK_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define CFG_CLK_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define CFG_CLK_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define CFG_CLK_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define CFG_CLK_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define CFG_CLK_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define CFG_CLK_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define CFG_CLK_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set CFG_DAT aliases
#define CFG_DAT_TRIS                 TRISCbits.TRISC2
#define CFG_DAT_LAT                  LATCbits.LATC2
#define CFG_DAT_PORT                 PORTCbits.RC2
#define CFG_DAT_WPU                  WPUCbits.WPUC2
#define CFG_DAT_OD                   ODCONCbits.ODCC2
#define CFG_DAT_ANS                  ANSELCbits.ANSC2
#define CFG_DAT_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define CFG_DAT_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define CFG_DAT_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define CFG_DAT_GetValue()           PORTCbits.RC2
#define CFG_DAT_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define CFG_DAT_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define CFG_DAT_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define CFG_DAT_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define CFG_DAT_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define CFG_DAT_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define CFG_DAT_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define CFG_DAT_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set CFG_RES aliases
#define CFG_RES_TRIS                 TRISCbits.TRISC3
#define CFG_RES_LAT                  LATCbits.LATC3
#define CFG_RES_PORT                 PORTCbits.RC3
#define CFG_RES_WPU                  WPUCbits.WPUC3
#define CFG_RES_OD                   ODCONCbits.ODCC3
#define CFG_RES_ANS                  ANSELCbits.ANSC3
#define CFG_RES_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define CFG_RES_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define CFG_RES_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define CFG_RES_GetValue()           PORTCbits.RC3
#define CFG_RES_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define CFG_RES_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define CFG_RES_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define CFG_RES_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define CFG_RES_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define CFG_RES_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define CFG_RES_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define CFG_RES_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

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

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

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