
#include "main.h" 
#include <stdbool.h>

extern volatile uint32_t timer6_tick;
extern volatile uint8_t count_10sec;

bool getData_DHT22(void);
bool getData_DHT11(void);