
#include "main.h"
#include "rc522_control.h"



void RC522_CS_LOW(void)
{
	GPIOA->ODR &= ~(0x1ul<<4); 
}

void RC522_CS_HIGH(void)
{
	GPIOA->ODR |= 0x1ul<<4;
}

void RC522_RST_LOW(void)
{
	GPIOB->ODR &= ~0x1ul;
}

void RC522_RST_HIGH(void){
	GPIOB->ODR |= 0x1ul;
}

uint8_t SPI1_Transfer(uint8_t data)
{
    // ?? TX ?
    while (!(SPI1->SR & SPI_SR_TXE));

    *(volatile uint8_t*)&SPI1->DR = data;

    // ?? RX ??
    while (!(SPI1->SR & SPI_SR_RXNE));
		uint8_t value = *(volatile uint8_t*)&SPI1->DR;
     
    return value;
}

void RC522_WriteReg(uint8_t addr, uint8_t val)
{
    RC522_CS_LOW();

    SPI1_Transfer((addr << 1) & 0x7E);
    SPI1_Transfer(val);

    RC522_CS_HIGH();
}

uint8_t RC522_ReadReg(uint8_t addr)
{
    uint8_t val;

    RC522_CS_LOW();

    SPI1_Transfer(((addr << 1) & 0x7E) | 0x80);
    val = SPI1_Transfer(0x00);

    RC522_CS_HIGH();

    return val;
}


void RC522_SetBitMask(uint8_t reg, uint8_t mask)
{
    RC522_WriteReg(reg, RC522_ReadReg(reg) | mask);
}

void RC522_ClearBitMask(uint8_t reg, uint8_t mask)
{
    RC522_WriteReg(reg, RC522_ReadReg(reg) & (~mask));
}

void RC522_AntennaOn(void)
{
    uint8_t temp = RC522_ReadReg(TxControlReg);

    if (!(temp & 0x03))
    {
        RC522_SetBitMask(TxControlReg, 0x03);
    }
}

//#define CommandReg      0x01
//#define PCD_RESETPHASE  0x0F

void RC522_Reset(void)
{
    RC522_WriteReg(CommandReg, PCD_RESETPHASE);
    HAL_Delay(50);
}

void RC522_Init(void)
{
    RC522_CS_HIGH();

    RC522_RST_LOW();
    HAL_Delay(50);
    RC522_RST_HIGH();
    HAL_Delay(50);

    RC522_Reset();

    RC522_WriteReg(TModeReg, 0x8D);
    RC522_WriteReg(TPrescalerReg, 0x3E);
    RC522_WriteReg(TReloadRegL, 30);
    RC522_WriteReg(TReloadRegH, 0);

    RC522_WriteReg(TxASKReg, 0x40);
    RC522_WriteReg(ModeReg, 0x3D);

    RC522_AntennaOn();
}

uint8_t RC522_ToCard(uint8_t command, uint8_t *sendData,uint8_t sendLen, uint8_t *backData, uint16_t *backLen)
{
    uint8_t status = MI_ERR;
    uint8_t irqEn = 0x00;
    uint8_t waitIRq = 0x00;
    uint8_t n;
    uint16_t i;

    if (command == PCD_TRANSCEIVE)
    {
        irqEn = 0x77;
        waitIRq = 0x30;
    }

    RC522_WriteReg(ComIEnReg, irqEn | 0x80);
    RC522_ClearBitMask(ComIrqReg, 0x80);
    RC522_SetBitMask(FIFOLevelReg, 0x80);

    RC522_WriteReg(CommandReg, PCD_IDLE);

    for (i = 0; i < sendLen; i++)
    {
        RC522_WriteReg(FIFODataReg, sendData[i]);
    }

    RC522_WriteReg(CommandReg, command);

    if (command == PCD_TRANSCEIVE)
    {
        RC522_SetBitMask(BitFramingReg, 0x80);
    }

    i = 2000;

    do
    {
        n = RC522_ReadReg(ComIrqReg);
        i--;
    }
    while ((i != 0) && !(n & 0x01) && !(n & waitIRq));

    RC522_ClearBitMask(BitFramingReg, 0x80);

    if (i != 0)
    {
        if (!(RC522_ReadReg(ErrorReg) & 0x1B))
        {
            status = MI_OK;

            if (n & 0x01)
            {
                status = MI_NOTAGERR;
            }

            if (command == PCD_TRANSCEIVE)
            {
                n = RC522_ReadReg(FIFOLevelReg);
                uint8_t lastBits = RC522_ReadReg(ControlReg) & 0x07;

                if (lastBits)
                    *backLen = (n - 1) * 8 + lastBits;
                else
                    *backLen = n * 8;

                if (n == 0)
                    n = 1;

                if (n > 16)
                    n = 16;

                for (i = 0; i < n; i++)
                {
                    backData[i] = RC522_ReadReg(FIFODataReg);
                }
            }
        }
    }

    return status;
}

uint8_t RC522_Request(uint8_t reqMode, uint8_t *tagType)
{
    uint8_t status;
    uint16_t backBits;

    RC522_WriteReg(BitFramingReg, 0x07);

    tagType[0] = reqMode;

    status = RC522_ToCard(PCD_TRANSCEIVE, tagType, 1, tagType, &backBits);

    if ((status != MI_OK) || (backBits != 0x10))
    {
        status = MI_ERR;
    }

    return status;
}

uint8_t RC522_Anticoll(uint8_t *serNum)
{
    uint8_t status;
    uint8_t i;
    uint8_t serNumCheck = 0;
    uint16_t unLen;

    RC522_WriteReg(BitFramingReg, 0x00);

    serNum[0] = PICC_ANTICOLL;
    serNum[1] = 0x20;

    status = RC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

    if (status == MI_OK)
    {
        for (i = 0; i < 4; i++)
        {
            serNumCheck ^= serNum[i];
        }

        if (serNumCheck != serNum[4])
        {
            status = MI_ERR;
        }
    }

    return status;
}

uint8_t RC522_ReadUID(uint8_t *uid)
{
    uint8_t status;
    uint8_t tagType[2];

    status = RC522_Request(PICC_REQIDL, tagType);

    if (status != MI_OK)
    {
        return MI_NOTAGERR;
    }

    status = RC522_Anticoll(uid);

    if (status == MI_OK)
    {
        return MI_OK;
    }

    return MI_ERR;
}