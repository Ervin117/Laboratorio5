/*
 * PWMTimer0.c
 *
 * Created: 4/6/2025 7:33:29 PM
 *  Author: Ervin Gomez 231226
 */ 

#include "PWMTimer0.h"
void PWM0A(uint8_t invertido, uint16_t presc)
{
	DDRD |=(1<< DDD6);
	
	TCCR0A &= ~(1<<COM0A1) | (1<<COM0A0);
	if (invertido == invt)
	{
		TCCR0A |=(1<<COM0A1) | (1<<COM0A0); //modo invertido
	}
	else
	{
		TCCR0A |=(1<<COM0A1); //modo no invertido
	}
	TCCR0A |= (1<< WGM01) | (1<< WGM00);

	TCCR0B &= ~(1<<CS02) | (1<<CS01) | (1<<CS00);
	switch(presc){
		case 1:
		TCCR0B |= (1<<CS00);
		break;
		case 8:
		TCCR0B |= (1<<CS01);
		break;
		case 64:
		TCCR0B |= (1<<CS01) | (1<<CS00);
		break;
		case 256:
		TCCR0B |= (1<<CS02);
		break;
		case 1024:
		TCCR0B |= (1<<CS02) | (1<<CS00);
		break;
		default:
		break;
	}
	TCCR0B |= (1 << CS02); //256 de prescaler
}
void updateDutyCycle(uint8_t duty)
{
	OCR0A = duty;
}
