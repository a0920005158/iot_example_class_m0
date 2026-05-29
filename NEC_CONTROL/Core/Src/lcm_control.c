#include "main.h"

#define LCM_RS_PORT GPIOB
#define LCM_RS_PIN GPIO_PIN_0
#define LCM_E_PORT GPIOB
#define LCM_E_PIN GPIO_PIN_1

void HD44780A_Out_4bit(uint8_t data){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, (data >> 0) & 0x01ul);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (data >> 1) & 0x01ul);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, (data >> 2) & 0x01ul);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, (data >> 3) & 0x01ul);
}

void HD44780A_Enable_Pulse(void){
		HAL_GPIO_WritePin(LCM_E_PORT, LCM_E_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCM_E_PORT, LCM_E_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
}

void HD44780A_Write(uint8_t value, uint8_t mode) {
    HAL_GPIO_WritePin(LCM_RS_PORT, LCM_RS_PIN, mode);
    
    HD44780A_Out_4bit(value >> 4);
    HD44780A_Enable_Pulse();
    
    HD44780A_Out_4bit(value & 0x0F);
    HD44780A_Enable_Pulse();
}

void LCM_Send_Cmd(uint8_t cmd) {
    HD44780A_Write(cmd, 0);
    if (cmd == 0x01 || cmd == 0x02) {
        HAL_Delay(2);
    } else {
        HAL_Delay(1);
    }
}

void LCM_Send_Data(uint8_t data) {
    HD44780A_Write(data, 1);
    HAL_Delay(1);
}

void LCM_Init(void) {
    HAL_Delay(50);
    
    HAL_GPIO_WritePin(LCM_RS_PORT, LCM_RS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCM_E_PORT, LCM_E_PIN, GPIO_PIN_RESET);
    
    //HD44780A_Out_4bit(0x03ul); HD44780A_Enable_Pulse(); HAL_Delay(5);
    //HD44780A_Out_4bit(0x03ul); HD44780A_Enable_Pulse(); HAL_Delay(1);
    //HD44780A_Out_4bit(0x03ul); HD44780A_Enable_Pulse(); HAL_Delay(1);
    HD44780A_Out_4bit(0x02ul); HD44780A_Enable_Pulse(); HAL_Delay(1); //4bit model
    
    LCM_Send_Cmd(0x28ul); // Function Set: 4bit 2row 5x8
		LCM_Send_Cmd(0x0Cul); // Display on/off: cursor open/close
    LCM_Send_Cmd(0x01ul); // clear display
		LCM_Send_Cmd(0x06ul); // entry mode set: cursor shift right
}

void LCM_Set_Cursor(int row, int col) {
    uint8_t address = (row == 0) ? (0x00 + col) : (0x40 + col);
    LCM_Send_Cmd(0x80 | address);
}

void LCM_Send_String(char *str) {
    while (*str) LCM_Send_Data(*str++);
}