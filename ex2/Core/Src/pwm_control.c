#include "main.h"

void enablePWM_ch3_servo(void)
{
	TIM2->CNT =0;
	TIM2->CR1 |= 0x1ul;
	TIM2->CCER |= 0x1ul<<8;
}

void disablePWM_ch3_servo(uint32_t level)
{
	TIM2->CCER &= ~(0x1ul<<8);
	TIM2->CR1 &= ~0x1ul;
}

void pwmLevel_ch3_servo(uint32_t level)
{
	TIM2->CCR3 = level;
}
