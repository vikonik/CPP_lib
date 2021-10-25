#ifndef _RELAY_H_
#define _RELAY_H_
#include "MDR1986VE1T.h"                // Device header
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT
#include "port.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>


#ifdef __cplusplus
}
#endif

class RELAY: public PortMapIO{
	public:
		RELAY(void);
		RELAY(MDR_PORT_TypeDef* PORTx,	uint16_t _pin);
	
	
		void on(void);
		void off(void);
		uint8_t getStatus(void);

	private:

};


#endif
