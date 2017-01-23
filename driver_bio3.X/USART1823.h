#ifndef USART1823_H
#define USART1823_H

#include <xc.h>

//BIO

// BAUD is defined in bps
#define BAUD 9600

// FREQ is defined in kHz
#define FREQ 500


//Baud Rate Generation (page 301)
//9600bps for CLK = 500KHz: SPBRGL = 12
//9600bps for CLK = 1 MHz: SPBRGL = 25
//2400bps for CLK = 1 MHz: SPBRGL = 103

#if (BAUD == 9600 && FREQ == 500)
#define CONFIG_BAUD() { BRGH = 1;\
                        BRG16 = 1;\
                        SPBRGH = 0;\
                        SPBRGL = 12; }
#endif

#if (BAUD == 9600 && FREQ == 1000)
#define CONFIG_BAUD() { BRGH = 1;\
                        BRG16 = 1;\
                        SPBRGH = 0;\
                        SPBRGL = 25; }
#endif

#if (BAUD == 2400 && FREQ == 1000)
#define CONFIG_BAUD() { BRGH = 1;\
                        BRG16 = 1;\
                        SPBRGH = 0;\
                        SPBRGL = 103; }
#endif

#define TX_FREE 0
#define TX_BUSY 1
#define RX_FREE 0
#define RX_RECEIVED 1
#define RX_RECEIVED_TIMEOUT 2

#define TX_BUF_SIZE 15
#define RX_BUF_SIZE 15

extern volatile unsigned char USART_rx_flag;
extern volatile unsigned char USART_rx_index;
//extern volatile unsigned char USART_rx_size;
//extern volatile unsigned char USART_rx_received;
extern volatile unsigned char USART_rx_data[RX_BUF_SIZE];

extern volatile unsigned char USART_tx_flag;
extern volatile unsigned char USART_tx_data[TX_BUF_SIZE];
extern volatile unsigned char USART_tx_index;
extern volatile unsigned char USART_tx_length;


void start_TX_USART(); 
void start_RX_USART();
void close_USART();
void close_RX_USART();
void putch(unsigned char byte);
int putch_ISR(unsigned char byte);
unsigned char getch();
void lputs(unsigned char* data, unsigned char length);
void lputs_ISR(unsigned char* data, unsigned char length);

void start_RX_USART_ISR();
void start_TX_USART_ISR();

#endif