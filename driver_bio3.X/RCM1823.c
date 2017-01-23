#include "RCM1823.h"
#include <xc.h>

void start_RCM() {
    //CLKRCON = 0b11110000;  // CLKR module enabled, Output pin enabled, SR enabled, 50% duty cycle, base clock (page 74)
    CLKRCON = 0b11010000;  // CLKR module enabled, Output pin enabled, SR DISABLED!, 50% duty cycle, base clock (page 74)
}

void stop_RCM() {
    CLKRCON = 0b00110000; // CLKR module disabled, Output pin disabled
}