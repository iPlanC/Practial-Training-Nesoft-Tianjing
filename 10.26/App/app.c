#include "app.h"

/* 
 * ��������Task_LED
 * ����  : LED��ˮ��	
 * ����  ����
 * ���  : ��
 */
void Task_LED(void *p_arg)
{
	OS_ERR err;
  (void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����

  while (1)
  {
      GPIO_WriteBit(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4, Bit_SET);
      OSTimeDlyHMSM(0, 0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
			GPIO_WriteBit(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4, Bit_RESET);
			OSTimeDlyHMSM(0, 0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
  }
}
