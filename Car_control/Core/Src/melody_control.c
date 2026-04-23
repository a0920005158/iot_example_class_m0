
#include "main.h"
#include <stdio.h>
#include "timer_control.h"
#include "melody_control.h"

//Basic tone
uint8_t note_basic[]={1,2,3,4,5,6,7,1+7,2+7,3+7,4+7,5+7,6+7,7+7,1+14,2+14,3+14,4+14,5+14,6+14,7+14}; 

// Little Star Song	
const uint8_t note_little_star[]={1,1,5,5,6,6,5,4,4,3,3,2,2,1,5,5,4,4,3,3,2,5,5,4,4,3,3,2,1,1,5,5,6,6,5,4,4,3,3,2,2,1};
		
const uint16_t beat_little_star[]={500,500,500,500,500,500,1000,500,500,500,500,500,500,1000,500,500,500,500,500,500,
	1000,500,500,500,500,500,500,1000,500,500,500,500,500,500,1000,500,500,500,500,500,500,1000};
	
	
//Little Bee Song	
const uint8_t  note_little_bee[]={5,3,3,4,2,2,1,2,3,4,5,5,5,5,3,3,4,2,2,1,3,5,5,3,
		                          2,2,2,2,2,3,4,3,3,3,3,3,4,5,5,3,3,4,2,2,1,3,5,5,1};	
		
const uint16_t beat_little_bee[]={250,250,500,250,250,500,250,250,250,250,250,250,500,250,250,500,250,250,500,250,250,250,250,1000,
	250,250,250,250,250,250,500,250,250,250,250,250,250,500,250,250,500,250,250,500,250,250,250,250,1000};
	
// Happy Birthday Song
const uint8_t note_happy_song[]={5,5,6,5,1+7,7,0,5,5,6,5,2+7,1+7,5,5,5+7,3+7,1+7,7,6,0,4+7,4+7,3+7,1+7,2+7,1+7};

const uint16_t beat_happy_song[]={250,250,500,500,500,500,500,250,250,500,500,500,1000,
                            250,250,500,500,500,500,1500,500,250,250,500,500,500,1000};

// sun day
const uint8_t sun_day_song[] = {
  3, 2, 1, 5,
  3, 2, 1, 5,
  3, 2, 1, 5,
  1, 1, 7-7, 1,
  3, 2, 1, 5,
  3, 2, 1, 5,
  3, 2, 1, 5,
  1, 2, 3, 1
};
int beat_sun_day_song[] = {
  250, 250, 250, 250,
  250, 250, 250, 250,
  250, 250, 250, 250,
  250, 250, 250, 250,
  250, 250, 250, 250,
  250, 250, 250, 250,
  250, 250, 250, 250,
  250, 250, 500, 500
};

// Beatles - Let It Be (Chorus)
int beatles_song[] = {
  1+7, 7, 6, 5,
  6, 5, 3, 1, 
  1+7, 7, 6, 5,
  3, 2, 1, 1,
  1+7, 7, 6, 5,
  6, 5, 3, 1,
  3, 2, 2, 1,
  1
};

int beat_beatles_song[] = {
  500, 250, 250, 500,
  250, 250, 500, 500,
  500, 250, 250, 500,
  250, 250, 500, 500,
  500, 250, 250, 500,
  250, 250, 500, 500,
  500, 500, 500, 500,
  500
};

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

void playMelody(uint8_t song_num)
{
	uint32_t beatValue, toneValue;
	const uint32_t soundStop = 100;
	
	switch(song_num){
		case Song_1:
			printf("play listle star\n\r");
			enable_buzz();
			for(int i=0;i<sizeof(note_little_star);i++){
				toneValue = note_little_star[i];
				toneValue+=7;
				select_tone(toneValue);
				beatValue = beat_little_star[i];
				Delay_timer6(beatValue);
				disable_buzzer();
				Delay_timer6(soundStop);
				if(song_number!=Song_1)
					break;
				enable_buzz();
			}
			break;
		
		case Song_2:
			printf("play little bee\n\r");
			for(int i=0;i<sizeof(note_little_bee);i++){
				toneValue = note_little_bee[i];
				toneValue+=7;
				select_tone(toneValue);
				beatValue = beat_little_bee[i];
				Delay_timer6(beatValue);
				disable_buzzer();
				Delay_timer6(soundStop);
				if(song_number!=Song_2)
					break;
				enable_buzz();
			}
			
			break;
		
		case Song_3:
			printf("play happy song\n\r");
			enable_buzz();
			for(int i=0; i<sizeof(note_happy_song);i++){
				toneValue = note_happy_song[i];
				beatValue = beat_happy_song[i];
				if(toneValue==0){
					disable_buzzer();
					Delay_timer6(beatValue);
					enable_buzz();
				}else{
					select_tone(toneValue);
					Delay_timer6(beatValue);
					disable_buzzer();
					Delay_timer6(soundStop);
					if(song_number!=Song_3)
						break;
					enable_buzz();
				}
			}
		
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
				if(song_number != Song_4)
					break;
				enable_buzz();
			}
			break;
		case Song_5:
			printf("sun day tone.\n\r");
			enable_buzz();
			for(int i=0;i<sizeof(sun_day_song);i++){
				toneValue = sun_day_song[i];
				toneValue+=7;
				select_tone(toneValue);
				beatValue = beat_sun_day_song[i];
				Delay_timer6(beatValue);
				disable_buzzer();
				Delay_timer6(soundStop);
				if(song_number!=Song_5)
					break;
				enable_buzz();
			}
			break;
		case Song_6:
			enable_buzz();
			for(int i=0;i<sizeof(beatles_song);i++){
				toneValue = beatles_song[i];
				if(toneValue==0){
					disable_buzzer();
					Delay_timer6(beatValue);
					enable_buzz();
				}else{
					select_tone(toneValue);
					beatValue = beat_beatles_song[i];
					Delay_timer6(beatValue);
					disable_buzzer();
					Delay_timer6(soundStop);
					if(song_number!=Song_6)
						break;
					enable_buzz();
				}
			}
			break;
		case Song_off:
			disable_buzzer();
			break;
	}
	
}