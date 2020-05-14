#include "NEMS.h"
#include "comm.h"
#include "mcc_generated_files/tmr0.h"

//Program settings

volatile NEMS_program program;
volatile NEMS_waveform waveform;

volatile NEMS_state NEMS_states;
volatile NEMS_wave_state NEMS_wave_states;
volatile NEMS_pulse_state NEMS_pulse_states;

void NEMS_initialize(void)
{
    //Stop TMR0
    TMR0_StopTimer();
           
    
    //Only for testing purposes
    program.amplitude = 1;
    program.frequency = 35;
    program.phase_duration = 1;
    program.ON_time = 2;
    program.OFF_time = 6;
    program.contractions = 5;
    program.ramp_up = 10;
    program.ramp_down = 10;
    program.symmetry_factor = 1;
    
    //Clear all program variables
    /*
    program.amplitude = 0;
    program.frequency = 0;
    program.phase_duration = 0;
    program.ON_time = 0;
    program.OFF_time = 0;
    program.contractions = 0;
    program.ramp_up = 0;
    program.ramp_down = 0;
    */
    //Redirect the interrupt handler
    TMR0_SetInterruptHandler(NEMS_timer);
    
    DAC1_SetOutput(0);
        
}

void NEMS_message_handler(void)
{
    unsigned char header;
    
    header = EUSART1_Read();
    
    switch (header) {
        case 't': // Test communications
            _puts("Ok ");
            break;
            
        case 'a': // Set current amplitude [mA] 1 mA - 32 mA or higher (pp. 31, Chap 3)
            NEMS_set_amplitude();
            break;
            
        case 'f': // Set frequency [Hz] 15 - 50 (pp. 32, Chap 3))
            NEMS_set_frequency();
            break;
            
        case 'd': // Set phase duration [us/50] ( 200us - 400us --> 4 - 8) (pp. 83, Chap 6)
            NEMS_set_phase_duration();
            break;
            
        case 'k': // // symmetric = 1, asymmetric = phase_negative/ phase_duration = [2,4,8]
            NEMS_set_symmetry_factor();
            break;
            
        case 'o': // Set ON time [s] 2s-4s (pp. 86, Chap 6) ON/OFF ~ 4:12, 1:3 
            NEMS_set_ON_time();
            break;
            
        case 'O': // Set OFF time [s] ON/OFF 1/3 to 1/5  over 10-15 contractions
            NEMS_set_OFF_time();
            break;
            
        case 'c': // Set number of contractions
            NEMS_set_contractions();
            break;
            
        case 'r': // Set ramp-up time [ds] depends on the muscle and exercise, typically below 2s.(pp. 89, Chap 6)
            NEMS_set_ramp_up();
            break;
            
        case 'R': // Set ramp_down time [ds] 
            NEMS_set_ramp_down();
            break;           
        
        case 'p': // Read current program configuration
            NEMS_get_program();
            break;           
            
        case 's': // Save program configuration in EEPROM
            NEMS_save_program();
            break;   
            
        case 'l': // Load program configuration from EEPROM
            NEMS_load_program();
            break;
            
        case 'n': // Start stimulation program
            NEMS_start_program();
            break;
            
        case 'N': // Stop stimulation program
            NEMS_stop_program();
            break;
            
        default: //Unknown header
            break; 
    }
    
}

unsigned char NEMS_get_packet(unsigned char* pt)
{
    unsigned char message[2];
    
    __delay_ms(10);
    
    if (eusart1RxCount == 2) { //Valid packet size
        message[0] = EUSART1_Read();
        message[1] = EUSART1_Read();
        
        *pt = message[0] - '0';
        *pt *= 10;
        *pt += message[1] - '0';
        
        return 1;
    } else {
        return 0; // error, wrong packet's size 
    }    
}

void NEMS_set_amplitude(void) 
{  
    if(NEMS_get_packet(&program.amplitude)) {
        _puts("a-ok ");
        
    } else {
        _puts("a-err ");
    }        
}

void NEMS_set_frequency(void)
{
    if(NEMS_get_packet(&program.frequency)) {
        _puts("f-ok ");
        
    } else {
        _puts("f-err ");
    }
}

void NEMS_set_phase_duration(void)
{
    if(NEMS_get_packet(&program.phase_duration)) {
        _puts("d-ok ");
        
    } else {
        _puts("d-err ");
    }
}

