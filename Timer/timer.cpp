#include "timer.h"
TIMER::TIMER(){}
	
	TIMER::TIMER(MDR_TIMER_TypeDef* _TIMERx, uint32_t period_us)
	:TIMERx(_TIMERx)
	{
	this->init( period_us);
	}
  /*
	x1 =	SystemCoreClock/1000000;//Столько импульсов на одну микросекунду
	x2 = x1 * period_us;//столько импульсов на на период обновления
	
	*/
	
	
/*
	Период счета таймера в микросекундах
	в одной секунде 1М микросекунд
	*/	
void TIMER::init(uint32_t period_us){
	TIMER_CntInitTypeDef TIMxInit;
	
	TIMER_DeInit(TIMERx); //Задание начельных значений регистров для таймера.	
	if(TIMERx == MDR_TIMER1)//Включение тактирования таймера
		RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER1, ENABLE);
	if(TIMERx == MDR_TIMER2)
		RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER2, ENABLE);
	if(TIMERx == MDR_TIMER3)
		RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER3, ENABLE);	
	// Включение делителя тектовой частоты 
	TIMER_BRGInit(TIMERx, TIMER_HCLKdiv1); 
	TIMER_CntStructInit(&TIMxInit);

  uint16_t prescaler = 1;
	uint32_t x1 =	SystemCoreClock/1000000;//Столько импульсов на одну микросекунду
	uint32_t x2 = x1 * period_us;//столько импульсов на на период обновления
while(x2 > 0xFFFF){
prescaler *= 2;
x2 /= 2;
}

	// Задаем параметры счета
	TIMxInit.TIMER_Prescaler   	= prescaler-1; 	
	TIMxInit.TIMER_Period   		= x2-1; 
	TIMER_CntInit(TIMERx, &TIMxInit);

	// Включение прерывания от таймера
	if(TIMERx == MDR_TIMER1){//Включение тактирования таймера
			NVIC_EnableIRQ(Timer1_IRQn);
TIMER_ITConfig(TIMERx,TIMER_STATUS_CNT_ARR,ENABLE);
}
	if(TIMERx == MDR_TIMER2)
			NVIC_EnableIRQ(Timer2_IRQn);
	if(TIMERx == MDR_TIMER3)
			NVIC_EnableIRQ(Timer3_IRQn);  
	// Установка приоритета прерывания
	
	// NVIC_SetPriority(TIMER1_IRQn, 0);
	// Разрешение работы таймера
	TIMER_Cmd(TIMERx, ENABLE); 
	
}



	//Пример настройки таймера
//void initTimer2(void){
//	PORT_InitTypeDef PortInit;
//	PortInit.PORT_Pin    = MCU_INT; //X33.2-6 контакт
//PortInit.PORT_OE    = PORT_OE_IN; 
//PortInit.PORT_PULL_UP  = PORT_PULL_UP_OFF;
//PortInit.PORT_PULL_DOWN  = PORT_PULL_DOWN_ON ; 
//PortInit.PORT_PD_SHM  = PORT_PD_SHM_ON ; 
//PortInit.PORT_PD    = PORT_PD_DRIVER; 
//PortInit.PORT_FUNC   = PORT_FUNC_MAIN ; 
//PortInit.PORT_SPEED  = PORT_SPEED_MAXFAST; 
//PortInit.PORT_MODE   = PORT_MODE_DIGITAL; 
//PORT_Init(MDR_PORTE, &PortInit);
//	
//TIMER_CntInitTypeDef TIM2Init;
//TIMER_ChnInitTypeDef CH2Init; 
//	
////Задание начельных значений регистров для таймера.
//TIMER_DeInit(MDR_TIMER2);       
////Включение тактирования таймера
//RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER2, ENABLE);
//// Включение делителя тектовой частоты 
//TIMER_BRGInit(MDR_TIMER2, TIMER_HCLKdiv1); 
//TIMER_CntStructInit(&TIM2Init);
//// Задаем параметры счета
//TIM2Init.TIMER_Prescaler   = 1; 
//TIM2Init.TIMER_Period   = 5000; 
//// Инициализация таймера
//TIMER_CntInit (MDR_TIMER2, &TIM2Init);       
//// Настройка первого канала таймера на регистрацию событий
//// Загрузка параметров по умолчанию
//TIMER_ChnStructInit(&CH2Init);       
//// Выбираем первый канал
//CH2Init.TIMER_CH_Number = TIMER_CHANNEL3; 
//// Выбираем режим захвата
//CH2Init.TIMER_CH_Mode = TIMER_CH_MODE_CAPTURE; 
//// Выбираем положительный фронт импульса для события захвата в регистр CCR
//CH2Init.TIMER_CH_EventSource = TIMER_CH_EvSrc_PE; 
//// Выбираем отрицательный фронт импульса для события захвата в регистр CCR1
//CH2Init.TIMER_CH_CCR1_EventSource = TIMER_CH_CCR1EvSrc_NE; 
//// Немедленное обновление регистров CCR и CCR1
//CH2Init.TIMER_CH_CCR_UpdateMode = TIMER_CH_CCR_Update_Immediately;    
//// Инициализация таймера
//TIMER_ChnInit(MDR_TIMER2, &CH2Init);   
//// Очистка флагов событий   
//TIMER_ClearFlag(MDR_TIMER2, 0);        
//// Разрешение прерываний по захвату фронта и среза 
//TIMER_ITConfig(MDR_TIMER2, TIMER_STATUS_CCR_CAP_CH2 /*|  TIMER_STATUS_CCR_CAP1_CH1*/, ENABLE); 
//// Включение прерывания от таймера
//NVIC_EnableIRQ(TIMER2_IRQn);     
//// Установка приоритета прерывания
//NVIC_SetPriority(TIMER2_IRQn, 0);
//// Разрешение работы таймера
//TIMER_Cmd(MDR_TIMER2, ENABLE); 

//}
