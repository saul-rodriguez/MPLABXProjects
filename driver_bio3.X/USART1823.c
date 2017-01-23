#include "USART1823.h"

//BIO1

volatile unsigned char USART_rx_flag;
volatile unsigned char USART_rx_index;
//extern volatile unsigned char USART_rx_size;
//volatile unsigned char USART_rx_received;
volatile unsigned char USART_rx_data[RX_BUF_SIZE];

volatile unsigned char USART_tx_flag;
volatile unsigned char USART_tx_data[TX_BUF_SIZE];
volatile unsigned char USART_tx_index;
volatile unsigned char USART_tx_length;

void start_TX_USART()
{
    
    CONFIG_BAUD();    
    SYNC = 0;  // configures the USART for async. serial comm.
    SPEN = 1;  // Enables the usart and configures TX pin as output
    TXEN = 1;  // Enables transmitter circuitry

}

void start_RX_USART()
{
    CONFIG_BAUD();

    SYNC = 0;  // configures the USART for async. serial comm.
    SPEN = 1;  // Enables the usart and configures TX pin as output
    CREN = 1; //  Enables the receiver circuitry
}

void close_RX_USART()
{
//    SPEN = 0;
//    TXEN = 0;
    RCIE = 0;  // RX Interrupt enable
    CREN = 0;


}

void close_USART()
{
    SPEN = 0;
    TXEN = 0;
    CREN = 0;
}

void putch(unsigned char byte)
{
	/* output one byte */
	while(!TXIF)	/* set when register is empty */
            continue;
        
	TXREG = byte;
}

unsigned char getch()
{
	/* retrieve one byte */
	while(!RCIF)	/* set when register is not empty */
            continue;

        return RCREG;
}

void lputs(unsigned char* data, unsigned char length)
{
    unsigned char aux;

    aux = length;

    while (aux) {
        putch(*data++);
        aux--;
    }
}

void start_RX_USART_ISR()
{

     CONFIG_BAUD();

    SYNC = 0;  // configures the USART for async. serial comm.
    SPEN = 1;  // Enables the usart and configures TX pin as output
    CREN = 1; //  Enables the receiver circuitry

    USART_rx_flag = RX_FREE;
    USART_rx_index = 0;
    
    RCIE = 1;  // RX Interrupt enable
    PEIE = 1;  // Pheriperal interrupt enable
    GIE = 1;   // Global interrupt enable

}

void start_TX_USART_ISR()
{
    CONFIG_BAUD();
    SYNC = 0;  // configures the USART for async. serial comm.
    SPEN = 1;  // Enables the usart and configures TX pin as output
    TXEN = 1;  // Enables transmitter circuitry

    USART_tx_flag = TX_FREE;
    USART_tx_index = 0;
    USART_tx_length = 0;

    //TXIE = 1;
    PEIE = 1;
    GIE = 1;
}


int putch_ISR(unsigned char byte)
{
   /* if (USART_tx_flag == TX_BUSY)
        return 0;

    USART_tx_flag == TX_BUSY;
    
    USART_tx_data = byte;
    TXIE = 1;*/

    return 1;

}

void lputs_ISR(unsigned char* data, unsigned char length)
{
    unsigned char i;

    if (USART_tx_flag == TX_BUSY) //Transmitter busy, discard the message!
        return;
    
    for (i = 0; i < length; i++)
        USART_tx_data[i] = data[i];

    USART_tx_index = 0;
    USART_tx_length = length;

    USART_tx_flag = TX_BUSY;
    TXIE = 1; // run!
}

/* This code has to be included in the interrupt function if ISR are used

  //TMR0 ISRservice routine
    if (TMR0IF && TMR0IE) { //Important to && TMR0IE since TMR0IF may be set!

        TMR0IF = 0;  //Reset interrupt flag
        TMR0 = TIMER0_timeout;  // re-load timer register

        // Flag the event
        //TIMER0_flag = 1;
        // The TMR0 is attached to the USART, so the USART_rx_flag is used
        USART_rx_flag = RX_RECEIVED;

        // Stop the timer
        stop_TMR0_ISR();

        return;
    }


    //USART RX ISR routine
    if (RCIF) {
        stop_TMR0_ISR();

        //USART_rx_flag = RX_RECEIVED;
        if (USART_rx_index >= RX_BUF_SIZE) { //  buffer overflow. Reset the index
            USART_rx_index = 0;
        }

        USART_rx_data[USART_rx_index++] = RCREG;

       // if (TXIF == 0) {//Only half duplex!!!! channel used by Transmitter, discard the message!
       //     Ustop_TMR0_ISR();SART_rx_index = 0;
       //     return;
       // }

        start_TMR0_ISR(98); // 98 -> Start timer0, timeout in 10ms (500kHz oscillator freq)

        return;
    }


    //USART RX ISR routine
    if (TXIF && TXIE) { //TXIF IS ALWAYS 1 when txbuf is empty!!!!!!
        //USART_tx_isr;
        TXREG = USART_tx_data[USART_tx_index++];

        if (USART_tx_index >= USART_tx_length) {
            TXIE = 0;
            USART_tx_flag = TX_FREE;

            //Uncomment these lines if re-enabling of Rx circuitry is needed
            //__delay_ms(5);
            //start_RX_USART_ISR(); 
        }
        return;
    }

 */

