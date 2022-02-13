#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"

#define   LED1 	    GPIO_Pin_8
#define   LED2      GPIO_Pin_13
#define   RGBLED   GPIO_Pin_9
#define   RGB_H     GPIOB->BSRR |= GPIO_Pin_9   //配置对应RGB引脚为 高电平
#define   RGB_L     GPIOB->BRR  |= GPIO_Pin_9	//配置对应RGB引脚为 低电平


void LED_Config(void);
void LED_On(u16 LEDx);
void LED_Off(u16 LEDx);
void LED_Toggle(u16 LEDx);
void LED_CyclieOn(u32 delayms);

void LED_Init(void);
void LED_Run(void);
void RGB_LED_Rand(void);
void RGB_LED_Runing(void);
void RGB_LED_Off(void);
void RGB_LED_Red(void);
void RGB_LED_Orange(void);
void RGB_LED_Yellow(void);
void RGB_LED_green(void);
void RGB_LED_Green(void);
void RGB_LED_Cyan(void);
void RGB_LED_Blue(void);
void RGB_LED_Violet(void);
void RGB_LED_FLY(void);
void RGB_LED_White(void);
void GYRO_Offset_LED(void);
void ACC_Offset_LED(void);
void BAR_Offset_LED(void);
void BATT_Alarm_LED(void);

#endif
