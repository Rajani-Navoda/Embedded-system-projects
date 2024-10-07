#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#include <stdbool.h>

volatile char count = 0;
volatile bool showed = false;


int main(void)
{
	DDRB = 0b00111111;
	DDRD = 0b11000000;

	PORTD = PORTD | (1<<2) | (1<<3); //input pull-up

	EICRA = 0b00001010; // falling interrupt
	EIMSK = 0b00000011;
	
	sei();
	
	while(1)
	{
		

		
		
	}
	return 0;
}
ISR(INT0_vect){

	count++;
	
}

ISR(INT1_vect){
	showed =! showed;
	
	
	if (showed)
	{
		PORTB = PORTB| (count >>2) ;
		PORTD = PORTD | (count <<  6) ;  // & with zeros will only output to the ports with 1.then the right shift will shift the port bits to the 0 and 1 pins of the port
		count = 0;
	}
	else{
		PORTB = PORTB & 0b11000000;
		PORTD = PORTD & 0b00111111;
		count = 0;
	}
	
	
}