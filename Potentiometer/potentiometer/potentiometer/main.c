
#include <avr/io.h>

int main(void)
{
    DDRB = DDRB  | 0b00011111;
	DDRC = DDRC & 0b11111110;
	ADMUX = (ADMUX & 0b01111111) | 0b01000000; //set the reference voltage
	ADMUX = ADMUX & 0b11111000; //set ADC0 as analog input
	ADCSRA = ADCSRA | 0b00000111;
	ADCSRA = ADCSRA | 0b10000000;
	
	
    while (1) 
    {
		ADCSRA = ADCSRA | 0b01000000;
		while(ADCSRA & 0b01000000);
		float vin = ADCW * 5.0/1024;
		PORTB = PORTB & 0b11100000;
		if (vin > 4)
			PORTB = PORTB | 0b00011111;
		else if (vin > 3)
			PORTB = PORTB | 0b00001111;
		else if (vin > 2)
			PORTB = PORTB | 0b00000111;
		else if (vin > 1)
			PORTB = PORTB | 0b0000011;
		else if (vin > 0)
			PORTB = PORTB | 0b00000001;			
    }
	return 0;
}

