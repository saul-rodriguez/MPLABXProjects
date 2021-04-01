#include "NEMS.h"
#include "comm.h"
#include "mcc_generated_files/tmr0.h"

//Program settings

volatile NEMS_program program;
volatile NEMS_waveform waveform;

volatile NEMS_state NEMS_states;
volatile NEMS_wave_state NEMS_wave_states;
volatile NEMS_pulse_state NEMS_pulse_states;

unsigned char NEMS_nmux1;
unsigned char NEMS_pmux1;

bool channel_control;

volatile unsigned char sens_buf[SENSOR_BUFFER_SIZE];
volatile unsigned char sensor_ind;

//channel selector 
//         bit4  bit3 bit2 bit1 bit0
//MAX 306  EN1    A3   A2   A1   A0

const unsigned char mux[17] = {
    0b00000000, // No electrode selected !
    0b00010000, // electrode 1
    0b00010001, // electrode 2
    0b00010010,
    0b00010011,
    0b00010100,
    0b00010101,
    0b00010110,
    0b00010111,
    0b00011000,
    0b00011001,
    0b00011010,
    0b00011011,
    0b00011100,
    0b00011101,
    0b00011110, // electrode 15
    0b00011111  // electrode 16 
};


void NEMS_initialize(void)
{
    //Stop TMR0
    TMR0_StopTimer();
           
    
    //Only for testing purposes
    program.amplitude = 1;
    program.amplitude2 = 1;
    program.frequency = 35;
    program.phase_duration = 1;
    program.ON_time = 2;
    program.OFF_time = 6;
    program.contractions = 5;
    program.ramp_up = 10;
    program.ramp_down = 10;
    program.symmetry_factor = 1;
    program.channel1 = 0; // no channel selected
    program.channel2 = 0; // no channel selected
    program.channel3 = 0; // no channel selected
    program.channel4 = 0; // no channel selected
    
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
    
    DAC1_SetOutput(0); //Current source set to 0
    
    NEMS_nmux1 = 0; // bottom switches deactivated
    NEMS_pmux1 = 0; // top switches deactivated
    LATC = NEMS_nmux1;
    LATB = NEMS_pmux1;
    
    channel_control = 0;
    
    sensor_ind = 0;
        
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
            
        case 'A': // Set current amplitude [mA] 1 mA - 32 mA or higher (pp. 31, Chap 3)
            NEMS_set_amplitude2();
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
            
        case 'M': // set multiplexer channel 1
            NEMS_set_channel1();
            break;
            
        case 'm': // set multiplexer channel 2
            NEMS_set_channel2();
            break;
            
        case 'Q': // set multiplexer channel 3
            NEMS_set_channel3();
            break;
            
        case 'q': // set multiplexer channel 4
            NEMS_set_channel4();
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

void NEMS_set_amplitude2(void)
{
    if(NEMS_get_packet(&program.amplitude2)) {
        _puts("A-ok ");
        
    } else {
        _puts("A-err ");
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
    _puts("Amplitude1 (mA): ");
    _puts(aux);
    _puts("\n");
    
    _sprintf_u8b(aux,program.amplitude2);    
    _puts("Amplitude2 (mA): ");
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
    
    _sprintf_u8b(aux,program.channel1);
    _puts("Channel 1: ");
    _puts(aux);
    _puts("\n");    
    
    _sprintf_u8b(aux,program.channel2);
    _puts("Channel 2: ");
    _puts(aux);
    _puts("\n");   

    _sprintf_u8b(aux,program.channel3);
    _puts("Channel 3: ");
    _puts(aux);
    _puts("\n");    
    
    _sprintf_u8b(aux,program.channel4);
    _puts("Channel 4: ");
    _puts(aux);
    _puts("\n");       
    
}

void NEMS_set_channel1(void)
{
    if(NEMS_get_packet(&program.channel1)) {
        _puts("M-ok ");
        
    } else {
        _puts("M-err ");
    } 
}

void NEMS_set_channel2(void)
{
    if(NEMS_get_packet(&program.channel2)) {
        _puts("m-ok ");
        
    } else {
        _puts("m-err ");
    } 
}

void NEMS_set_channel3(void)
{
    if(NEMS_get_packet(&program.channel3)) {
        _puts("Q-ok ");
        
    } else {
        _puts("Q-err ");
    } 
}

void NEMS_set_channel4(void)
{
    if(NEMS_get_packet(&program.channel4)) {
        _puts("q-ok ");
        
    } else {
        _puts("q-err ");
    } 
}

void NEMS_save_program(void)
{
    unsigned char addr;
    
    addr = 0;
    eeprom_write(addr++,program.amplitude);
    eeprom_write(addr++,program.amplitude2);
    eeprom_write(addr++,program.frequency);
    eeprom_write(addr++,program.phase_duration);
    eeprom_write(addr++,program.symmetry_factor);
    eeprom_write(addr++,program.ON_time);
    eeprom_write(addr++,program.OFF_time);
    eeprom_write(addr++,program.ramp_up);
    eeprom_write(addr++,program.ramp_down);
    eeprom_write(addr++,program.contractions);
    eeprom_write(addr++,program.channel1);
    eeprom_write(addr++,program.channel2);
    eeprom_write(addr++,program.channel3);
    eeprom_write(addr,program.channel4);
        
    _puts("s-ok ");
    
}

void NEMS_load_program(void)
{
    unsigned short addr;
    
    addr = 0;
    
    program.amplitude = eeprom_read(addr++);
    program.amplitude2 = eeprom_read(addr++);
    program.frequency = eeprom_read(addr++);
    program.phase_duration = eeprom_read(addr++);
    program.symmetry_factor = eeprom_read(addr++);
    program.ON_time = eeprom_read(addr++);
    program.OFF_time = eeprom_read(addr++);
    program.ramp_up = eeprom_read(addr++);
    program.ramp_down = eeprom_read(addr++);
    program.contractions = eeprom_read(addr++);
    program.channel1 = eeprom_read(addr++);
    program.channel2 = eeprom_read(addr++);
    program.channel3 = eeprom_read(addr++);
    program.channel4 = eeprom_read(addr);
    
    _puts("l-ok ");
}

void NEMS_recalculate_program(void)
{
    waveform.num_clocks_per_pulse = (unsigned short)NEMS_TIMER_FREQUENCY/program.frequency;
    
    // the counter will runs at twice frequency for 2 simultaneous channels
    waveform.num_clocks_per_pulse /= 2; 
    
    waveform.clock_index = 0;
    waveform.pulse_index = 0;
    
    waveform.pulse_index2 = 0;
    
    waveform.ramp_up_pulses = (program.ramp_up*program.frequency)/10;  
    waveform.ramp_down_pulses = (program.ramp_down*program.frequency)/10;
    
    waveform.ramp_up_time = waveform.ramp_up_pulses;
    
    waveform.ON_time = program.ON_time*program.frequency + waveform.ramp_up_time;    
    waveform.ramp_down_time = waveform.ramp_down_pulses + waveform.ON_time;    
    waveform.OFF_time = program.OFF_time*program.frequency + waveform.ON_time;       
    
    waveform.pulse_amplitude = 0;
    waveform.current_amplitude = 0;
    waveform.program_amplitude = program.amplitude;
    
    waveform.program_amplitude2 = program.amplitude2;
    
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
    
    waveform.channel1 = mux[program.channel1];
    waveform.channel2 = mux[program.channel2];
    waveform.channel3 = mux[program.channel3];
    waveform.channel4 = mux[program.channel4];
    
    NEMS_calculate_ramp();
    
    NEMS_states = NEMS_DISABLED;
    NEMS_wave_states = NEMS_OFF_TIME;    
    NEMS_pulse_states = NEMS_PULSE_OFF;   
    
    channel_control = 0;
}

void NEMS_calculate_ramp(void)
{
    unsigned char i;
    
    for (i = 0; i < waveform.ramp_up_pulses; i++) {
        waveform.ramp_up_amplitude[i] = (unsigned short)(i*waveform.program_amplitude)/waveform.ramp_up_pulses;        
        waveform.ramp_up_amplitude2[i] = (unsigned short)(i*waveform.program_amplitude2)/waveform.ramp_up_pulses;        
    }
    
    for (i = 0; i < waveform.ramp_down_pulses; i++) {
        waveform.ramp_down_amplitude[i] = (unsigned short)((waveform.ramp_down_pulses-i-1)*waveform.program_amplitude)/waveform.ramp_down_pulses;
        waveform.ramp_down_amplitude2[i] = (unsigned short)((waveform.ramp_down_pulses-i-1)*waveform.program_amplitude2)/waveform.ramp_down_pulses;        
    }    
    
}

//1 channel version
/*
void NEMS_timer(void)
{   
    //UPDATE OUTPUTS
    DAC1_SetOutput(waveform.current_amplitude);
   
    //Digital outputs controlling the MUX are updated here
    //LATC = NEMS_pulse_states;
    LATC = NEMS_nmux1;
    LATB = NEMS_pmux1;
            
   
    //PULSE STATES
    waveform.clock_index++;
    

    //Check if a new pulse is starting
    if (waveform.clock_index >= waveform.num_clocks_per_pulse)  { //New Pulse should start 
        waveform.clock_index = 0;  
        
        waveform.pulse_index++;
        
        NEMS_pulse_states = NEMS_PLUS_UP; //start with channel1 (n-) and channel2 (p+);
       // NEMS_nmux1 = waveform.channel1;
       // NEMS_pmux1 = waveform.channel2;
        
    
        if (waveform.pulse_index < waveform.ramp_up_time) {
            waveform.pulse_amplitude = waveform.ramp_up_amplitude[waveform.pulse_index];
                    
        } else if (waveform.pulse_index < waveform.ON_time) {
            waveform.pulse_amplitude = waveform.program_amplitude;
                    
        } else if (waveform.pulse_index < waveform.ramp_down_time) {
            waveform.pulse_amplitude = waveform.ramp_down_amplitude[waveform.pulse_index - waveform.ON_time];
        
        } else if (waveform.pulse_index < waveform.OFF_time) {
            waveform.pulse_amplitude = 0;
            NEMS_pulse_states = NEMS_PULSE_OFF;            
            NEMS_nmux1 = 0;
            NEMS_pmux1 = 0;
            
        
        } else { //single repetition finished
            waveform.pulse_index = 0;        
        }
        
    }
    
    //Check if a running pulse needs to be changed its state
    if (NEMS_pulse_states != NEMS_PULSE_OFF) {
        if (waveform.clock_index < program.phase_duration) {               
            NEMS_pulse_states = NEMS_PLUS_UP;
            NEMS_nmux1 = waveform.channel1;
            NEMS_pmux1 = waveform.channel2;
            
            waveform.current_amplitude = waveform.pulse_amplitude;
            
        }  else if (waveform.clock_index < waveform.silence_phase_duration) {
            NEMS_pulse_states = NEMS_REST;
            NEMS_nmux1 = 0;
            NEMS_pmux1 = 0;
            
            waveform.current_amplitude = 0;
            
        } else if (waveform.clock_index < waveform.minus_phase_duration) {
            NEMS_pulse_states = NEMS_MINUS_UP;
            NEMS_nmux1 = waveform.channel2;
            NEMS_pmux1 = waveform.channel1;
            
            waveform.current_amplitude = waveform.pulse_amplitude >> waveform.symmetry_divider;
            
        } else {
            NEMS_pulse_states = NEMS_PULSE_OFF;
            NEMS_nmux1 = 0;
            NEMS_pmux1 = 0;
            
            waveform.current_amplitude = 0;
        }
    }
          
}
*/

//2 channels version
void NEMS_timer(void)
{   
   // LED_SetHigh();
    
    //UPDATE OUTPUTS
    DAC1_SetOutput(waveform.current_amplitude);
   
    //Digital outputs controlling the MUX are updated here
    //LATC = NEMS_pulse_states;
    LATC = NEMS_nmux1;
    LATB = NEMS_pmux1;
            
    //PULSE STATES
    waveform.clock_index++;
   
    //Check if a new pulse is starting
    if (waveform.clock_index >= waveform.num_clocks_per_pulse)  { //New Pulse should start 
        waveform.clock_index = 0;  
     
         
         NEMS_pulse_states = NEMS_PLUS_UP; //start with channel1 (n-) and channel2 (p+);
        
        if (channel_control) { //Updates only every other pulse           
            channel_control = 0;  
            
            waveform.pulse_index++;
            
            // Logic to control ramp-up, ON, ramp-down, OFF
            if (waveform.pulse_index < waveform.ramp_up_time) {
                waveform.pulse_amplitude = waveform.ramp_up_amplitude[waveform.pulse_index];

            } else if (waveform.pulse_index < waveform.ON_time) {
                waveform.pulse_amplitude = waveform.program_amplitude;

            } else if (waveform.pulse_index < waveform.ramp_down_time) {
                waveform.pulse_amplitude = waveform.ramp_down_amplitude[waveform.pulse_index - waveform.ON_time];

            } else if (waveform.pulse_index < waveform.OFF_time) {
                waveform.pulse_amplitude = 0;
                NEMS_pulse_states = NEMS_PULSE_OFF;            
                NEMS_nmux1 = 0;
                NEMS_pmux1 = 0;
            } else { //single repetition finished
                waveform.pulse_index = 0;        
            }
        } else {
            channel_control = 1;
            
            waveform.pulse_index2++;
            
                 // Logic to control ramp-up, ON, ramp-down, OFF
            if (waveform.pulse_index2 < waveform.ramp_up_time) {
                waveform.pulse_amplitude = waveform.ramp_up_amplitude2[waveform.pulse_index2];

            } else if (waveform.pulse_index2 < waveform.ON_time) {
                waveform.pulse_amplitude = waveform.program_amplitude2;

            } else if (waveform.pulse_index2 < waveform.ramp_down_time) {
                waveform.pulse_amplitude = waveform.ramp_down_amplitude2[waveform.pulse_index2 - waveform.ON_time];

            } else if (waveform.pulse_index2 < waveform.OFF_time) {
                waveform.pulse_amplitude = 0;
                NEMS_pulse_states = NEMS_PULSE_OFF;            
                NEMS_nmux1 = 0;
                NEMS_pmux1 = 0;
            } else { //single repetition finished
                waveform.pulse_index2 = 0;        
            }
        }        
        
    }
    
        
    // Logic to control pulse shape
    if (NEMS_pulse_states != NEMS_PULSE_OFF) {
        if (waveform.clock_index < program.phase_duration) {               
            NEMS_pulse_states = NEMS_PLUS_UP;
            
            if (channel_control) {
                NEMS_nmux1 = waveform.channel3;
                NEMS_pmux1 = waveform.channel4;            
                waveform.current_amplitude = waveform.pulse_amplitude;
            } else {
                NEMS_nmux1 = waveform.channel1;
                NEMS_pmux1 = waveform.channel2;
                waveform.current_amplitude = waveform.pulse_amplitude;
            }            
            
            //waveform.current_amplitude = waveform.pulse_amplitude;
            
        }  else if (waveform.clock_index < waveform.silence_phase_duration) {
            NEMS_pulse_states = NEMS_REST;
            NEMS_nmux1 = 0;
            NEMS_pmux1 = 0;
            
            waveform.current_amplitude = 0;
            
        } else if (waveform.clock_index < waveform.minus_phase_duration) {
            NEMS_pulse_states = NEMS_MINUS_UP;
            
            if (channel_control) {
                NEMS_nmux1 = waveform.channel4;
                NEMS_pmux1 = waveform.channel3; 
                waveform.current_amplitude = waveform.pulse_amplitude >> waveform.symmetry_divider;
            } else {
                NEMS_nmux1 = waveform.channel2;
                NEMS_pmux1 = waveform.channel1;            
                waveform.current_amplitude = waveform.pulse_amplitude >> waveform.symmetry_divider;
            }
           // waveform.current_amplitude = waveform.pulse_amplitude >> waveform.symmetry_divider;
            
        } else {
            NEMS_pulse_states = NEMS_PULSE_OFF;
            NEMS_nmux1 = 0;
            NEMS_pmux1 = 0;
            
            waveform.current_amplitude = 0;
        }
    }
    
    
  //  LED_SetLow();      
}


void NEMS_start_program()
{
    //Check that channel1 != channel2
    if (program.channel1 != 0 && program.channel2 != 0 ) {
        if (program.channel1 == program.channel2) {
            _puts("Error: channel1 = channel2\n");     
            return;
        }    
    }
    
    NEMS_recalculate_program();
    
    NEMS_states = NEMS_ENABLED;
    TMR0_StartTimer();
    
    NEMS_start_sensors();
    
    _puts("n-ok ");
}

void NEMS_stop_program()
{
    NEMS_states = NEMS_DISABLED;    
    TMR0_StopTimer();   
        
    DAC1_SetOutput(0);
    NEMS_nmux1 = 0; // bottom switches deactivated
    NEMS_pmux1 = 0; // top switches deactivated
    LATC = NEMS_nmux1;
    LATB = NEMS_pmux1;
    
    NEMS_stop_sensors();
    
    _puts("N-ok ");
}

void NEMS_start_sensors(void)
{
    TMR1_Reload();
    TMR1_StartTimer(); 
}

void NEMS_stop_sensors(void)
{
    TMR1_StopTimer();
}

void NEMS_read_sensors(void)
{
    unsigned short aux;
    unsigned char i;
      
    aux = ADCC_GetSingleConversion(SENSOR1);
    
    sens_buf[sensor_ind++] = (unsigned char)(aux & 0xff);
    sens_buf[sensor_ind++] = (unsigned char)((aux >> 8) & 0xff);
            
    if (sensor_ind >= SENSOR_BUFFER_SIZE) {
        write(sens_buf,SENSOR_BUFFER_SIZE);        
        sensor_ind = 0;
    } 

}
