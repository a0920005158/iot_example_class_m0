
#include "main.h"
#include "stdio.h"

const uint8_t command=0xd;
const uint8_t touch_addr=0x50;

void i2c_master_write(void)
{
	I2C1->CR2 |= 0x1ul<<16 | (touch_addr)<<1;
	I2C1->CR2 &= ~(0x1ul<<10 | 0x1ul<<25);
}

void i2c_master_read(void)
{
	I2C1->CR2 |= 0x1ul<<16 | (touch_addr)<<1;
	I2C1->CR2 |= 0x1ul<<10 | 0x1ul<<25;
}

void get_touchData(void){
	i2c_master_write();
	I2C1->CR2 |= 0x1ul<<13;
	
	while(!(I2C1->ISR & (0x1ul<<1))){
		if(I2C1->ISR & (0x1ul<<4)){
			printf("error 1\n\r");
			goto end;
		}
	}
	I2C1->TXDR = command;
	
	i2c_master_read();
	I2C1->CR2 |= 0x1ul<<13;
	
	while(!(I2C1->ISR & (0x1ul<<2))){
		if(I2C1->ISR & (0x1ul<<4)){
			printf("error 2\n\r");
			goto end;
		}
	}
	
	uint8_t value = I2C1->RXDR;
	printf("value=%d\n\r",value);
	
	while(!(I2C1->ISR & (0x1ul<<5))){}
	I2C1->ICR |= 0x1ul<<5;
	return;
		
	end:
		I2C1->ICR = 0x1ul<<4 | 0x1ul<<5;
}