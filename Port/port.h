#ifndef _PORT_H
#define _PORT_H
//#ifdef USE_MDR1986VE9x
//#include "MDR1986VE1T.h"                // Device header
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT
#include "MDR32F9Qx_config.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>


#ifdef __cplusplus
}
#endif

class PortMapIO{
	public:
		
    PortMapIO();
		PortMapIO (MDR_PORT_TypeDef *port, uint16_t pin);
	
    PortMapIO (MDR_PORT_TypeDef *port, uint16_t PORT_Pin, PORT_OE_TypeDef PORT_OE, PORT_PULL_UP_TypeDef PORT_PULL_UP, \
    PORT_PULL_DOWN_TypeDef PORT_PULL_DOWN, PORT_PD_SHM_TypeDef PORT_PD_SHM, PORT_PD_TypeDef PORT_PD, PORT_GFEN_TypeDef PORT_GFEN, \
    PORT_FUNC_TypeDef PORT_FUNC, PORT_SPEED_TypeDef PORT_SPEED, PORT_MODE_TypeDef PORT_MODE);
	
		void init();
		void togglePin();
		void setLow();
		void setHigh();
		uint8_t getStatus();	
		void fullInitPin( 
							PORT_OE_TypeDef PORT_OE, 
							PORT_PULL_UP_TypeDef PORT_PULL_UP, 
							PORT_PULL_DOWN_TypeDef PORT_PULL_DOWN, 
							PORT_PD_SHM_TypeDef PORT_PD_SHM, 
							PORT_PD_TypeDef PORT_PD, 
							PORT_GFEN_TypeDef PORT_GFEN, 
							PORT_FUNC_TypeDef PORT_FUNC, 
							PORT_SPEED_TypeDef PORT_SPEED, 
							PORT_MODE_TypeDef PORT_MODE);

		//Установка состояния и функции выводов
	void setPinAsInput();
	void setPinAsOff();
	void setPinAsOutput();
	void setPinAsAnalog();
//	void setPinAsAlternative(uint8_t digital, uint8_t OE);
	uint16_t PortMapIoPORT_Read();
	void PortMapIoPORT_Write(uint16_t *data);
	uint16_t getPin(){return m_pin;}

	
	private:
void enablePort();
		MDR_PORT_TypeDef * m_port;
		uint16_t m_pin;
		uint8_t m_status;
};




#endif
