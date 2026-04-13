
#include "main.h"

void relay1_on(void)
{
	GPIOC->ODR = 0x1ul;
	HAL_Delay(200);	
}

void relay1_off(void)
{
	GPIOC->ODR &= ~0x1ul;
	HAL_Delay(200);
}

void relay2_on(void)
{
	GPIOC->ODR |= 0x1ul<<1;
	HAL_Delay(200);
}

void relay2_off(void)
{
	GPIOC->ODR &= ~(0x1ul<<1);
	HAL_Delay(200);
}

void relay3_on(void)
{
	GPIOC->ODR |= 0x1ul<<2;
	HAL_Delay(200);
}

void relay3_off(void)
{
	GPIOC->ODR &= ~(0x1ul<<2);
	HAL_Delay(200);
}

void relay4_on(void)
{
	GPIOC->ODR |= 0x1ul<<3;
	HAL_Delay(200);
}

void relay4_off(void)
{
	GPIOC->ODR &= ~(0x1ul<<3);
	HAL_Delay(200);
}
