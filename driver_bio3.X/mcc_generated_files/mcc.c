/**
  @Generated MPLAB(c) Code Configurator Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.16
        Device            :  PIC16LF1823
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

// Configuration bits: selected in the GUI

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection->INTOSC oscillator: I/O function on CLKIN pin
#pragma config WDTE = ON    // Watchdog Timer Enable->WDT disabled
#pragma config PWRTE = OFF    // Power-up Timer Enable->PWRT disabled
#pragma config MCLRE = ON    // MCLR Pin Function Select->MCLR/VPP pin function is MCLR
#pragma config CP = OFF    // Flash Program Memory Code Protection->Program memory code protection is disabled
#pragma config CPD = OFF    // Data Memory Code Protection->Data memory code protection is disabled
#pragma config BOREN = OFF    // Brown-out Reset Enable->Brown-out Reset disabled
#pragma config CLKOUTEN = OFF    // Clock Out Enable->CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin
#pragma config IESO = ON    // Internal/External Switchover->Internal/External Switchover mode is enabled
#pragma config FCMEN = OFF    // Fail-Safe Clock Monitor Enable->Fail-Safe Clock Monitor is disabled

// CONFIG2
#pragma config WRT = OFF    // Flash Memory Self-Write Protection->Write protection off
#pragma config PLLEN = OFF    // PLL Enable->4x PLL disabled
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable->Stack Overflow or Underflow will cause a Reset
#pragma config BORV = HI    // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (Vbor), high trip point selected.
#pragma config LVP = OFF    // Low-Voltage Programming Enable->High-voltage on MCLR/VPP must be used for programming

#include "mcc.h"
//#include "RCM1823.h"

void SYSTEM_Initialize(void)
{
    
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
  //  start_RCM();
}

void OSCILLATOR_Initialize(void)
{
    // SCS INTOSC; SPLLEN disabled; IRCF 500KHz_MF; 
    OSCCON = 0x3A;
    // LFIOFR disabled; HFIOFL not stable; OSTS intosc; PLLR disabled; HFIOFS not stable; HFIOFR disabled; MFIOFR disabled; T1OSCR disabled; 
    OSCSTAT = 0x00;
    // TUN 0; 
    OSCTUNE = 0x00;
    // Set the secondary oscillator
    
}

void USARTX_change_pol(void)
{
    SCKP = 1;   // Change polarity of TX pin (page 296)
}


/**
 End of File
*/
