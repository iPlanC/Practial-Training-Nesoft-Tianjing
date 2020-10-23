#include "bsp_bkp.h"

void BKP_Configuration(void) {
	BKP_DeInit();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
}
