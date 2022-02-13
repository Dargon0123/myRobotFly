/***************************************************************************************
                                      声  明
    本项目代码仅供个人学习使用，可以自由移植修改，但必须保留此声明信息。移植过程中出现
其他不可估量的BUG，天际智联不负任何责任。请勿商用！

程序版本：2.1
更新日期：2018-1-23
程序作者：愤怒的小孩，东方萧雨
版权所有：西安天际智联信息技术有限公司
****************************************************************************************/
#include "led.h"
#include "systick.h"

// RGB七彩跑马灯 浪费内存啊！
static u32 Run_buf[][16] = 
{
	{0xFFA500,0,0,0,0xFFA500,0,0,0,0xFFA500,0,0,0,0xFFA500,0,0,0,},//橙色
	{0x00FF00,0,0,0,0x00FF00,0,0,0,0x00FF00,0,0,0,0x00FF00,0,0,0,},//绿色
	{0xFF00FF,0,0,0,0xFF00FF,0,0,0,0xFF00FF,0,0,0,0xFF00FF,0,0,0,},//紫色
	{0x00FFFF,0,0,0,0x00FFFF,0,0,0,0x00FFFF,0,0,0,0x00FFFF,0,0,0,},//青色
	{0x0000FF,0,0,0,0x0000FF,0,0,0,0x0000FF,0,0,0,0x0000FF,0,0,0,},//蓝色
	{0xFFFF00,0,0,0,0xFFFF00,0,0,0,0xFFFF00,0,0,0,0xFFFF00,0,0,0,},//黄色
	{0xFFFFFF,0,0,0,0xFFFFFF,0,0,0,0xFFFFFF,0,0,0,0xFFFFFF,0,0,0,},//白色
	
};

void LED_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructus;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructus.GPIO_Pin = LED1|RGBLED;
	GPIO_InitStructus.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructus.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB,&GPIO_InitStructus);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructus.GPIO_Pin = LED2;
	GPIO_InitStructus.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructus.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC,&GPIO_InitStructus);
	
	LED_Off(LED1);
}

//点亮LED灯
void LED_On(u16 LEDx)
{
	u16 led;
	led =LEDx;
	switch(led)
	{
		case LED1: GPIO_ResetBits(GPIOB,LED1); break;
		case LED2: GPIO_ResetBits(GPIOC,LED2); break;
		case RGBLED: GPIO_ResetBits(GPIOB,RGBLED); break;
		default: break;
	}
}

void LED_Off(u16 LEDx)
{
	u16 led;
	led =LEDx;
	switch(led)
	{
		case LED1: GPIO_SetBits(GPIOB,LED1); break;
		case LED2: GPIO_SetBits(GPIOC,LED2); break;
		case RGBLED: GPIO_SetBits(GPIOB,RGBLED); break;
		default: break;
	}
}

//开关LED
void LED_Toggle(u16 LEDx)
{
	u16 led;
	led =LEDx;
	switch(led)
	{
		case LED1: GPIOB->ODR ^= LED1; break;
		case LED2: GPIOC->ODR ^= LED2; break;
		case RGBLED: GPIOB->ODR ^= RGBLED; break;
		default: break;
	}
	// GPIOC->ODR ^= LEDx;	//异或，开关模式输出高低电平
}

/********************************************************************************
* 函  数：void Write0(void)
* 功  能：写 0码 函数
* 参  数：无
* 返回值：无
* 备  注: 根据RGB灯手册查得 ：RGB_H 延时 300ns，RGB_L 延时 900ns
*		  RGB_H，RGB_L之间的延时，根据不同芯片的主频实际调节__nop()函数的个数	  
*********************************************************************************/
void Write0(void)
{
	RGB_H;
	__nop();__nop();__nop();__nop();__nop();__nop();
	
	RGB_L;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}


/********************************************************************************
* 函  数：void Write1(void)
* 功  能：写 1码 函数
* 参  数：无
* 返回值：无
* 备  注: 根据RGB灯手册查得 ：RGB_H 延时 600ns，RGB_L 延时 600ns
*		  RGB_H，RGB_L之间的延时，根据不同芯片的主频实际调节__nop()函数的个数	  
*********************************************************************************/
void Write1(void)
{
	RGB_H;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
	
	RGB_L;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}

