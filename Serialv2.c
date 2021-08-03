/***************************************************
* Module name: Serialv2.c
*
* First written on ubuntu by tamhau.
*
* Module Description:
* Module support to send data from PC to ATmega328P
* by using the Polling method.
*
***************************************************/
/*  Include section
* #include <stdint.h>
* #include <avr/io.h>
* #include <avr/interrupt.h>
* #include <avr/pgmspace.h>
* #include "Serialv2.h".
*
***************************************************/
/*  Defines section
* #define F_CPU 16000000UL
* #define ENABLE_USART0 1
* #define USART_INT_MODE 0 
* #define BAUDRATE 9600
* #define BAUD_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1).
*
***************************************************/
/*  Function Prototype Section
* extern void USART_init(void)
* extern void USART_send(char data, uint8_t usart_num)
* extern void USART_putstring(char *StringPtr, uint8_t usart_num)
* extern void USART_putstring_P(const char *StringPtr, uint8_t usart_num).
*
***************************************************/


 #include <stdint.h>

 
 #include <avr/io.h>                     /*needed for uint8_t*/
 #include <avr/interrupt.h>
 #include <avr/pgmspace.h>


 #include "avr/Serialv2.h"


 /*CPU Freq*/
 /*define F_CPU 16000000UL*/
 #define F_CPU 16000000UL
 /*Enable USART*/
 #define ENABLE_USART0 1
 /*choose USART Mode (=0 is polling; =1 is interupt)*/
 #define USART_INT_MODE 0 
 /*Baurate*/
 #define BAUDRATE 9600
 /*Macro to determine the baud prescale rate*/
 /*See table 24.1 in the Mega datasheet*/
 #define BAUD_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)


 /*function prototype*/
 extern void USART_init(void);

 /*Send a char using UART with usart_num = 0 or 1 */
 extern void USART_send(char data, uint8_t usart_num);

 /*Send a string using UART with usart_num = 0 or 1 */
 extern void USART_putstring(char *StringPtr, uint8_t usart_num);

 /*Send a string using UART with usart_num = 0 or 1 and string from data mem */
 extern void USART_putstring_P(const char *StringPtr, uint8_t usart_num);

 inline void 
 _inline_USART_init (void) {
 #if ENABLE_USART0
   /*Set the baud rate prescale rate register*/
   UBRR0H = BAUD_PRESCALER >> 8;
   UBRR0L = BAUD_PRESCALER;
   /*Enable receiver and transmitter*/
   UCSR0B = ((1<<RXEN0)|(1<<TXEN0));
   #if USART_INT_MODE
   UCSR0B = ((1<<RXEN0)|(1<<TXEN0)|(1 << RXCIE0));
   #endif
   /*Set frame format: 8data, 1 stop bit*/
   UCSR0C = 0x06;
 #endif
 }

 inline void
 _inline_USART_send( volatile char data, uint8_t usart_num) {
 #if ENABLE_USART0
 if (usart_num == 0) {
   /*while the transmit buffer is not empty loop*/
   while (!( UCSR0A & (1<<UDRE0)));
   /*when the buffer is empty write data to the transmitted*/
   UDR0 = data;
 }
 #endif
 }

 inline void 
 _inline_USART_putstring(char *StringPtr, uint8_t usart_num)
 {
  while(*StringPtr != 0x00)
  {
    USART_send(*StringPtr,usart_num);
    StringPtr++;
  }
 }
