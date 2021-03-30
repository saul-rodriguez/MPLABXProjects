/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>
#include "mcc_generated_files/mcc.h"



// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star

// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#define NEMS_TIMER_FREQUENCY 20000
#define SILENCE_PERIOD 1    // 1 CYCKE if NEMS_TIMER_FREQUENCY
    
typedef struct {
    unsigned char amplitude;  // [mA] 1 mA - 31 mA or higher (pp. 31, Chap 3)
    unsigned char amplitude2;
    unsigned char frequency;  // [Hz] 15 - 50 (pp. 32, Chap 3))
    unsigned char phase_duration; // [us/50] ( 200us - 400us --> 4 - 8) (pp. 83, Chap 6)
    unsigned char symmetry_factor; // symmetric = 1, asymmetric = phase_negative/ phase_duration = [2,4,8]
    unsigned char ON_time;  // [s] 2s-4s (pp. 86, Chap 6) ON/OFF ~ 4:12, 1:3 
    unsigned char OFF_time; // [s] ON/OFF 1/3 to 1/5  over 10-15 contractions
    unsigned char contractions; // number of contractions depends on the program's total time (Total time/(ON_time+OFF_time))
    unsigned char ramp_up; // [ds] depends on the muscle and exercise, typically below 2s.(pp. 89, Chap 6)
    unsigned char ramp_down; // [ds]
    unsigned char channel1;
    unsigned char channel2;
    unsigned char channel3;
    unsigned char channel4;
} NEMS_program;

extern volatile NEMS_program program;

typedef struct {
    unsigned short num_clocks_per_pulse; //number clock cycles before a pulse is sent    
    unsigned short clock_index; // clock counter 
    unsigned short pulse_index;  // pulse index
    unsigned short current_pulse_index;
    
    unsigned char  silence_phase_duration;
    unsigned char  minus_phase_duration;
    unsigned short ON_time; // Number of pulses during ON_time    
    unsigned short OFF_time; // Number of ulses during OFF_time
    
    unsigned char program_amplitude;
    unsigned char pulse_amplitude;
    unsigned char symmetry_divider;
    unsigned char current_amplitude; // current used amplitude
    
    unsigned char program_amplitude2;
    unsigned char pulse_amplitude2;
    
    unsigned char ramp_up_amplitude[100];
    unsigned char ramp_up_amplitude2[100];
    unsigned short ramp_up_pulses; //Number of pulses for ramp up
    unsigned short ramp_up_time;
    
    unsigned char ramp_down_amplitude[100];
    unsigned char ramp_down_amplitude2[100];
    unsigned short ramp_down_pulses; //Number of pulses for ramp down
    unsigned short ramp_down_time;
  
    unsigned char ramp_index;
    unsigned char contractions_index;
    
    unsigned char channel1;
    unsigned char channel2;
    
    unsigned char channel3;
    unsigned char channel4;
    
   
    
} NEMS_waveform;

extern volatile NEMS_waveform waveform;

typedef enum {
    NEMS_DISABLED,
    NEMS_ENABLED    
} NEMS_state;

extern volatile NEMS_state NEMS_states;

typedef enum {
    NEMS_ON_TIME,
    NEMS_OFF_TIME    
} NEMS_wave_state;

extern volatile NEMS_wave_state NEMS_wave_states;
  
typedef enum {
    NEMS_PULSE_OFF = 0b00000000,
    NEMS_PLUS_UP = 0b00000010,  
    NEMS_REST = 0b00000001,
    NEMS_MINUS_UP = 0b0000100
} NEMS_pulse_state;

extern volatile NEMS_pulse_state NEMS_pulse_states;

extern const unsigned char mux[17]; 
//extern const unsigned char pmux[16]; 

void NEMS_initialize(void);
void NEMS_message_handler(void);

unsigned char NEMS_get_packet(unsigned char* pt);
void NEMS_set_amplitude(void);
void NEMS_set_amplitude2(void);
void NEMS_set_frequency(void);
void NEMS_set_phase_duration(void);
void NEMS_set_symmetry_factor(void);
void NEMS_set_ON_time(void);
void NEMS_set_OFF_time(void);
void NEMS_set_contractions(void);
void NEMS_set_ramp_up(void);
void NEMS_set_ramp_down(void);
void NEMS_set_channel1(void);
void NEMS_set_channel2(void);
void NEMS_set_channel3(void);
void NEMS_set_channel4(void);


void NEMS_get_program(void);
void NEMS_save_program(void);
void NEMS_load_program(void);
void NEMS_recalculate_program(void);
void NEMS_calculate_ramp(void);

void NEMS_start_program(void);
void NEMS_stop_program(void);

void NEMS_timer(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

