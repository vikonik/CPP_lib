#ifndef _TIMER_H
#define _TIMER_H
#include "MDR32F9Qx_timer.h"            // Keil::Drivers:TIMER
#include "MDR32F9Qx_config.h"           // Keil::Device:Startup
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK

class TIMER{
public:
TIMER();
TIMER(MDR_TIMER_TypeDef* _TIMERx, uint32_t period_us);
~TIMER();
void init(uint32_t period_us);
void timerStart();
void timerStop();
private:
MDR_TIMER_TypeDef* TIMERx;
};


#endif
