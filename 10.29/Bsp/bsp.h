#ifndef  __BSP_H__
#define  __BSP_H__

#include "stm32f10x.h"
#include "os_cfg_app.h"
#include "LedAndKey.h"
#include "bsp_oled.h"

void BSP_Init(void);
void SysTick_init(void);


#endif /* __BSP_H__ */



