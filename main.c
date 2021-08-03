/*
 * main.c
 *
 *  Created on: Apr 27, 2016
 *      Author: tamhau
 */


 #include <stdio.h>
 #include <stdint.h>


 #include <util/delay.h>
 #include <avr/io.h>


 #include <avr/Serial.h>


 int main()
 {
   USART_init();
   while (1)
   {
     //Using function USART_send send one by one 
     USART_send('H',0);
     USART_send('A',0);
     USART_send('U',0);
     USART_send('\n',0);
     //Using function USART_putstring
     USART_putstring("Helloworld",0);
     USART_putstring("\n",0);
     //Delay 1s
     _delay_ms(1000);
   }

 }
