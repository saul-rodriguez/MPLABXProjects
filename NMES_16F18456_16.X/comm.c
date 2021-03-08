#include "comm.h"
#include "mcc_generated_files/mcc.h"


void _puts(char *pt)
{
    unsigned char index;
    index = 0;
    while(pt[index]) {
        while(!EUSART1_is_tx_ready());
        EUSART1_Write(pt[index++]);        
    }
}

void write(unsigned char *pt, unsigned char lenght)
{
    unsigned char i;
    
    for (i=0; i<lenght; i++) {
        while(!EUSART1_is_tx_ready());
        EUSART1_Write(pt[i]); 
    }    
}

void _sprintf_u16b(char *mess, unsigned short val)
{
   // Converts ushort to a fixed point string with a range 0.000 - 9.999
   // Note that val is expressed in 1e-3 (milli-X)
    
  unsigned short aux;   
  
  aux = val%10;
  val /= 10;  
    
  mess[5] = 0x00;
    
  mess[4] = (unsigned char)aux+'0';
    
  aux = val%10;
  val /= 10;
    
  mess[3] = (unsigned char)aux+'0';
    
  aux = val%10;
  val /= 10;
    
  mess[2] = (unsigned char)aux+'0';
  mess[1] = '.';
  mess[0] = (unsigned char)val+'0';  
}

void _sprintf_u8b(char* mess, unsigned char val)
{
    // Converts uchar to a string
    unsigned char aux;
    unsigned char buf[3];
    
    aux = val%10;
    val /=10;
    
    buf[2] = aux;
    
    aux = val%10;
    val /=10;
    
    buf[1] = aux;    
    buf[0] = val;
    
    if (buf[0] != 0) { // 3 digit number
        mess[0] = buf[0] + '0';
        mess[1] = buf[1] + '0';
        mess[2] = buf[2] + '0';
        mess[3] = 0x00;
        return;
        
    } else if (buf[1] != 0) { // 2 digit number
        mess[0] = buf[1] + '0';
        mess[1] = buf[2] + '0';
        mess[2] = 0x00;        
        return;
        
    } else { // 1 digit number
        mess[0] = buf[2] + '0';
        mess[1] = 0x00;
    }
}

unsigned char _gets(unsigned char *pt, unsigned char length)
{
    unsigned char index;
 //read a line
    index = 0;
    while (index < length) {
        pt[index] = EUSART1_Read();
        if (pt[index] == 0x0a) {
            index --; //uncommented only if CR+LN
            return index; 
        } 
        index++;
    } 
    
    //error, buffer Overflow
    return 0;    
}

/*
void tests()
{
    unsigned char mess[5];   
    unsigned char val;
    
    val = 9;
    _sprintf_u8b(mess,val);
    
    val = 0;
    _sprintf_u8b(mess,val);
    
    val = 12;
    _sprintf_u8b(mess,val);
    
    val = 202;
    _sprintf_u8b(mess,val);
    
    val = 9;
    _sprintf_u8b(mess,val);      
    
}
*/