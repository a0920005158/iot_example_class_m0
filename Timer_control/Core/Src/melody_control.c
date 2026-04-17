
#include "main.h"
#include <stdio.h>
#include "timer_control.h"

//Basic tone
uint8_t note_basic[]={1,2,3,4,5,6,7,1+7,2+7,3+7,4+7,5+7,6+7,7+7,1+14,2+14,3+14,4+14,5+14,6+14,7+14}; 

void disable_buzzer(void)
{
	TIM14->CCER &= ~0x1ul;
	TIM14->CR1 &= ~0x1ul;
}

void enable_buzz(void)
{
	TIM14->CNT = 0;
	TIM14->CR1 |= 0x1ul;
	TIM14->CCER |= 0x1ul;
}

void select_tone(uint32_t tone_num)
{
	uint32_t arr_value;
	// program ARR register
	uint32_t ToneArr[]={0,764,681,607,573,510,454,405,382,340,303,286,255,227,202,191,170,152,143,128,114,101};
		
		arr_value = ToneArr[tone_num];
		TIM14->ARR = arr_value;
		TIM14->CNT = 0;
		TIM14->CCR1 = arr_value * 0.8;
}
#define Song_1 1
#define Song_2 2
#define Song_3 3
#define Song_4 4
#define Song_5 5
#define Song_6 6
#define Song_7 7
#define Song_off 0

void playMelody(uint8_t song_num)
{
	uint32_t beatValue, toneValue;
	const uint32_t soundStop = 100;
	
	switch(song_num){
		case Song_1:
			
			break;
		
		case Song_2:
			
			break;
		
		case Song_3:
			
			break;
		
		case Song_4:
			printf("basic tone.\n\r");
			enable_buzz();
			for(int i=0; i<sizeof(note_basic);i++){
				toneValue = note_basic[i];
				select_tone(toneValue);
				Delay_timer6(500);
				disable_buzzer();
				Delay_timer6(soundStop);
				enable_buzz();
			}
			break;
		case Song_off:
			disable_buzzer();
			break;
	}
	
}