void NEMS_set_symmetry_factor(void)
{
    if(NEMS_get_packet(&program.symmetry_factor)) {
        _puts("k-ok ");
        
    } else {
        _puts("k-err ");
    }

}

void NEMS_set_ON_time(void)
{
    if(NEMS_get_packet(&program.ON_time)) {
        _puts("o-ok ");
        
    } else {
        _puts("o-err ");
    }        
}

void NEMS_set_OFF_time(void)
{
    if(NEMS_get_packet(&program.OFF_time)) {
        _puts("O-ok ");
        
    } else {
        _puts("O-err ");
    }
}

void NEMS_set_contractions(void)
{
    if(NEMS_get_packet(&program.contractions)) {
        _puts("c-ok ");
        
    } else {
        _puts("c-err ");
    }
}

void NEMS_set_ramp_up(void)
{
    if(NEMS_get_packet(&program.ramp_up)) {
        _puts("r-ok ");
        
    } else {
        _puts("r-err ");
    }
    
}

void NEMS_set_ramp_down(void)
{
    if(NEMS_get_packet(&program.ramp_down)) {
        _puts("R-ok ");
        
    } else {
        _puts("R-err ");
    }
}

void NEMS_get_program(void)
{
    unsigned char aux[4];
    
    _puts("\nNEMS program\n");    
    
    _sprintf_u8b(aux,program.amplitude);    
    _puts("Amplitude (mA): ");
    _puts(aux);
    _puts("\n");
    
    _sprintf_u8b(aux,program.frequency);
    _puts("Frequency (Hz): ");
    _puts(aux);
    _puts("\n");
    
    _sprintf_u8b(aux,program.phase_duration);
    _puts("Phase duration (us/50): ");
    _puts(aux);
    _puts("\n");
    
     _sprintf_u8b(aux,program.symmetry_factor);
    _puts("Symmetry factor: ");
    _puts(aux);
    _puts("\n");
    
    _sprintf_u8b(aux,program.ON_time);
    _puts("ON time (s) : ");
    _puts(aux);
    _puts("\n");
    
    _sprintf_u8b(aux,program.OFF_time);
    _puts("OFF time (s) : ");
    _puts(aux);
    _puts("\n");
    
    _sprintf_u8b(aux,program.ramp_up);
    _puts("Ramp up time (ds) : ");
    _puts(aux);
    _puts("\n");
    
    _sprintf_u8b(aux,program.ramp_down);
    _puts("Ramp down time (ds) : ");
    _puts(aux);
    _puts("\n");
    
    _sprintf_u8b(aux,program.contractions);
    _puts("Number of contractions: ");
    _puts(aux);
    _puts("\n");    
    
}

void NEMS_save_program(void)
{
    unsigned char addr;
    
    addr = 0;
    eeprom_write(addr++,program.amplitude);
    eeprom_write(addr++,program.frequency);
    eeprom_write(addr++,program.phase_duration);
    eeprom_write(addr++,program.symmetry_factor);
    eeprom_write(addr++,program.ON_time);
    eeprom_write(addr++,program.OFF_time);
    eeprom_write(addr++,program.ramp_up);
    eeprom_write(addr++,program.ramp_down);
    eeprom_write(addr,program.contractions);
        
    _puts("s-ok ");
    
}

void NEMS_load_program(void)
{
    unsigned short addr;
    
    addr = 0;
    
    program.amplitude = eeprom_read(addr++);
    program.frequency = eeprom_read(addr++);
    program.phase_duration = eeprom_read(addr++);
    program.symmetry_factor = eeprom_read(addr++);
    program.ON_time = eeprom_read(addr++);
    program.OFF_time = eeprom_read(addr++);
    program.ramp_up = eeprom_read(addr++);
    program.ramp_down = eeprom_read(addr++);
    program.contractions = eeprom_read(addr);
    
    _puts("l-ok ");
}

