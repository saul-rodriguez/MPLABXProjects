#ifndef TMR0_H
#define TMR0_H

void setup_TMR0(void);
void run_TMR0(unsigned char val);
void start_TMR0_ISR(unsigned char val);
void stop_TMR0_ISR(void);

extern volatile unsigned char TIMER0_flag;
extern volatile unsigned short TIMER0_timeout;

#endif

