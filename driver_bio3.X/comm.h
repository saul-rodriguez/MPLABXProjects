/* 
 * File:   comm.h
 * Author: saul
 *
 * Created on January 24, 2017, 10:11 AM
 */

#ifndef COMM_H
#define	COMM_H

#ifdef	__cplusplus
extern "C" {
#endif

#define BUFF_SIZE 3
extern volatile unsigned char mess_rec[BUFF_SIZE];   //Buffer to store USART RX data
extern volatile unsigned char mess_rec_size;

void mess_handler(); //Process data received from the USART



#ifdef	__cplusplus
}
#endif

#endif	/* COMM_H */

