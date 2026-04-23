
#include "main.h"
#include <stdio.h>
#include "pwm_control.h"
#include "car_direction.h"

void enable_car(void)
{
	GPIOA->ODR |= 0x1ul;
}

void disable_car(void)
{
	GPIOA->ODR &= ~0x1ul;
}

void car_direction(uint8_t direction)
{
	switch(direction){
		case Car_forward:
			pwmLevel_ch3(100);
			pwmLevel_ch4(100);
			GPIOC->ODR &= ~(0xful<<4);
			GPIOC->ODR |= 0x1ul<<4 | 0x1ul<<7;
			break;
		
		case Car_right:
			pwmLevel_ch3(100);
			pwmLevel_ch4(45);
			GPIOC->ODR &= ~(0xful<<4);
			GPIOC->ODR |= 0x1ul<<4 | 0x1ul<<7;
			break;
		
		case Car_left:
			pwmLevel_ch3(45);
			pwmLevel_ch4(100);
			GPIOC->ODR &= ~(0xful<<4);
			GPIOC->ODR |= 0x1ul<<4 | 0x1ul<<7;
			break;
		
		case Car_backward:
			GPIOC->ODR |= 0xful << 4;
			HAL_Delay(100);
			pwmLevel_ch3(80);
			pwmLevel_ch4(80);
			GPIOC->ODR &= ~(0xful<<4);
			GPIOC->ODR |= 0x1ul<<5 | 0x1ul<<6;
			break;
		
		case Car_stop:
			GPIOC->ODR |= 0xful << 4;
			break;
	}
}