#include "includes.h"


OS_TCB	LED_TCB;		     //����������ƿ�
CPU_STK	LED_Stk[128];	   //���������ջ

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  OS_ERR err;	

  /* �弶��ʼ�� */	
	BSP_Init();

  /* ��ʼ��"uC/OS-III"�ں� */  
	OSInit(&err);		                                        
  
	/*��������*/
	OSTaskCreate((OS_TCB     *)&LED_TCB,                    // ������ƿ�ָ��          
               (CPU_CHAR   *)"LED",		                    // ��������
               (OS_TASK_PTR )Task_LED, 	                  // �������ָ��
               (void       *)0,			                      // ���ݸ�����Ĳ���parg
               (OS_PRIO     )2,			                      // �������ȼ�
               (CPU_STK    *)&LED_Stk[0],	                // �����ջ����ַ
               (CPU_STK_SIZE)12,			                    // ��ջʣ�ྯ����
               (CPU_STK_SIZE)128,			                    // ��ջ��С
               (OS_MSG_QTY  )0,			                      // �ɽ��յ������Ϣ������
               (OS_TICK     )0,			                      // ʱ��Ƭ��תʱ��
               (void       *)0,			                      // ������ƿ���չ��Ϣ
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      // ����ѡ��
               (OS_ERR     *)&err);		                    // ����ֵ
	  
  /* ����������ϵͳ������Ȩ����uC/OS-III */
  OSStart(&err);                                       
}

/*********************************************END OF FILE**********************/

