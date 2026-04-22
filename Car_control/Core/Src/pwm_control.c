
#include "main.h"

void enablePWM_ch1(void)
{
	TIM3->CNT =0;
	TIM3->CR1 |= 0x1ul;
	TIM3->CCER |= 0x1ul;
}

void disablePWM_ch1(void)
{
	TIM3->CCER &= ~0x1ul;
	TIM3->CR1 &= ~0x1ul;
}

void pwmLevel_ch1(uint32_t level)
{
	TIM3->CCR1 = level;
}

void enablePWM_ch2(void)
{
	TIM3->CNT =0;
	TIM3->CR1 |= 0x1ul;
	TIM3->CCER |= 0x1ul<<4;
}

void disablePWM_ch2(uint32_t level)
{
	TIM3->CCER &= ~(0x1ul<<4);
	TIM3->CR1 &= ~0x1ul;
}

void pwmLevel_ch2(uint32_t level)
{
	TIM3->CCR2 = level;
}

void enablePWM_ch3(void)
{
	TIM3->CNT =0;
	TIM3->CR1 |= 0x1ul;
	TIM3->CCER |= 0x1ul<<8;
}

void disablePWM_ch3(uint32_t level)
{
	TIM3->CCER &= ~(0x1ul<<8);
	TIM3->CR1 &= ~0x1ul;
}

void pwmLevel_ch3(uint32_t level)
{
	TIM3->CCR3 = level;
}

void enablePWM_ch4(void)
{
	TIM3->CNT =0;
	TIM3->CR1 |= 0x1ul;
	TIM3->CCER |= 0x1ul<<12;
}

void disablePWM_ch4(uint32_t level)
{
	TIM3->CCER &= ~(0x1ul<<12);
	TIM3->CR1 &= ~0x1ul;
}

void pwmLevel_ch4(uint32_t level)
{
	TIM3->CCR4 = level;
}

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

void enablePWM_ch4_servo(void)
{
	TIM2->CNT =0;
	TIM2->CR1 |= 0x1ul;
	TIM2->CCER |= 0x1ul<<12;
}

void disablePWM_ch4_servo(uint32_t level)
{
	TIM2->CCER &= ~(0x1ul<<12);
	TIM2->CR1 &= ~0x1ul;
}

void pwmLevel_ch4_servo(uint32_t level)
{
	TIM2->CCR4 = level;
}


