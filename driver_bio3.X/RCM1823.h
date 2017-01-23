#ifndef RCM_H
#define RCM_H

/* To use the Referense Clock Module (RCM) it is neccesary to add CLKOUTEN_OFF to config.  (Section 6.3.2 pag 74)*/

void start_RCM();
void stop_RCM();

#endif