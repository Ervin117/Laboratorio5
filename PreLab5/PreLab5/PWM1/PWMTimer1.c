/*
 * PWMTimer1.c
 *
 * Created: 4/6/2025 9:45:34 PM
 *  Author: razer
 */ 
#include "PWMTimer1.h"
void PWM1A(uint8_t invertido, uint16_t presc)
{
	DDRB |= (1 << PORTB1); // OC1A como salida

	
	TCCR1A &= ~((1<<COM1A1) | (1<<COM1A0));

	if (invertido == invt)
	{
		TCCR1A |= (1 << COM1A1) | (1 << COM1A0); // modo invertido
	}
	else
	{
		TCCR1A |= (1 << COM1A1); // modo no invertido
	}

	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);

	ICR1 = 19999;

	switch (presc)
	{
		case 1:
			TCCR1B |= (1 << CS10);
			break;
		case 8:
			TCCR1B |= (1 << CS11);
			break;
		case 64:
			TCCR1B |= (1 << CS11) | (1 << CS10);
			break;
		case 256:
			TCCR1B |= (1 << CS12);
			break;
		case 1024:
			TCCR1B |= (1 << CS12) | (1 << CS10);
			break;
		default:
			TCCR1B |= (1 << CS11); // por defecto prescaler 8
			break;
	}
}

void updateDutyCycle1(uint16_t duty)
{
	if (duty > ICR1) duty = ICR1;
	OCR1A = duty;
}
