#include "bio4.h"
#include "comm.h"

//#define WAIT __delay_ms(1)
//#define WAIT __delay_ms(2)
//#define WAIT __delay_us(2)
#define WAIT __delay_us(5)
//#define WAIT ;


void BIO_turnOffADC(void)
{
    ADCON0bits.ADON = 0;    
}

void BIO_messageHandler(void)
{
    unsigned char message;
    
    message = EUSART_Read();
    switch (message) {        
        case 't': //test comm
            //write(message,mess_rec_size);
            _puts("Ok");
            break;
        
        case 'f': //single shot sweep measurement SE no offset, crc
            BIO_sweep();
            break;
            
        case 'a': //Measure ADC channels            
            BIO_testADC();
            break;
        /*     
        case 'c': //config            
            config_ASIC();
            break;
            
        case 'm': //Measure ADC channels
            read_ADC_channels();
            break;
        
        case 'z': //Impedance Measurement
            measure_Impedance();
            break; 
            
        case 'y': //Impedance without offset
            measure_Impedance_no_offset();
            break;
            
        case 'o': //Offset measurement
            measure_Offset();
            break;
            
        case 's': //impedance Measurement Single Ended 
            measure_Impedance_SE();
            break;
        */
        #ifdef INDUCTIVE_POW
        case '&': //Tx loop to calibrate the reader
            BIO_calibrate_reader();
            break;
        #endif
                  
            
        default: 
            break;
    }

}

void BIO_changeTxPolarity(void)
{
    BAUDCONbits.SCKP = 1;
}

