/*
 * PreLab5.c
 *
 * Created: 4/6/2025 5:55:32 PM
 * Author : Ervin Gomez 231226
 */ 

/****************************************/
// Encabezado (Libraries)
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "PWM1/PWMTimer1.h"

uint16_t duty = 0; //191
uint8_t angulo = 0; 
/****************************************/
// Function prototypes
void setup(); 
void _ADC(); 

/****************************************/
// Main Function
int main(void){
	
	setup(); 
	_ADC(); 
	
	while (1)
	{
		
	}
}

/****************************************/
// NON-Interrupt subroutines
void setup()
{
	cli(); 
	CLKPR = (1<<CLKPCE);
	CLKPR = (1<<CLKPS2); //Frecuancia de CPU 1Mhz
	PWM1A(no_invt, 64); 
	
	UCSR0B = 0;
	sei(); 
}

void _ADC(void)
{
	ADMUX = 0;
	ADMUX |= (1<<REFS0) | (1<<ADLAR) | (1 << MUX0) |  (1 << MUX1) | (1<<MUX2);
	
	ADCSRA = 0;
	ADCSRA |= (1<<ADPS1) | (1<<ADPS2) |  (1<<ADIE) | (1<<ADEN);
	ADCSRA |= (1<<ADSC);
	
}
/****************************************/
// Interrupt routines
ISR(ADC_vect)
{
	angulo = (ADCH*180)/255;
	duty = 16 + (angulo*(45-16)/180);
	updateDutyCycle1(duty);
	ADCSRA |= (1<<ADSC);
}