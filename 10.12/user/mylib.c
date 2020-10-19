#include "mylib.h"

volatile char receiveBuffer[50];
volatile uint16_t receiveLength = 0;
unsigned int setflag = 0;
unsigned int timer;
uint16_t Deepdata;
uint16_t Tempdata;

void delayus(unsigned int us) {
	timer = us;
	SysTick->CTRL |= (1 << 0);
	while (timer);
	SysTick->CTRL &= ~(1 << 0);
}

void GPIO_init(GPIO_TypeDef* GPIOx, u16 GPIO_Pin_x, GPIOSpeed_TypeDef GPIO_Speed, GPIOMode_TypeDef GPIO_Mode) {
	GPIO_InitTypeDef GPIOA_init;
	
	GPIOA_init.GPIO_Pin = GPIO_Pin_x;
	GPIOA_init.GPIO_Speed = GPIO_Speed;
	GPIOA_init.GPIO_Mode = GPIO_Mode;
	
	GPIO_Init(GPIOx, &GPIOA_init);
}

void RCC_init(void) {
	#ifdef USE_WWDG
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	#endif
	
	#ifdef USE_USART2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	#endif
	
	#ifdef USE_RTC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	#endif
	
	#ifdef USE_AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	#endif
	
	#ifdef USE_GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	#endif
	
	#ifdef USE_GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	#endif
	
	#ifdef USE_USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	#endif
	
	#ifdef USE_ADC1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	#endif
	
	#ifdef USE_DMA
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	#endif
}

void RTC_init(void) {
	PWR_BackupAccessCmd(ENABLE);
	BKP_DeInit();
	RCC_LSEConfig(RCC_LSE_ON);
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == SET);
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForLastTask();
	RTC_WaitForSynchro();
	
	//RTC_EnterConfigMode();
	RTC_SetPrescaler(32768);
	RTC_WaitForLastTask();
	RTC_WaitForSynchro();
	//RTC_SetCounter(1602691200 + 28800);
	//RTC_WaitForLastTask();
	//RTC_WaitForSynchro();
	//RTC_ExitConfigMode();
	
	PWR_BackupAccessCmd(DISABLE);
}

void USART_init(void) {
	USART_InitTypeDef USART1_init;
//	NVIC_InitTypeDef NVIC_init;
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//	NVIC_init.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_init.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_init.NVIC_IRQChannelSubPriority = 2;
//	NVIC_init.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_init);
	
	GPIO_init(GPIOA, GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
	GPIO_init(GPIOA, GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);
//	GPIO_init(GPIOA, GPIO_Pin_2, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
//	GPIO_init(GPIOA, GPIO_Pin_3, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);
	
	USART1_init.USART_BaudRate = 115200;
	USART1_init.USART_WordLength = USART_WordLength_8b;
	USART1_init.USART_StopBits = USART_StopBits_1;
	USART1_init.USART_Parity = USART_Parity_No;
	USART1_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART1_init.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART1_init);
	
//	USART_init.USART_BaudRate = 2400;
//	USART_init.USART_Mode = USART_Mode_Rx;
//	USART_Init(USART2, &USART_init);
//	
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
//	USART_Cmd(USART2, ENABLE);
}

void SysTick_init(void) {
	while (SysTick_Config(72));
	SysTick->CTRL &= ~(1 << 0);
}

void USART_GetString(USART_TypeDef* USARTx, char* temp) {
	int i = 0;
	while(i < 14) {
		while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
			temp[i++] = USART_ReceiveData(USART1);	
	}
}

int fputc(int c, FILE *fp) {
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, c);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	return 0;
}

int isLeap(int year) {
	return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

int monthDays(int month,int leap) {
	int days[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                       {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
	return days[leap][month];
}

void Set_Time(void) {
	if (setflag == 0) {
		char* temp = "0000000000000000";
		unsigned int time = 0;
		printf("input date:\n");
		USART_GetString(USART1, temp);
		
		printf("%s\n", temp);
		
		//time = time + 28800;
		
		PWR_BackupAccessCmd(ENABLE);
		RTC_SetCounter(time);
		RTC_WaitForLastTask();
		RTC_WaitForSynchro();
		PWR_BackupAccessCmd(DISABLE);
		
		setflag = 1;
	}
}

void Get_Time(void) {
	if (setflag == 1) {
		int time = 0;
		dateTime date;
		date.month = 1;
		date.year = 1970;
		time = RTC_GetCounter();
		printf("%d second(s).\t", time);
		
		date.day = time / (60 * 60 * 24);
		while (date.day >= leapDay(date.year)) {
			date.day = date.day - leapDay(date.year);
			date.year++;
		}
		while (date.day >= monthDays(date.month, isLeap(date.year))) {
			date.day = date.day - monthDays(date.month, isLeap(date.year));
			date.month++;
		}
		
		printf("%04d-", date.year);
		printf("%02d-", date.month);
		printf("%02d ", date.day + 1);
		printf("%02d:", time / (60 * 60) % 24);
		printf("%02d:", time / 60 % 60);
		printf("%02d.\n", time % 60);
	}
}
