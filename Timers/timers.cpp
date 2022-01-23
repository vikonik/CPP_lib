#include "timers.h"

/**/
TIMER::TIMER(MDR_TIMER_TypeDef* TIMERx):TIMERx(TIMERx){

}
	
/**/
void TIMER::init(MDR_TIMER_TypeDef* TIMERx){
	TIMER_CntInitTypeDef Timer;
	TIMER_DeInit(TIMERx);	
	TIMER_CntStructInit(&Timer);
	//Включаем тактирование таймера
	if(TIMERx == MDR_TIMER1){
    MDR_RST_CLK->PER_CLOCK |=  RST_CLK_PCLK_TIMER1;//разрешение тактирования Таймера 1
    MDR_RST_CLK->TIM_CLOCK |= RST_CLK_TIM_CLOCK_TIM1_CLK_EN;		

	}
	
	if(TIMERx == MDR_TIMER2){
    MDR_RST_CLK->PER_CLOCK |=  RST_CLK_PCLK_TIMER2;//разрешение тактирования Таймера 2
    MDR_RST_CLK->TIM_CLOCK |= RST_CLK_TIM_CLOCK_TIM2_CLK_EN;		

	}	
	
	if(TIMERx == MDR_TIMER3){
    MDR_RST_CLK->PER_CLOCK |=  RST_CLK_PCLK_TIMER3;//разрешение тактирования Таймера 3
    MDR_RST_CLK->TIM_CLOCK |= RST_CLK_TIM_CLOCK_TIM3_CLK_EN;		

	}
	
	if(TIMERx == MDR_TIMER4){
    MDR_RST_CLK->PER_CLOCK |=  RST_CLK_PCLK_TIMER4;//разрешение тактирования Таймера 4
    MDR_RST_CLK->TIM_CLOCK |= RST_CLK_UART_CLOCK_TIM4_CLK_EN;		
		
	}
	TIMER_BRGInit(TIMERx,TIMER_HCLKdiv1);
	
	Timer.TIMER_ARR_UpdateMode = TIMER_ARR_Update_Immediately;		
	Timer.TIMER_BRK_Polarity = TIMER_BRKPolarity_NonInverted;		
	Timer.TIMER_CounterDirection = 	TIMER_CntDir_Up;
	Timer.TIMER_CounterMode = TIMER_CntMode_ClkFixedDir;
	Timer.TIMER_EventSource = TIMER_EvSrc_None;
	Timer.TIMER_FilterSampling = TIMER_FDTS_TIMER_CLK_div_1;
	Timer.TIMER_IniCounter = 0;
	Timer.TIMER_Period = 1;//ARR(Модуль счета)
	Timer.TIMER_Prescaler = 1;//PSG(Делитель частоты)
	TIMER_CntInit (TIMERx, &Timer);
	
}

/*
Устанавливаем период в микро сек
*/
void TIMER::setPerioduSec(uint16_t uSec){
	double period = 1/SystemCoreClock;
	double period_1uSec = 0.000001/period;
	this->TIMERx->ARR = uSec;
	this->TIMERx->PSG = period_1uSec-1;
}
	
/*
Устанавливаем период в мили сек
*/
void TIMER::setPeriodmSec(uint16_t mSec){
	double period = 1/SystemCoreClock;
	double period_1mSec = 0.001/period;
	uint16_t div = 1;
	while(period_1mSec > 0xFFFF){
		period_1mSec /= 2;
		div++;
	}
	
	this->TIMERx->PSG = period_1mSec-1;
	this->TIMERx->ARR = (mSec*div);
}

/*
Устанавливаем период в сек
*/
void TIMER::setPeriodSec(uint16_t Sec){

}

/*
Устанавливаем период в Гц
*/
void TIMER::setPeriodHz(uint16_t Hz){

}

		
		