/***************************************************************************
* 函  数：void RGB_WByte(uint8_t byte)
* 功  能：写一个字节（8bit）数据
* 参  数：byte 
* 返回值: 无
* 备  注: RGB的亮度通过更改 0x01 处的值进行调节
***************************************************************************/
void RGB_WByte(uint8_t byte)
{
	uint8_t i=0;
	for(i=0;i<8;i++)
	{
	  if((byte<<i)&0x01)
		  Write1();
	  else
		  Write0();
	}
}

/***************************************************************************
* 函  数：void Write24Bit(uint8_t green, uint8_t red, uint8_t blue)
* 功  能：设置一个RGB灯的色彩
* 参  数：green red blue，红绿蓝光所占比例大小,范围0~255
* 返回值: 无
* 备  注: 灯亮的顺序为GRB，每种颜色占8位数据，因此一个灯需要写24位数据
***************************************************************************/
void Write24Bit(uint8_t green, uint8_t red, uint8_t blue)
{
	RGB_WByte(green);
	RGB_WByte(red);
	RGB_WByte(blue);
}




void RGB_LED_Runing(void)
{
	uint8_t i,red=0,green=0,blue=0;
	static uint8_t cnt = 0,wcnt = 0,times = 0;
	if(times++ >= 16)
	{
	 times = 0; 
	 wcnt++;
	}
	for(i=0;i<4;i++)
	{
		if(cnt>4) cnt = 0;
		red   = ((Run_buf[wcnt][cnt]>>16)&0xff);
		green = ((Run_buf[wcnt][cnt]>>8)&0xff); 
		blue  = ((Run_buf[wcnt][cnt]>>0)&0xff);
		Write24Bit(green,red,blue);//ºÏ³ÉÑÕÉ«
		cnt++;
	}
	if(wcnt==7) wcnt = 0;  
}


void RGB_LED_Red(void)
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		Write24Bit(0,0xff,0);
	}
}


void RGB_LED_Orange(void)
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		Write24Bit(0xa5,0xff,0x00);
	}
}


void RGB_LED_Yellow(void)
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		Write24Bit(0xff,0xff,0);
	}
}


void RGB_LED_Green(void)
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		Write24Bit(0xff,0,0);
	}
}

/**************************************************************************
* º¯  Êý£ºvoid RGB_LED_Cyan(void)
* ¹¦  ÄÜ£ºÇàµÆ
* ²Î  Êý£ºÎÞ
* ·µ»ØÖµ£ºÎÞ
* ±¸  ×¢: ÎÞ
**************************************************************************/
void RGB_LED_Cyan(void)
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		Write24Bit(0xff,0,0xff);
	}
}

/**************************************************************************
* º¯  Êý£ºvoid RGB_LED_Blue(void)
* ¹¦  ÄÜ£ºÀ¶µÆ
* ²Î  Êý£ºÎÞ
* ·µ»ØÖµ£ºÎÞ
* ±¸  ×¢: ÎÞ
**************************************************************************/
void RGB_LED_Blue(void)
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		Write24Bit(0,0,0xff);
	}
}

/**************************************************************************
* º¯  Êý£ºvoid RGB_LED_Violet(void)
* ¹¦  ÄÜ£º×ÏµÆ
* ²Î  Êý£ºÎÞ
* ·µ»ØÖµ£ºÎÞ
* ±¸  ×¢: ÎÞ
**************************************************************************/
void RGB_LED_Violet(void)
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		Write24Bit(0x00,0xcd,0xcd);
	}
}

/**************************************************************************
* º¯  Êý£ºvoid RGB_LED_FLY(void)
* ¹¦  ÄÜ£ºÁ½ºìÁ½ÂÌ
* ²Î  Êý£ºÎÞ
* ·µ»ØÖµ£ºÎÞ
* ±¸  ×¢: ÎÞ
**************************************************************************/
void RGB_LED_FLY(void)
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		if(i<2)
			Write24Bit(0xff,0,0);
		else
			Write24Bit(0,0xff,0);
	}
}

