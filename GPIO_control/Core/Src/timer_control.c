
#include "main.h"

extern volatile uint32_t timer6_tick;
extern volatile uint32_t timer7_tick;

void Delay_timer6(uint32_t tick_number)
{
	uint32_t currentTick;
	
	currentTick=timer6_tick;
	while( (timer6_tick-currentTick) < tick_number )
	{
		__NOP();
	}

}

void Delay_timer7(uint32_t tick_number)
{
	uint32_t currentTick;
	
	currentTick=timer7_tick;
	while( (timer7_tick-currentTick) < tick_number )
	{
		__NOP();
	}
}