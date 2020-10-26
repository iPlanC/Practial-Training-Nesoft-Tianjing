#include "includes.h"

OS_TCB	LED1_TCB;
OS_TCB	LED2_TCB;
OS_TCB	LED3_TCB;
OS_TCB	LED4_TCB;
CPU_STK	LED1_Stk[128];
CPU_STK	LED2_Stk[128];
CPU_STK	LED3_Stk[128];
CPU_STK	LED4_Stk[128];

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
	OSSchedRoundRobinCfg(ENABLE, 1, &err);
	/*��������*/
	
	OSTaskCreate((OS_TCB     *)&LED1_TCB,                    // ������ƿ�ָ��          
               (CPU_CHAR   *)"LED1",		                    // ��������
               (OS_TASK_PTR )Task_LED1, 	                  // �������ָ��
               (void       *)0,			                      // ���ݸ�����Ĳ���parg
               (OS_PRIO     )2,			                      // �������ȼ�
               (CPU_STK    *)&LED1_Stk[0],	                // �����ջ����ַ
               (CPU_STK_SIZE)12,			                    // ��ջʣ�ྯ����
               (CPU_STK_SIZE)128,			                    // ��ջ��С
               (OS_MSG_QTY  )0,			                      // �ɽ��յ������Ϣ������
               (OS_TICK     )2000,			                      // ʱ��Ƭ��תʱ��
               (void       *)0,			                      // ������ƿ���չ��Ϣ
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      // ����ѡ��
               (OS_ERR     *)&err);		                    // ����ֵ
	
	OSTaskCreate((OS_TCB     *)&LED2_TCB,                    // ������ƿ�ָ��          
               (CPU_CHAR   *)"LED2",		                    // ��������
               (OS_TASK_PTR )Task_LED2, 	                  // �������ָ��
               (void       *)0,			                      // ���ݸ�����Ĳ���parg
               (OS_PRIO     )2,			                      // �������ȼ�
               (CPU_STK    *)&LED2_Stk[0],	                // �����ջ����ַ
               (CPU_STK_SIZE)12,			                    // ��ջʣ�ྯ����
               (CPU_STK_SIZE)128,			                    // ��ջ��С
               (OS_MSG_QTY  )0,			                      // �ɽ��յ������Ϣ������
               (OS_TICK     )2000,			                      // ʱ��Ƭ��תʱ��
               (void       *)0,			                      // ������ƿ���չ��Ϣ
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      // ����ѡ��
               (OS_ERR     *)&err);		                    // ����ֵ
	
	OSTaskCreate((OS_TCB     *)&LED3_TCB,                    // ������ƿ�ָ��          
               (CPU_CHAR   *)"LED3",		                    // ��������
               (OS_TASK_PTR )Task_LED3, 	                  // �������ָ��
               (void       *)0,			                      // ���ݸ�����Ĳ���parg
               (OS_PRIO     )2,			                      // �������ȼ�
               (CPU_STK    *)&LED3_Stk[0],	                // �����ջ����ַ
               (CPU_STK_SIZE)12,			                    // ��ջʣ�ྯ����
               (CPU_STK_SIZE)128,			                    // ��ջ��С
               (OS_MSG_QTY  )0,			                      // �ɽ��յ������Ϣ������
               (OS_TICK     )2000,			                      // ʱ��Ƭ��תʱ��
               (void       *)0,			                      // ������ƿ���չ��Ϣ
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      // ����ѡ��
               (OS_ERR     *)&err);		                    // ����ֵ
	
	OSTaskCreate((OS_TCB     *)&LED4_TCB,                    // ������ƿ�ָ��          
               (CPU_CHAR   *)"LED4",		                    // ��������
               (OS_TASK_PTR )Task_LED4, 	                  // �������ָ��
               (void       *)0,			                      // ���ݸ�����Ĳ���parg
               (OS_PRIO     )2,			                      // �������ȼ�
               (CPU_STK    *)&LED4_Stk[0],	                // �����ջ����ַ
               (CPU_STK_SIZE)12,			                    // ��ջʣ�ྯ����
               (CPU_STK_SIZE)128,			                    // ��ջ��С
               (OS_MSG_QTY  )0,			                      // �ɽ��յ������Ϣ������
               (OS_TICK     )2000,			                      // ʱ��Ƭ��תʱ��
               (void       *)0,			                      // ������ƿ���չ��Ϣ
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      // ����ѡ��
               (OS_ERR     *)&err);		                    // ����ֵ
	  
  /* ����������ϵͳ������Ȩ����uC/OS-III */
  OSStart(&err); 


}

/*********************************************END OF FILE**********************/