/**************************************************************************
* º¯  Êý£ºvoid RGB_LED_White(void)
* ¹¦  ÄÜ£º°×µÆ
* ²Î  Êý£ºÎÞ
* ·µ»ØÖµ£ºÎÞ
* ±¸  ×¢: ÎÞ
**************************************************************************/
void RGB_LED_White(void)
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		Write24Bit(0xff,0xff,0xff);
	}
}

/**************************************************************************
* º¯  Êý£ºvoid RGB_LED_Off(void)
* ¹¦  ÄÜ£ºÀ¶µÆ
* ²Î  Êý£ºÎÞ
* ·µ»ØÖµ£ºÎÞ
* ±¸  ×¢: ÎÞ
**************************************************************************/
void RGB_LED_Off(void)
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		Write24Bit(0,0,0);
	}
}

/**************************************************************************
* º¯  Êý£ºvoid GYRO_Offset_LED(void)
* ¹¦  ÄÜ£ºÍÓÂÝÒÇÐ£×¼Íê³ÉÀ¶µÆÉÁË¸
* ²Î  Êý£ºÎÞ
* ·µ»ØÖµ£ºÎÞ
* ±¸  ×¢: ÎÞ
**************************************************************************/
void GYRO_Offset_LED(void)
{
	 RGB_LED_Off();
	 RGB_LED_Blue();
	 delay_ms(100);
	 RGB_LED_Off();
	 delay_ms(100);
	 RGB_LED_Blue();
	 delay_ms(100);
	 RGB_LED_Off();
	 delay_ms(100);
	 RGB_LED_Blue();
	 delay_ms(100);
	 RGB_LED_Off();
}

/**************************************************************************
* º¯  Êý£ºvoid ACC_Offset_LED(void)
* ¹¦  ÄÜ£º¼ÓËÙ¶ÈÐ£×¼Íê³ÉÂÌµÆÉÁË¸
* ²Î  Êý£ºÎÞ
* ·µ»ØÖµ£ºÎÞ
* ±¸  ×¢: ÎÞ
**************************************************************************/
void ACC_Offset_LED(void)
{
	 RGB_LED_Off();
	 RGB_LED_Green();
	 delay_ms(100);
	 RGB_LED_Off();
	 delay_ms(100);
	 RGB_LED_Green();
	 delay_ms(100);
	 RGB_LED_Off();
	 delay_ms(100);
	 RGB_LED_Green();
	 delay_ms(100);
	 RGB_LED_Off();
}

/**************************************************************************
* º¯  Êý£ºvoid BAR_Offset_LED(void)
* ¹¦  ÄÜ£ºÆøÑ¹¼ÆÐ£×¼Íê³É×ÏµÆÉÁË¸
* ²Î  Êý£ºÎÞ
* ·µ»ØÖµ£ºÎÞ
* ±¸  ×¢: ÎÞ
**************************************************************************/
void BAR_Offset_LED(void)
{
	 RGB_LED_Off();
	 RGB_LED_Violet();
	 delay_ms(100);
	 RGB_LED_Off();
	 delay_ms(100);
	 RGB_LED_Violet();
	 delay_ms(100);
	 RGB_LED_Off();
	 delay_ms(100);
	 RGB_LED_Violet();
	 delay_ms(100);
	 RGB_LED_Off();
}

/**************************************************************************
* º¯  Êý£ºvoid BATT_Alarm_LED(void)
* ¹¦  ÄÜ£ºµÍµçÁ¿ºìµÆ¿ìÉÁ
* ²Î  Êý£ºÎÞ
* ·µ»ØÖµ£ºÎÞ
* ±¸  ×¢: ÎÞ
**************************************************************************/
//void BATT_Alarm_LED(void)
//{
//	static uint8_t flag = 0;
//	if(BATT_LEDflag)
//	{
//		if(flag)
//		{
//			flag = 0;
//			RGB_LED_Red();
//		}
//		else
//		{
//			flag = 1;
//			RGB_LED_Off();
//		}
//	}
//}
