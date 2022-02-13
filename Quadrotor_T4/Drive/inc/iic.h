#ifndef   _IIC_H
#define   _IIC_H
#include "stdint.h"
#include "math.h"

/********************IIC ������ֲ��********************/

#define RCC_IIC_SCL   RCC_APB2Periph_GPIOB  //�˿�ʱ��
#define IIC_SCl_PORT  GPIOB                 //�˿�
#define IIC_SCL       GPIO_Pin_6            //����

#define RCC_IIC_SDA   RCC_APB2Periph_GPIOB  //�˿�ʱ��
#define IIC_SDA_PORT  GPIOB                 //�˿�
#define IIC_SDA       GPIO_Pin_7            //����

/******************************************************/

//��ƫ���� ���F4������
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

void IIC_GPIO_Init(void);        //��ʼ��IIC��IO��				 
void IIC_Start(void);			 //����IIC��ʼ�ź�
void IIC_Stop(void);	  	  	 //����IICֹͣ�ź�
void IIC_Ack(void);				 //IIC����ACK�ź�
void IIC_NAck(void);			 //IIC������ACK�ź�
uint8_t IIC_WaitAck(void); 		 //IIC�ȴ�ACK�ź�

void IIC_SendByte(uint8_t data);  //IIC����һ���ֽ�
uint8_t IIC_ReadByte(uint8_t ack);//IIC��ȡһ���ֽ�

uint8_t IIC_ReadByteFromSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t *buf);
uint8_t IIC_ReadMultByteFromSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data);
uint8_t IIC_WriteByteToSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t buf);
uint8_t IIC_WriteMultByteToSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data);


#endif
