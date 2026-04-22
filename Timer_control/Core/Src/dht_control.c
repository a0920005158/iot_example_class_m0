
#include "main.h"
#include <stdio.h>
#include <stdbool.h>
#include "dht_control.h"

char humString[8];
char tempString[8];

void set_high(void)
{
	GPIOA->ODR |= 0x1ul << 12;
}

void set_low(void)
{
	GPIOA->ODR &= ~(0x1ul<<12);
}

void set_output(void)
{
	GPIOA->MODER &= ~(0x3ul<< 12*2);
	GPIOA->MODER |= 0x1ul << 12*2;
}

void set_input(void)
{
	GPIOA->MODER &= ~(0x3ul<< 12*2);
}

bool getData_DHT22(void)
{
	uint32_t startTick, pulseWidth, pulseLow;
	uint32_t data[43];
	uint32_t data_low[43];
	bool resultFlag;
	uint32_t dataValue, parityData, humData, tempData;
	uint32_t checkData, checkParity;
	float tempFinal, humFinal;
	
	set_low();
	HAL_Delay(5);
	set_high();
//	for (int i=0;i<100;i++)
//		__NOP();
	
	startTick = timer6_tick;
	resultFlag = true;
	set_input();
	
	for(int i=0; i<42; i++){
		pulseLow=0;
		pulseWidth=0;
		
		while((GPIOA->IDR & (0x1ul<<12)) == 0){
			pulseLow++;
			if(timer6_tick - startTick>500) {
				resultFlag = false;
				break;
			}
		}
		data_low[i]=pulseLow;
		
		while(GPIOA->IDR & (0x1ul<<12)){
			pulseWidth++;
			if(timer6_tick - startTick>500) {
				resultFlag = false;
				break;
			}
		}
		data[i]=pulseWidth;
		
	}
	
	int time = timer6_tick-startTick;
	printf("\n\rtime = %d ms \n\r",time);
//	for(int i=0; i<42; i++){
//		printf("%d low value = %d\n\r",i, data_low[i]);
//		printf("%d high value = %d\n\r",i, data[i]);
//	}
	
	set_output();
	set_high();
	
	if(resultFlag == false)
		return resultFlag;
	
	dataValue = 0;
	parityData = 0;
	
	for(int i=2; i<42; i++){
		if(i<34){
			if(data[i]>200)
				dataValue |= 0x1ul;
			
			if(i<33)
				dataValue = dataValue<<1;
		} else {
			if(data[i]>200)
				parityData |= 0x1ul;
			
			if(i<41)
				parityData = parityData<<1;
		}
	}
	
	printf("data value = %x \n\r",dataValue);
	printf("parity value %x \n\r",parityData);
	
	checkParity=0;
	checkData = dataValue;
	for(int i=0;i<4;i++) {
		checkParity += checkData & 0xff;
		checkData = checkData>>8;
	}
	checkParity = checkParity & 0xff;
	
	printf("check parity value = %x \n\r",checkParity);
	
	if(checkParity == parityData){
		tempData = dataValue & 0xffff;
		humData = (dataValue >> 16) & 0xffff;
		tempFinal = tempData/10.0;
		humFinal = humData/10.0;
		
		printf("temperature = %0.2f \n\r",tempFinal);
		printf("humidity = %0.2f \n\r",humFinal);
		
		sprintf(tempString,"%0.2f",tempFinal);
		sprintf(humString,"%0.2f",humFinal);
//		printf("temp string = %s\n\r",tempString);
//		printf("hum string = %s\n\r",humString);
	} else {
		resultFlag = false;
	}
	
	return resultFlag;
}

void set_high_dht11(void)
{
	GPIOA->ODR |= 0x1ul << 11;
}

void set_low_dht11(void)
{
	GPIOA->ODR &= ~(0x1ul<<11);
}

void set_output_dht11(void)
{
	GPIOA->MODER &= ~(0x3ul<< 11*2);
	GPIOA->MODER |= 0x1ul << 11*2;
}

void set_input_dht11(void)
{
	GPIOA->MODER &= ~(0x3ul<< 11*2);
}


bool getData_DHT11(void)
{
	uint32_t startTick, pulseWidth, pulseLow;
	uint32_t data[43];
	uint32_t data_low[43];
	bool resultFlag;
	uint32_t dataValue, parityData, humData, tempData;
	uint32_t checkData, checkParity;
	
	set_low_dht11();
	HAL_Delay(18);
	set_high_dht11();
//	for (int i=0;i<100;i++)
//		__NOP();
	
	startTick = timer6_tick;
	resultFlag = true;
	set_input_dht11();
	
	for(int i=0; i<42; i++){
		pulseLow=0;
		pulseWidth=0;
		
		while((GPIOA->IDR & (0x1ul<<11)) == 0){
			pulseLow++;
			if(timer6_tick - startTick>500) {
				resultFlag = false;
				break;
			}
		}
		data_low[i]=pulseLow;
		
		while(GPIOA->IDR & (0x1ul<<11)){
			pulseWidth++;
			if(timer6_tick - startTick>500) {
				resultFlag = false;
				break;
			}
		}
		data[i]=pulseWidth;
		
	}
	
	int time = timer6_tick-startTick;
	printf("\n\rtime = %d ms \n\r",time);
//	for(int i=0; i<42; i++){
//		printf("%d low value = %d\n\r",i, data_low[i]);
//		printf("%d high value = %d\n\r",i, data[i]);
//	}
//	
	set_output_dht11();
	set_high_dht11();
	
	if(resultFlag == false)
		return resultFlag;
	
	dataValue = 0;
	parityData = 0;
	
	for(int i=2; i<42; i++){
		if(i<34){
			if(data[i]>150)
				dataValue |= 0x1ul;
			
			if(i<33)
				dataValue = dataValue<<1;
		} else {
			if(data[i]>150)
				parityData |= 0x1ul;
			
			if(i<41)
				parityData = parityData<<1;
		}
	}
	
	printf("data value = %x \n\r",dataValue);
	printf("parity value %x \n\r",parityData);

	checkParity=0;
	checkData = dataValue;
	for(int i=0;i<4;i++) {
		checkParity += checkData & 0xff;
		checkData = checkData>>8;
	}
	checkParity = checkParity & 0xff;
	
	printf("check parity value = %x \n\r",checkParity);
	
	if(checkParity == parityData){
		tempData = dataValue & 0xffff;
		humData = (dataValue >> 16) & 0xffff;
		
		printf("temperature = %0.2f \n\r",tempData/10.0);
		printf("humidity = %0.2f \n\r",humData/10.0);
		
		sprintf(tempString,"%0.2f",tempData/10.0);
		sprintf(humString,"%0.2f",humData/10.0);
//		printf("temp string = %s\n\r",tempString);
//		printf("hum string = %s\n\r",humString);
	} else {
		resultFlag = false;
	}
	
	return resultFlag;
}