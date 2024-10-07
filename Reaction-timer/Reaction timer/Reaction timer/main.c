
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h> //library includes srand(), rand() methods
#define F_CPU 16000000UL;

int volatile randomnum;     //Declare volatile variable for random number generation
int volatile speed;         //Declare volatile variable to get the reaction speed

int main(void)
{
	//Serial.begin(9600);
	DDRB = DDRB | 0b00100111; //Configure PB5 as blue led,PB0,PB1,PB2 as other leds outputs
	DDRD = DDRD & 0b11110011; //Configure PD2(INT0), PD3(INT3) as inputs
	PORTD = PORTD | 0b00001100;     //Pull-up PD2, PD3
	
	EICRA = (EICRA & 0b11111010) | 0b00001010;      //Set external interrupt on falling edge of INT0,INT1
	EIMSK = EIMSK | 0b00000011;                     //Enable external interrupt on INT0,INT1
	sei();                                          //Enable interrupts globally
	//timer 1 = 16 bit timer
	TCCR1B = (TCCR1B & 0b11111101) | 0b00000101;    //Set clock source as F_CPU/1024
	
	
	TCNT1 = 0;                                      //Default TCNT value as 0
	//timer 0 = 8 bit timer
	TCCR0B = (TCCR0B & 0b11111101) | 0b00000101;    //Set clock source as F_CPU/1024
	
	TCNT0 = 0;
	while (1)
	{
		//Serial.println(TCNT0);
	}
	return 0;
}

ISR(INT0_vect){
	
	PORTB = 0;                                          //Switch off all LEDs
	//Seed the random number using timer 0
	srand( TCNT0 );
	randomnum = rand() % 10 + 1;                        //Generate a random number between 1-10
	TCNT1 = ( 65535 - (int)(randomnum * 3906.25) ) + 1;      //Assign the value for TCNT to get the delay of random number seconds
	TIFR1 |= 0b00000001; //clear timer overflow flag bit
	TIMSK1 = TIMSK1 | 0b00000001;                       //Enable timer overflow interrupt
}

ISR(TIMER1_OVF_vect){                   //ISR for timer overflow interrupt
	PORTB=PORTB|0b00100000;                 //Switch ON LED connected to PB5
	TIFR1 |= 0b00000001; //clear timer overflow flag bit
}

ISR(INT1_vect){
	
	
	speed = TCNT1 / 3906.25;                            //Calculate the time taken to react
	PORTB &= 0b11011000;  //sets all led to off
	if(speed > 2)                                       //If reaction time greater than 2s
	{
		//Serial.println(2);
		PORTB = PORTB | 0b00000100;                     //Switch ON LED connected to PB2
	}

	else if(speed < 1)                                  //If reaction time less than 1s
	{
		//Serial.println(0);
		PORTB = PORTB | 0b00000001;                     //Switch ON LED connected to PB0
	}
	else                   //If reaction time greater than 1s but less than 2s
	{
		//Serial.println(1);
		PORTB = PORTB | 0b00000010;                     //Switch ON LED connected to PB1
	}
	TIMSK1 = TIMSK1 & 0b11111110; //disable timer overflow
}

