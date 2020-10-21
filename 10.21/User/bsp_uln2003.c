/*
	���߱�
	STM32								ULN2003����
	PA4    	<-------> 	IN1
	PA5			<-------> 	IN2
	PA6			<-------> 	IN3
	PA7			<-------> 	IN4
	
	5V 28BYJ-48����������ڲ����м���װ�� ���ٱȣ�1/64   ����ǣ�5.625��/64��64������ת��5.625�㣩

����ת����
	������Ŀ���˳��(A-AB-B-BC-C-CD-D-DA)
				1		2		3		4		5		6		7		8
	A			-		-		+		+		+		+		+		-
	B			+		-		-		-		+		+		+		+
	C			+		+		+		-		-		-		+		+
	D			+		+		+		+		+		-		-		-
����ת����(DA-D-CD-C-BC-B-AB-A)
*/

#include "bsp_uln2003.h"

void ULN2003_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOA, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7, Bit_RESET);
}

//�ٶȿ���:
void stepper(unsigned int dir, unsigned int speed)
{
	if(dir == Pos)
	{
		//step1:
		IN1_HIGH;
		IN2_LOW;
		IN3_LOW;
		IN4_LOW;
		Delay_us(speed);
		
		//step2:	
		IN1_HIGH;
		IN2_HIGH;
		IN3_LOW;
		IN4_LOW;
		Delay_us(speed);

		//step3:		
		IN1_LOW;
		IN2_HIGH;
		IN3_LOW;
		IN4_LOW;
		Delay_us(speed);

		//step4:
		IN1_LOW;
		IN2_HIGH;
		IN3_HIGH;
		IN4_LOW;
		Delay_us(speed);

		//step5:
		IN1_LOW;
		IN2_LOW;
		IN3_HIGH;
		IN4_LOW;
		Delay_us(speed);

		//step6:
		IN1_LOW;
		IN2_LOW;
		IN3_HIGH;
		IN4_HIGH;
		Delay_us(speed);

		//step7:
		IN1_LOW;
		IN2_LOW;
		IN3_LOW;
		IN4_HIGH;
		Delay_us(speed);

		//step8:
		IN1_HIGH;
		IN2_LOW;
		IN3_LOW;
		IN4_HIGH;
		Delay_us(speed);
	}
	else
	{
		//step1:
		IN1_HIGH;
		IN2_LOW;
		IN3_LOW;
		IN4_HIGH;
		Delay_us(speed);

		//step2:		
		IN1_LOW;
		IN2_LOW;
		IN3_LOW;
		IN4_HIGH;
		Delay_us(speed);

		//step3:		
		IN1_LOW;
		IN2_LOW;
		IN3_HIGH;
		IN4_HIGH;
		Delay_us(speed);

		//step4:
		IN1_LOW;
		IN2_LOW;
		IN3_HIGH;
		IN4_LOW;
		Delay_us(speed);

		//step5:
		IN1_LOW;
		IN2_HIGH;
		IN3_HIGH;
		IN4_LOW;
		Delay_us(speed);

		//step6:
		IN1_LOW;
		IN2_HIGH;
		IN3_LOW;
		IN4_LOW;
		Delay_us(speed);

		//step7:
		IN1_HIGH;
		IN2_HIGH;
		IN3_LOW;
		IN4_LOW;
		Delay_us(speed);

		//step8:
		IN1_HIGH;
		IN2_LOW;
		IN3_LOW;
		IN4_LOW;
		Delay_us(speed);
	}
}

//�Ƕȿ��ƣ�
void angle_control(unsigned int dir, double angle, unsigned int speed)
{
	int i;
	
	for(i = 0; i < angle / STEPPER_ANGLE; i++)
		stepper(dir, speed);
}
