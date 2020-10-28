#include "includes.h"
#include <stdio.h>

OS_FLAG_GRP flags;
OS_TCB  key1_TCB;
OS_TCB  key2_TCB;
CPU_STK	key1_Stk[128];
CPU_STK	key2_Stk[128];

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
	
	OSFlagCreate(&flags, "FLAGS", 0, &err);
	
	/*��������*/
	OSTaskCreate((OS_TCB     *)&key1_TCB,                    // ������ƿ�ָ��          
               (CPU_CHAR   *)"Task1",		                    // ��������
               (OS_TASK_PTR )Task1, 	                  // �������ָ��
               (void       *)0,			                      // ���ݸ�����Ĳ���parg
               (OS_PRIO     )2,			                      // �������ȼ�
               (CPU_STK    *)&key1_Stk[0],	                // �����ջ����ַ
               (CPU_STK_SIZE)12,			                    // ��ջʣ�ྯ����
               (CPU_STK_SIZE)128,			                    // ��ջ��С
               (OS_MSG_QTY  )0,			                      // �ɽ��յ������Ϣ������
               (OS_TICK     )0,			                      // ʱ��Ƭ��תʱ��
               (void       *)0,			                      // ������ƿ���չ��Ϣ
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      // ����ѡ��
               (OS_ERR     *)&err);		                    // ����ֵ
	
	OSTaskCreate((OS_TCB     *)&key2_TCB,                    // ������ƿ�ָ��          
               (CPU_CHAR   *)"Task2",		                    // ��������
               (OS_TASK_PTR )Task2, 	                  // �������ָ��
               (void       *)0,			                      // ���ݸ�����Ĳ���parg
               (OS_PRIO     )3,			                      // �������ȼ�
               (CPU_STK    *)&key2_Stk[0],	                // �����ջ����ַ
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

