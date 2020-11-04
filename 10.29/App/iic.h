/******************** (C) COPYRIGHT 2017 shen hui xiang **************************
 * �ļ���  ��iic.h
 * ����    ��iic�����ļ���д����������ԭ�ӵ�iic�����ļ������ļ�������ѧϰiic���Լ���д������˼·�ο���ԭ�ӵ�iic����       
 * ʵ��ƽ̨��ԭ�ӿ�����mini��
 * ��汾  ��ST3.5.0
 * ����    ��2017
 * ����    �������
**********************************************************************************/
#ifndef __IIC__H_
#define __IIC__H_
#include "delay.h"
#include "sys.h"

#define IIC_SCL_Pin  GPIO_Pin_4
#define IIC_SDA_Pin  GPIO_Pin_5
#define GPIO_IIC     GPIOB
#define RCC_APB2Periph_GPIOIIC RCC_APB2Periph_GPIOB

#define IIC_SDA_OUT()  {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=0x00300000;}//����ģʽ������������ģʽ
#define IIC_SDA_IN()   {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=0x00800000;}//ͨ���������50MZ

#define SDA_PIN_OUT       PBout(5)
#define SCL_PIN_OUT       PBout(4)
#define SDA_PIN_IN        PBin(5)

void iic_init(void);
void iic_start(void);
void iic_stop(void);
u8 iic_wait_ack(void);
void iic_byte_write(u8 buf);
u8 iic_byte_read(unsigned char ask);
void iic_page_write(u8 device_address,u8 word_address,u8 byte_num,u8 *send_buff);
void iic_nbyte_read(u8 device_address,u8 word_address,u8 byte_num ,u8 *receive_buff);

void AT24_onebyte_write(u8 device_address,u8 word_address,u8 send_buff);
u8  AT24_onebyte_read(u8 device_address,u8 word_address);
void AT24_nbyte_read(u8 device_address,u8 word_address,u8 num,u8 *receive_buf);
#endif
