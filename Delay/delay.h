#ifndef _DELAY_H_
#define _DELAY_H_
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_timer.h"            // Keil::Drivers:TIMER
#include "MDR32F9Qx_it.h"



//#ifdef __cplusplus
//extern "C"
//{
//#endif

//#include <stdio.h>


//#ifdef __cplusplus
//}
//#endif
extern 	uint32_t tickDelay;

class DELAY{
	public:
	DELAY();
	void delayInit(void);
	void delay_ms(uint32_t _tickDelay);
	
	
//		uint32_t tickDelay;

	private:

};



#endif
