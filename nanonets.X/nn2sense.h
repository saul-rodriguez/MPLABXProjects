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

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
    
    typedef struct NN2SENSE_bits_struct {
        unsigned RE     :1;
        unsigned DAC0   :1;
        unsigned DAC1   :1;
        unsigned DAC2   :1;
        unsigned DAC3   :1;
        unsigned SEL0   :1;
        unsigned SEL1   :1;
        unsigned SEL2   :1;
        unsigned SEL3   :1;
        unsigned SEL4   :1;        
    } NN2SENSE_bits;
    
    typedef union {
        NN2SENSE_bits bits;
        unsigned short data;        
    } NN2SENSE;
        
    #define NN2SENSE_LENGTH 10
    
    typedef struct DAC_bits_struct {
        unsigned DAC0   :1; 
        unsigned DAC1   :1;
        unsigned DAC2   :1;
        unsigned DAC3   :1;        
    } DAC_bits; 
    
    typedef union {
        DAC_bits bits;
        unsigned char data;
    } DAC;
        
    typedef struct SEL_bits_struct {
        unsigned SEL0   :1;
        unsigned SEL1   :1;
        unsigned SEL2   :1;
        unsigned SEL3   :1;
        unsigned SEL4   :1;        
    } SEL_bits;
    
    typedef union {
        SEL_bits bits;
        unsigned char data;
    } SEL;
    
    extern volatile NN2SENSE nn2s;
    
    #define SETTLE_DELAY_MS 100
    
    void NN2SENSE_setup(void);
    void NN2SENSE_config(NN2SENSE conf);
    void NN2SENSE_setDAC(unsigned char dac);
    void NN2SENSE_setSEL(unsigned char sel);
    void NN2SENSE_selftest(void);
    
    
    
    
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

