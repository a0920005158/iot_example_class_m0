
#include "main.h"

extern volatile uint32_t timer6_tick;

void delay_us(uint32_t tick_number)
{
	uint32_t currentTick;
	
	currentTick=timer6_tick;
	while( (timer6_tick-currentTick) < tick_number )
	{
		__NOP();
	}

}