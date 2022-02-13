#ifndef   _IIC_H
#define   _IIC_H
#include "stdint.h"
#include "math.h"

/********************IIC 代码移植区********************/

#define RCC_IIC_SCL   RCC_APB2Periph_GPIOB  //端口时钟
#define IIC_SCl_PORT  GPIOB                 //端口
#define IIC_SCL       GPIO_Pin_6            //引脚

#define RCC_IIC_SDA   RCC_APB2Periph_GPIOB  //端口时钟
#define IIC_SDA_PORT  GPIOB                 //端口
#define IIC_SDA       GPIO_Pin_7            //引脚

/******************************************************/

//求偏移量 针对F4的配置
/*****************************************************
#define IIC_SCL_OFFSET (uint8_t)(log(IIC_SCL)/log(2))
#define IIC_SDA_OFFSET (uint8_t)(log(IIC_SDA)/log(2))

#define SDA_IN() (IIC_SCl_PORT->MODER &=~(3<<(IIC_SDA_OFFSET*2)); IIC_SCl_PORT->MODER |=0<<(IIC_SDA_OFFSET*2) )
#define SDA_OUT() (IIC_SCl_PORT->MODER &=~(3<<(IIC_SDA_OFFSET*2)); IIC_SCl_PORT->MODER |=1<<(IIC_SDA_OFFSET*2) )
******************************************************/

#define SCL_H         GPIOB->BSRR = GPIO_Pin_6
#define SCL_L         GPIOB->BRR  = GPIO_Pin_6
#define SDA_H         GPIOB->BSRR = GPIO_Pin_7 
#define SDA_L         GPIOB->BRR  = GPIO_Pin_7
#define SDA_read      ((GPIOB->IDR & GPIO_Pin_7)!=0)?1:0

void IIC_GPIO_Init(void);        //初始化IIC的IO口				 
void IIC_Start(void);			 //发送IIC开始信号
void IIC_Stop(void);	  	  	 //发送IIC停止信号
void IIC_Ack(void);				 //IIC发送ACK信号
void IIC_NAck(void);			 //IIC不发送ACK信号
uint8_t IIC_WaitAck(void); 		 //IIC等待ACK信号

void IIC_SendByte(uint8_t data);  //IIC发送一个字节
uint8_t IIC_ReadByte(uint8_t ack);//IIC读取一个字节

uint8_t IIC_ReadByteFromSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t *buf);
uint8_t IIC_ReadMultByteFromSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data);
uint8_t IIC_WriteByteToSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t buf);
uint8_t IIC_WriteMultByteToSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data);


#endif