void BIO_sweep(void)
{
    unsigned char gain_index;
    unsigned char freq_index;
    unsigned char i, ret, count;
    short I,Q;
    unsigned char aux[7], check;

#ifdef BIOASIC
    BIO3 asic;    
    asic.datashort = 0; //Clears all bits: NS = 0 (32 steps), CE = 0 (disabled)
#else
    VIN asic;
    asic.datas[0] = 0;
    asic.datas[1] = 0;
    asic.datas[2] = 0;    
#endif
            
    //Initial ASIC configuration
    freq_index = 10; // Starts from 1kHz   
    gain_index = 0; // Starts with lowest gain    
    BIO_setGain(&asic,gain_index); // Set initial gain
       
    //Sweep all frequencies
    for (i = 0; i < 11; i++) {
        
        #ifdef BIOASIC
        BIO_setFreq(&asic,freq_index);        
        #else
        setFreq(&asic,freq_index);
        setFilt(&asic,freq_index);
        #endif
        
        //Measure and check if it is in range
        count = 0;
        ret = 0;
        
        do {            
        
            ret = BIO_measure(&I,&Q,asic);
            
            if (ret == 1) { //Increase Gain and repeat
                
                if (count == 2) break; // Previous decrease of gain, stops now!
                count = ret;                

                #ifdef BIOASIC
                if (gain_index < 7) {
                #else
                if (gain_index < 5) {
                #endif                
                    gain_index++;
                    BIO_setGain(&asic,gain_index);
                } else {
                    break; 
                }   
                                
                continue;
                
            } else if (ret == 2) { //Decrease Gain and repeat
            
                if (count == 1) break; // Previous increase of gain, stops now!
                count = ret;
                
                if (gain_index > 0) {
                    gain_index--;
                    BIO_setGain(&asic,gain_index);
                } else {
                    break; 
                }
                
                continue;
            }
                        
        } while (ret);
                       
        //Transmit I,Q, and current gain/freq config
        
        //merge gain and freq in one byte [freq_index : gain_index ]
        ret = (freq_index << 4) & 0xf0;
        ret |= (gain_index & 0xff);
        
        aux[0] = 'f';
        aux[1] = (unsigned char)(I & 0xff);
        aux[2] = (unsigned char)((I >> 8) & 0xff);
        aux[3] = (unsigned char)(Q & 0xff);
        aux[4] = (unsigned char)((Q >> 8) & 0xff);
        aux[5] = ret;
        
        check = BIO_calculate_checksum(aux,6);
        aux[6] = check;
        
        //TODO Here is a good idea to disable the ADC
        BIO_turnOffADC();
        
        //Disable the RX USART
        PIE1bits.RCIE = 0;
        RCSTAbits.CREN = 0;
    
        write(aux,7);
        __delay_ms(10);
        
        //Enable the RX USART
        RCSTAbits.CREN = 1;
        PIE1bits.RCIE = 1;
        
        
        //This delay is to avoid to start a new measurement when 
        //the BT transmitter is sending.
        //__delay_ms(100);
        #ifndef BIOASIC
        __delay_ms(50);
        #endif              
        
        freq_index--;
    }
   
}


#ifdef BIOASIC 
void BIO_config(BIO3 conf)
{
    unsigned char i, out;
    
    CLK_SetLow();
    WAIT;
    
    RESETN_SetLow();
    WAIT;
    
    RESETN_SetHigh();
        
    for(i = 0; i < BIO3_LENGTH; i++) {
        if (conf.datashort & 0x0001) { //DATA to H    
            DAT_SetHigh();
        } else { //DATA to L            
            DAT_SetLow();
        }        
        conf.datashort >>= 1;
        
        WAIT;
                
        CLK_SetHigh();
        WAIT;                
        CLK_SetLow();
        
    }    
}

void BIO_setGain(BIO3* asic, unsigned char gain_index)
{
    RADIO_gain aux;
    aux.data = gains[gain_index];
    
    asic->data_bits.GD0 = aux.data_bits.GD0;
    asic->data_bits.GD1 = aux.data_bits.GD1;
    asic->data_bits.GD2 = aux.data_bits.GD2;
    asic->data_bits.GS0 = aux.data_bits.GS0;
    asic->data_bits.GS1 = aux.data_bits.GS1;
    asic->data_bits.GS2 = aux.data_bits.GS2;
    asic->data_bits.GS3 = aux.data_bits.GS3;
}

void BIO_setFreq(BIO3* asic, unsigned char freq_index)
{
    RADIO_freq aux;
    aux.data = freqs[freq_index];
    
    asic->data_bits.F0 = aux.data_bits.F0;
    asic->data_bits.F1 = aux.data_bits.F1;
    asic->data_bits.F2 = aux.data_bits.F2;
    asic->data_bits.F3 = aux.data_bits.F3;
        
}

#ifdef BIOASIC
unsigned char BIO_measure(short* I, short* Q, BIO3 asic)
#else
unsigned char BIO_measure(short* I, short* Q, VIN asic)
#endif
{
    unsigned short offset, value;
    short aux1,aux2;
    //Measurements done using Single Ended output
        
    //Extract DC offset (expected value around 512 ~ 0.9V)
    asic.data_bits.IQ = 0; //Select I reference
    asic.data_bits.CE = 0; //Disable the signal generator
    BIO_config(asic); 
     __delay_ms(CONF_DELAY);
     
    offset = ADC_GetConversion(VOUT_SE);//ADCC_GetSingleConversion(VOUT_SE);            
    
    //extract I
    asic.data_bits.CE = 1; //Enable the signal generator
    asic.data_bits.IQ = 0; //Select I reference
    
    BIO_config(asic); 
     __delay_ms(CONF_DELAY);
     
    value = ADC_GetConversion(VOUT_SE);//ADCC_GetSingleConversion(VOUT_SE); //read channel 5 (VOUT_SE)   
    *I = (value - offset);
    aux1 = *I;
        
    if (aux1 < 0) {
        aux1 = -aux1;
    }
          
    //extract Q
    
    //Extract DC offset (expected value around 512 ~ 0.9V)
      
    //asic.data_bits.CE = 1; //Enable the signal generator
    asic.data_bits.IQ = 1; //Select Q reference
    
    BIO_config(asic); 
     __delay_ms(CONF_DELAY);
     
    value = ADC_GetConversion(VOUT_SE);//ADCC_GetSingleConversion(VOUT_SE); //read channel 5 (VOUT_SE)   
    *Q = (value - offset);
    aux2 = *Q;
    
    if (aux2 < 0) {
        aux2 = -aux2;
    }
    
    if (aux2 > aux1) {
        aux1 = aux2;
    }
    
    if (aux1 > MEAS_MAX) {
        return 2;
    } else if (aux1 < MEAS_MIN) {
        return 1;
    }
         
    return 0;    

}

unsigned char BIO_calculate_checksum(unsigned char* data, unsigned char num)
{
    unsigned char check, i;
    
    check = 0;
    for (i = 0; i < num; i++) {
        check ^= data[i];
    }
    
    return check;        
}

void BIO_calibrate_reader(void)
{
 unsigned char aux[8];
    
    aux[0] = 'h';
    aux[1] = 'o';
    aux[2] = 'l';
    aux[3] = 'a';
    aux[4] = 0x00;
    aux[5] = 0xaa;
    aux[6] = 0xfe;
    aux[7] = '@';
    
    while (1) {
        CLRWDT();
         __delay_ms(250);
         __delay_ms(250);
         __delay_ms(250);
         __delay_ms(250);
         write(aux,8);        
    }
}

void BIO_testADC(void)
{
    unsigned short value;
    unsigned char aux[3];
    
    value = ADC_GetConversion(VOUT_SE);
    
    aux[0] = 'a';
    aux[1] = (unsigned char)(value & 0xff);
    aux[2] = (unsigned char)((value >> 8) & 0xff);
    
    write(aux,3);
    
}


#else

void config(VIN conf)
{
    
      unsigned char i,j,out;
    
    CLK_L;
    WAIT;
    
    RESETN_L;
    WAIT;
    
    RESETN_H;
        
    for(i = 0; i < 16; i++) {
        if (conf.datas[0] & 0x0001) { //DATA to H    
            DATA_H;
        } else { //DATA to L            
            DATA_L;
        }        
        conf.datas[0] >>= 1;
        
        WAIT;
                
        CLK_H;
        WAIT;                
        CLK_L;        
    }
    
    for(i = 0; i < 16; i++) {
        if (conf.datas[1] & 0x0001) { //DATA to H    
            DATA_H;
        } else { //DATA to L            
            DATA_L;
        }        
        conf.datas[1] >>= 1;
        
        WAIT;
                
        CLK_H;
        WAIT;                
        CLK_L;        
    }
    
    for(i = 0; i < 1; i++) {
        if (conf.datas[2] & 0x0001) { //DATA to H    
            DATA_H;
        } else { //DATA to L            
            DATA_L;
        }        
        conf.datas[2] >>= 1;
        
        WAIT;
                
        CLK_H;
        WAIT;                
        CLK_L;        
    }
   
}


void setGain(VIN* asic, unsigned char gain_index)
{
    RADIO_gain aux;
    aux.data = gains[gain_index];
    
    asic->data_bits.GD0 = aux.data_bits.GD0;
    asic->data_bits.GD1 = aux.data_bits.void BIO_messageHandler(void);GD1;
    asic->data_bits.GD2 = aux.data_bits.GD2;
    asic->data_bits.GS0 = aux.data_bits.GS0;
    asic->data_bits.GS1 = aux.data_bits.GS1;
    asic->data_bits.GS2 = aux.data_bits.GS2;
    asic->data_bits.GS3 = aux.data_bits.GS3;
}

void setFreq(VIN* asic, unsigned char freq_index)
{
    RADIO_freq aux;
    aux.data = freqs[freq_index];
    
    asic->data_bits.F0 = aux.data_bits.F0;
    asic->data_bits.F1 = aux.data_bits.F1;
    asic->data_bits.F2 = aux.data_bits.F2;
    asic->data_bits.F3 = aux.data_bits.F3;
        
}

void setFilt(VIN* asic, unsigned char freq_index)
{
    VINfilt aux;
    aux.datal = filt[freq_index];
    
    asic->data[2] = aux.data[0];
    asic->data[3] = aux.data[1];
    asic->data[4] = aux.data[2];    
    
}

#endif
