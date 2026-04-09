
#include "main.h"

#define All_ledOn  1
#define All_ledOff 2
#define Odd_ledOn  3
#define Even_ledOn 4
#define Bit_ledOn  5
#define Bit_oneOn  6

void led_change(int mode)
{
	
	switch(mode) {
		case All_ledOn:
			GPIOA->ODR |= 0x3ul | 0x3ul << 9;
			GPIOB->ODR |= 0x3ul << 12;
			GPIOC->ODR |= 0x3ul;
			break;
		
		case All_ledOff:
			GPIOA->ODR &= ~(0x3ul | 0x3ul << 9);
			GPIOB->ODR &= ~(0x3ul << 12);
			GPIOC->ODR &= ~(0x3ul);
			break;
		
		case Odd_ledOn:
			GPIOA->ODR |= 0x1ul | 0x1ul<<9;
			GPIOB->ODR |= 0x1ul << 12;
			GPIOC->ODR |= 0x1ul;
			break;
		
		case Even_ledOn:
			GPIOA->ODR |= 0x1ul<<1 | 0x1ul << 10;
			GPIOB->ODR |= 0x1ul << 13;
			GPIOC->ODR |= 0x1ul << 1;
			break;
		
		case Bit_ledOn:
			GPIOA->ODR |= 0x1ul;
			HAL_Delay(300);
			GPIOA->ODR |= 0x1ul << 1;
			HAL_Delay(300);
			GPIOA->ODR |= 0x1ul << 9;
			HAL_Delay(300);
			GPIOA->ODR |= 0x1ul << 10;
			HAL_Delay(300);
		
			GPIOB->ODR |= 0x1ul << 12;
			HAL_Delay(300);
			GPIOB->ODR |= 0x1ul << 13;
			HAL_Delay(300);
		
			GPIOC->ODR |= 0x1ul;
			HAL_Delay(300);
			GPIOC->ODR |= 0x1ul << 1;
			HAL_Delay(300);
			
			GPIOC->ODR &= ~(0x1ul << 1);
			HAL_Delay(300);
			GPIOC->ODR &= ~0x1ul;
			HAL_Delay(300);
			GPIOB->ODR &= ~(0x1ul << 13);
			HAL_Delay(300);
			GPIOB->ODR &= ~(0x1ul << 12);
			HAL_Delay(300);
			GPIOA->ODR &= ~(0x1ul << 10);
			HAL_Delay(300);
			GPIOA->ODR &= ~(0x1ul << 9);
			HAL_Delay(300);
			GPIOA->ODR &= ~(0x1ul << 1);
			HAL_Delay(300);
			GPIOA->ODR &= ~0x1ul;
			HAL_Delay(300);
			break;
		case Bit_oneOn:
			GPIOA->ODR |= 0x1ul;
			HAL_Delay(300);
			GPIOA->ODR &= ~0x1u;
			HAL_Delay(300);
		
			GPIOA->ODR |= 0x1ul << 1;
			HAL_Delay(300);
			GPIOA->ODR &= ~(0x1ul << 1);
			HAL_Delay(300);
		
			GPIOA->ODR |= 0x1ul << 9;
			HAL_Delay(300);
			GPIOA->ODR &= ~(0x1ul << 9);
			HAL_Delay(300);
		
			GPIOA->ODR |= 0x1ul << 10;
			HAL_Delay(300);
			GPIOA->ODR &= ~(0x1ul << 10);
			HAL_Delay(300);
		
			GPIOB->ODR |= 0x1ul << 12;
			HAL_Delay(300);
			GPIOA->ODR &= ~(0x1ul << 12);
			HAL_Delay(300);
			GPIOB->ODR |= 0x1ul << 13;
			HAL_Delay(300);
			GPIOA->ODR &= ~(0x1ul << 13);
			HAL_Delay(300);
		
			GPIOC->ODR |= 0x1ul;
			HAL_Delay(300);
			GPIOA->ODR &= ~0x1ul;
			HAL_Delay(300);
			
			GPIOC->ODR |= 0x1ul << 1;
			HAL_Delay(300);
			GPIOA->ODR &= ~(0x1ul << 1);
			HAL_Delay(300);
			break;
	}

}