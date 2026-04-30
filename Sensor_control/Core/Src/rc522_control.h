#include "main.h"

#define MI_OK       0
#define MI_NOTAGERR 1
#define MI_ERR      2

#define PICC_REQIDL 0x26
#define PICC_ANTICOLL 0x93

void RC522_Init(void);
uint8_t RC522_ReadUID(uint8_t *uid);

uint8_t RC522_ReadReg(uint8_t addr);

/* MFRC522 registers */
#define CommandReg      0x01
#define ComIEnReg       0x02
#define ComIrqReg       0x04
#define ErrorReg        0x06
#define FIFODataReg     0x09
#define FIFOLevelReg    0x0A
#define ControlReg      0x0C
#define BitFramingReg   0x0D
#define ModeReg         0x11
#define TxControlReg    0x14
#define TxASKReg        0x15
#define TModeReg        0x2A
#define TPrescalerReg   0x2B
#define TReloadRegH     0x2C
#define TReloadRegL     0x2D

/* MFRC522 commands */
#define PCD_IDLE        0x00
#define PCD_TRANSCEIVE  0x0C
#define PCD_RESETPHASE  0x0F