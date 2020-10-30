#include "bsp_oled.h"

extern unsigned int timer;

void Delay_us(unsigned int us) {
	timer = us;
	SysTick->CTRL |= (1 << 0);
	while (timer);
	SysTick->CTRL &= ~(1 << 0);
}

//dat:要写入的数据/命令
//cmd：0表示命令，1表示数据
void OLED_WR_Byte(unsigned char dat, unsigned int cmd)
{
	unsigned int i;
	
	if(cmd)
		OLED_DC_Set();
	else
		OLED_DC_Clr();
	
	OLED_CS_Clr();
	
	for(i = 0; i < 8; i++)
	{
		OLED_SCLK_Clr();
		if(dat & 0x80)
			OLED_SDIN_Set();
		else
			OLED_SDIN_Clr();
		OLED_SCLK_Set();
		
		dat <<= 1;
	}
	
	OLED_CS_Set();
}

void OLED_Clear(void)
{
	unsigned int i, j;
	
	for(i = 0; i < 8; i++)
	{
		OLED_WR_Byte(0xb0 + i, OLED_CMD);  //设置page地址
		OLED_WR_Byte(0x00, OLED_CMD);      //设置列地址的低位
		OLED_WR_Byte(0x10, OLED_CMD);			 //设置列地址的高位
		for(j = 0; j < 128; j++)
			OLED_WR_Byte(0x0, OLED_DATA);
	}
}

//x:表示的列，分为（列低地址和列高地址）， y:表示的是page页编号(0~7)
void OLED_Set_Pos(unsigned int x, unsigned int y)
{
	OLED_WR_Byte(0xb0 + y, OLED_CMD);
	
	OLED_WR_Byte((x&0x0F), OLED_CMD);
	OLED_WR_Byte((x&0xF0)>>4 | 0x10, OLED_CMD);
}

//y0~y1的取值范围是0~7，x0~x1的取值范围是0~127
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char bmp[])
{
	unsigned int i = 0;
	unsigned char x, y;
	
	for(y = y0; y <= y1; y++)
	{
		OLED_Set_Pos(x0, y);
		for(x = x0; x <= x1; x++)
		{
			OLED_WR_Byte(bmp[i++], OLED_DATA);
		}
	}
}


void OLED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
	
	OLED_RST_Set();
	Delay_us(100000);
	OLED_RST_Clr();
	Delay_us(20);
	OLED_RST_Set();
	
	OLED_WR_Byte(0xA8, OLED_CMD);
	OLED_WR_Byte(0x3F, OLED_CMD);
	OLED_WR_Byte(0xD3, OLED_CMD);
	OLED_WR_Byte(0x00, OLED_CMD);
	OLED_WR_Byte(0x40, OLED_CMD);
	OLED_WR_Byte(0xA1, OLED_CMD);   //A0/A1:控制屏幕显示左右映射翻转的
	OLED_WR_Byte(0xC8, OLED_CMD);   //C0/C8：控制屏幕上下映射翻转的
	OLED_WR_Byte(0xDA, OLED_CMD);
	OLED_WR_Byte(0x12, OLED_CMD);   //02h:隔行显示  12h:逐行显示
	OLED_WR_Byte(0x81, OLED_CMD);
	OLED_WR_Byte(0x7F, OLED_CMD);
	OLED_WR_Byte(0xA4, OLED_CMD);
	OLED_WR_Byte(0xA6, OLED_CMD);
	OLED_WR_Byte(0xD5, OLED_CMD);
	OLED_WR_Byte(0x80, OLED_CMD);
	OLED_WR_Byte(0x8D, OLED_CMD);
	OLED_WR_Byte(0x14, OLED_CMD);
	OLED_WR_Byte(0xAF, OLED_CMD);
	
	OLED_Clear();
	OLED_Set_Pos(0, 0);
}

