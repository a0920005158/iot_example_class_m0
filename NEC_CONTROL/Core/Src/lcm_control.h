#include "main.h"

void HD44780A_Out_4bit(uint8_t data);
void HD44780A_Enable_Pulse(void);
void HD44780A_Write(uint8_t value, uint8_t mode);
void LCM_Send_Cmd(uint8_t cmd);
void LCM_Send_Data(uint8_t data);
void LCM_Init(void);
void LCM_Set_Cursor(int row, int col);
void LCM_Send_String(char *str);