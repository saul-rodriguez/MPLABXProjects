#include <xc.h>

volatile unsigned char TIMER0_flag;
volatile unsigned short TIMER0_timeout;

/*
 * The TIMER0 has a clock_timer0 configured at a frec = (Focs/4)*(prescaler 1/ X)
 * The TIMER0 trigger the flag after counting (255 - val) clock_timer0 cycles
 */
void setup_TMR0()
{
 //   PS2 = 1;    PS1 = 1;    PS0 = 1;    //Prescaler 1:256
    PS2 = 0;    PS1 = 1;    PS0 = 0;    //Prescaler 1:8 (val = 98 for Focs = 500K, and 10ms timer)
    //PS2 = 0;    PS1 = 0;    PS0 = 1;    //Prescaler 1:4
    //PS2 = 0;    PS1 = 0;    PS0 = 0;    //Prescaler 1:2
    PSA = 0; //Prescaler assigned to Timer0
    //PSA = 1; //Prescaler NOT assigned to Timer0
    TMR0CS = 0; // Internal clock cycle (Fosc/4)
}

void run_TMR0(unsigned char val)
{

    TMR0IF = 0;
    TMR0 = val;
    while(!TMR0IF);

}

void start_TMR0_ISR(unsigned char val)
{
    TIMER0_timeout = val;
    TIMER0_flag = 0;

  
    TMR0 = TIMER0_timeout;

    //Enable the interrupts
    TMR0IF = 0;
    TMR0IE = 1;
    GIE = 1;
}

void stop_TMR0_ISR(void)
{
    //Disable the interrupt
    TMR0IE = 0;    
    TMR0IF = 0;
}

//TMR0 ISR service routine that needs to be added in the interrupt function:
/*
    if (TMR0IF) {

        TMR0IF = 0;  //Reset interrupt flag
        TMR0 = TIMER0_timeout;  // re-load timer register

        // Flag the event
        TIMER0_flag = 1;

        return;
    }

 */


