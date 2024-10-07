#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void moveright();
void moveleft();
const int d = 200;

int main(void)
{
	DDRB = 0b00011111;
	DDRD = 0b00001100;
	PORTD = 0b00000100;
	PORTB = 0b00000001;
	_delay_ms(d);
	
	while (1)
	{
		moveleft();
		PORTD = 0b00011111;
		PORTB = 0b00000001;
		_delay_ms(d);
		moveleft();
		moveright();
		PORTD = 0b00000100;
		PORTB = 0b00010000;
		_delay_ms(d);
		moveright();
	}
	return 0;
}

void moveleft()
{
	while(!(PORTB & (1<<4)))
	{
		PORTB = PORTB*2;
		_delay_ms(d);
	}
}
void moveright()
{
	while(!(PORTB & (1<<0)))
	{
		PORTB = PORTB /2;
		_delay_ms(d);
	}
}

