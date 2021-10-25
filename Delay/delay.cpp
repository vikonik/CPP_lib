#include "delay.h"


	uint32_t tickDelay;
DELAY::DELAY(){
	tickDelay = 0;
	delayInit();
}

void DELAY::delayInit(void){
	//SystemCoreClock = 72000000;
  SysTick_Config(SystemCoreClock/1000);

}

void DELAY::delay_ms(uint32_t _tickDelay){
	tickDelay = _tickDelay; //* 1000;
while(tickDelay);
}
