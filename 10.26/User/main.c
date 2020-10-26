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
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
  OS_ERR err;	

  /* 板级初始化 */	
	BSP_Init();

  /* 初始化"uC/OS-III"内核 */  
	OSInit(&err);		                                        
	OSSchedRoundRobinCfg(ENABLE, 1, &err);
	/*创建任务*/
	
	OSTaskCreate((OS_TCB     *)&LED1_TCB,                    // 任务控制块指针          
               (CPU_CHAR   *)"LED1",		                    // 任务名称
               (OS_TASK_PTR )Task_LED1, 	                  // 任务代码指针
               (void       *)0,			                      // 传递给任务的参数parg
               (OS_PRIO     )2,			                      // 任务优先级
               (CPU_STK    *)&LED1_Stk[0],	                // 任务堆栈基地址
               (CPU_STK_SIZE)12,			                    // 堆栈剩余警戒线
               (CPU_STK_SIZE)128,			                    // 堆栈大小
               (OS_MSG_QTY  )0,			                      // 可接收的最大消息队列数
               (OS_TICK     )2000,			                      // 时间片轮转时间
               (void       *)0,			                      // 任务控制块扩展信息
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      // 任务选项
               (OS_ERR     *)&err);		                    // 返回值
	
	OSTaskCreate((OS_TCB     *)&LED2_TCB,                    // 任务控制块指针          
               (CPU_CHAR   *)"LED2",		                    // 任务名称
               (OS_TASK_PTR )Task_LED2, 	                  // 任务代码指针
               (void       *)0,			                      // 传递给任务的参数parg
               (OS_PRIO     )2,			                      // 任务优先级
               (CPU_STK    *)&LED2_Stk[0],	                // 任务堆栈基地址
               (CPU_STK_SIZE)12,			                    // 堆栈剩余警戒线
               (CPU_STK_SIZE)128,			                    // 堆栈大小
               (OS_MSG_QTY  )0,			                      // 可接收的最大消息队列数
               (OS_TICK     )2000,			                      // 时间片轮转时间
               (void       *)0,			                      // 任务控制块扩展信息
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      // 任务选项
               (OS_ERR     *)&err);		                    // 返回值
	
	OSTaskCreate((OS_TCB     *)&LED3_TCB,                    // 任务控制块指针          
               (CPU_CHAR   *)"LED3",		                    // 任务名称
               (OS_TASK_PTR )Task_LED3, 	                  // 任务代码指针
               (void       *)0,			                      // 传递给任务的参数parg
               (OS_PRIO     )2,			                      // 任务优先级
               (CPU_STK    *)&LED3_Stk[0],	                // 任务堆栈基地址
               (CPU_STK_SIZE)12,			                    // 堆栈剩余警戒线
               (CPU_STK_SIZE)128,			                    // 堆栈大小
               (OS_MSG_QTY  )0,			                      // 可接收的最大消息队列数
               (OS_TICK     )2000,			                      // 时间片轮转时间
               (void       *)0,			                      // 任务控制块扩展信息
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      // 任务选项
               (OS_ERR     *)&err);		                    // 返回值
	
	OSTaskCreate((OS_TCB     *)&LED4_TCB,                    // 任务控制块指针          
               (CPU_CHAR   *)"LED4",		                    // 任务名称
               (OS_TASK_PTR )Task_LED4, 	                  // 任务代码指针
               (void       *)0,			                      // 传递给任务的参数parg
               (OS_PRIO     )2,			                      // 任务优先级
               (CPU_STK    *)&LED4_Stk[0],	                // 任务堆栈基地址
               (CPU_STK_SIZE)12,			                    // 堆栈剩余警戒线
               (CPU_STK_SIZE)128,			                    // 堆栈大小
               (OS_MSG_QTY  )0,			                      // 可接收的最大消息队列数
               (OS_TICK     )2000,			                      // 时间片轮转时间
               (void       *)0,			                      // 任务控制块扩展信息
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      // 任务选项
               (OS_ERR     *)&err);		                    // 返回值
	  
  /* 启动多任务系统，控制权交给uC/OS-III */
  OSStart(&err); 


}

/*********************************************END OF FILE**********************/

