/* 
 * File:   mcp23s17.h
 * Author: saul
 *
 * Created on August 24, 2020, 9:18 PM
 */

#ifndef MCP23S17_H
#define	MCP23S17_H

#ifdef	__cplusplus
extern "C" {
#endif

//Control Reg.
#define MCP23017_IOCON 0x0A
//Pin direction Regs.
#define MCP23017_IODIRA 0x00
#define MCP23017_IODIRB 0x01
//Pull-up resistors Regs.
#define MCP23017_GPPUA 0x0C
#define MCP23017_GPPUB 0x0D
//Port registers
#define MCP23017_GPIOA 0x12
#define MCP23017_GPIOB 0x13
//Interrupt enable registers
#define MCP23017_GPINTENA 0x04
#define MCP23017_GPINTENB 0x05
//Interrupt default compare register
#define MCP23017_DEFVALA 0x06
#define MCP23017_DEFVALB 0x07
//Interrupt control registers
#define MCP23017_INTCONA 0x08
#define MCP23017_INTCONB 0x09
//Interrupt flag registers
#define MCP23017_INTFA 0x0E
#define MCP23017_INTFB 0x0F
//Interrupt capture registers
#define MCP23017_INTCAPA 0x10
#define MCP23017_INTCAPB 0x11
    
extern unsigned char SPI_address;

void setAddress(unsigned char add);
void setTrisA(unsigned char tris); 
void writePortA(unsigned char val);


#ifdef	__cplusplus
}
#endif

#endif	/* MCP23S17_H */

