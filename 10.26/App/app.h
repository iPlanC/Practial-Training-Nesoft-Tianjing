#ifndef	_APP_H_
#define	_APP_H_

#include "bsp.h" 
#include "os.h"  		
#include "os_type.h"

/**************** �û��������� *******************/
void TimCallback(OS_TMR *p_tmr, void *p_arg);
void Task1(void *p_arg);
void Task2(void *p_arg);
void Task_init(void *p_arg);

#endif	//_APP_H_
