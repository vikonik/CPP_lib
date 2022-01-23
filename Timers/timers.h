#ifndef _TFT_MODULE_H_
#define _TFT_MODULE_H_
#include "MDR1986VE1T.h"                // Device header
#include "MDR32F9Qx_timer.h"            // Keil::Drivers:TIMER
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK



#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>


#ifdef __cplusplus
}
#endif

class TIMER{
	public:
		
	TIMER(MDR_TIMER_TypeDef* TIMERx);
	
	void init(MDR_TIMER_TypeDef* TIMERx);
	void setPerioduSec(uint16_t uSec);
	void setPeriodmSec(uint16_t mSec);
	void setPeriodSec(uint16_t Sec);
	void setPeriodHz(uint16_t Hz);
	
	private:
		MDR_TIMER_TypeDef* TIMERx;
};



#endif
