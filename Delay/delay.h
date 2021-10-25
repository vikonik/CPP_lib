#ifndef _DELAY_H_
#define _DELAY_H_
#include "MDR1986VE1T.h"                // Device header
#include "MDR32F9Qx_timer.h"            // Keil::Drivers:TIMER




//#ifdef __cplusplus
//extern "C"
//{
//#endif

//#include <stdio.h>


//#ifdef __cplusplus
//}
//#endif

class DELAY{
	public:
		DELAY();
	void delayInit(void);
	void delay_ms(uint32_t _tickDelay);
	
	
//		uint32_t tickDelay;

	private:

};



#endif