void NEMS_recalculate_program(void)
{
    waveform.num_clocks_per_pulse = (unsigned short)NEMS_TIMER_FREQUENCY/program.frequency;
    waveform.clock_index = 0;
    waveform.pulse_index = 0;
    
    waveform.ramp_up_pulses = (program.ramp_up*program.frequency)/10;  
    waveform.ramp_down_pulses = (program.ramp_down*program.frequency)/10;
    
    waveform.ramp_up_time = waveform.ramp_up_pulses;
    
    waveform.ON_time = program.ON_time*program.frequency + waveform.ramp_up_time;    
    waveform.ramp_down_time = waveform.ramp_down_pulses + waveform.ON_time;    
    waveform.OFF_time = program.OFF_time*program.frequency + waveform.ON_time;       
    
    waveform.pulse_amplitude = 0;
    waveform.current_amplitude = 0;
    waveform.program_amplitude = program.amplitude;
    
    switch (program.symmetry_factor) {
        case 1: waveform.symmetry_divider = 0; break;
        case 2: waveform.symmetry_divider = 1; break;
        case 4: waveform.symmetry_divider = 2; break;
        case 8: waveform.symmetry_divider = 3; break;
        default: waveform.symmetry_divider = 0;
    }
    
        
    waveform.silence_phase_duration = program.phase_duration + SILENCE_PERIOD;
    waveform.minus_phase_duration = program.phase_duration*program.symmetry_factor + program.phase_duration + SILENCE_PERIOD;
    
    
    waveform.ramp_index = 0;
    waveform.contractions_index = 0;
    
    NEMS_calculate_ramp();
    
    NEMS_states = NEMS_DISABLED;
    NEMS_wave_states = NEMS_OFF_TIME;    
    NEMS_pulse_states = NEMS_PULSE_OFF;    
}

void NEMS_calculate_ramp(void)
{
    unsigned char i;
    
    for (i = 0; i < waveform.ramp_up_pulses; i++) {
        waveform.ramp_up_amplitude[i] = (unsigned short)(i*waveform.program_amplitude)/waveform.ramp_up_pulses;
    }
    
    for (i = 0; i < waveform.ramp_down_pulses; i++) {
        waveform.ramp_down_amplitude[i] = (unsigned short)((waveform.ramp_down_pulses-i-1)*waveform.program_amplitude)/waveform.ramp_down_pulses;
    }
}

void NEMS_timer(void)
{   
    //UPDATE OUTPUTS
    DAC1_SetOutput(waveform.current_amplitude);
    LATC = NEMS_pulse_states;
   
    //PULSE STATES
    waveform.clock_index++;
        
    if (waveform.clock_index >= waveform.num_clocks_per_pulse)  { //New Pulse should start 
        waveform.clock_index = 0;  
        
        waveform.pulse_index++;
        
        NEMS_pulse_states = NEMS_PLUS_UP;
    
        if (waveform.pulse_index < waveform.ramp_up_time) {
            waveform.pulse_amplitude = waveform.ramp_up_amplitude[waveform.pulse_index];
                    
        } else if (waveform.pulse_index < waveform.ON_time) {
            waveform.pulse_amplitude = waveform.program_amplitude;
                    
        } else if (waveform.pulse_index < waveform.ramp_down_time) {
            waveform.pulse_amplitude = waveform.ramp_down_amplitude[waveform.pulse_index - waveform.ON_time];
        
        } else if (waveform.pulse_index < waveform.OFF_time) {
            waveform.pulse_amplitude = 0;
            NEMS_pulse_states = NEMS_PULSE_OFF;
        
        } else { //single repetition finished
            waveform.pulse_index = 0;        
        }
        
    }
    
    if (NEMS_pulse_states != NEMS_PULSE_OFF) {
        if (waveform.clock_index < program.phase_duration) {               
            NEMS_pulse_states = NEMS_PLUS_UP;
            waveform.current_amplitude = waveform.pulse_amplitude;
            
        }  else if (waveform.clock_index < waveform.silence_phase_duration) {
            NEMS_pulse_states = NEMS_REST;
            waveform.current_amplitude = 0;
            
        } else if (waveform.clock_index < waveform.minus_phase_duration) {
            NEMS_pulse_states = NEMS_MINUS_UP;
            waveform.current_amplitude = waveform.pulse_amplitude >> waveform.symmetry_divider;
            
        } else {
            NEMS_pulse_states = NEMS_PULSE_OFF;
            waveform.current_amplitude = 0;
        }
    }
          
}

void NEMS_start_program()
{
    NEMS_recalculate_program();
    
    NEMS_states = NEMS_ENABLED;
    TMR0_StartTimer();
    
    _puts("n-ok ");
}

void NEMS_stop_program()
{
    NEMS_states = NEMS_DISABLED;    
    TMR0_StopTimer();   
    DAC1_SetOutput(0);
    
    _puts("N-ok ");
}
