#ifndef _TFT_MODULE_H_
#define _TFT_MODULE_H_
#include "MDR1986VE1T.h"                // Device header
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT
#include "touchScreen.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>


#ifdef __cplusplus
}
#endif

class TFT_MODULE {
	public:
		
		TFT_MODULE( MDR_PORT_TypeDef *_touchPortXp,		
								MDR_PORT_TypeDef *_touchPortXm,
								MDR_PORT_TypeDef *_touchPortYp,		
								MDR_PORT_TypeDef *_touchPortYm,
								uint16_t _pinXp,
								uint16_t _pinXm,
								uint16_t _pinYp,
								uint16_t _pinYm);
		
		void initTouch();
		void switchToTouch();
		void switchToTFT();
		void writeData();
		void writeCmd();
	
	
	
	private:

	
	
};




#endif
