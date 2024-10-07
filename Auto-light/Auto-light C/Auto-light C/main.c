
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void) {
	DDRB = DDRB | 0b00000010;		// configure PB1 as input pin
	DDRC = DDRC & 0b11111110;	//configure PC0 as output pin

	ADCSRA = (ADCSRA & 0b01111111) | 0b01000000;	//vref == VCC(5V)
	ADMUX = ADMUX & 0b00011111;	//ADC0 channel
	ADCSRA = ADCSRA | 0b11111111;	// set ADC clock speed to F_CPU/128
	ADCSRA = ADCSRA | 0b10000000;	//Enable ADC

	while(1){
		
		ADCSRA = ADCSRA | 0b01000000;
		while ( ADCSRA & 0b01000000);
		
		if (ADCW < 500){
			PORTB = PORTB | 0b00000010;
			}
		else{
			PORTB = PORTB & 0b11111101;
		}
	}
	return 0;
}


