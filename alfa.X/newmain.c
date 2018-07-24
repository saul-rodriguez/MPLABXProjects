/*
 * File:   newmain.c
 * Author: saul
 *
 * Created on July 23, 2018, 12:04 PM
 */


#include <xc.h>

void __interrupt() myIsr(void)
{
// only process timer-triggered interrupts
if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
    INTCONbits.TMR0IF = 0; // clear this interrupt condition
    }
}

void main(void) {
    return;
}
