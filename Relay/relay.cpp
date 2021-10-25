#include "relay.h"
#include "port.h"

#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK


RELAY::RELAY(MDR_PORT_TypeDef* PORTx,	uint16_t _pin):PortMapIO(PORTx, _pin){

	}

	void RELAY::on(void){
		setHigh();
		
//		PORT_SetBits(this->relayPort,this->pin);	
//		this->status = 1;
	}
//	
//	
	void RELAY::off(void){
		setLow();
//		PORT_ResetBits(this->relayPort,this->pin);	
//		this->status = 0;
	}
//	
	uint8_t RELAY::getStatus(void){
	return getStatus();
//		return PORT_ReadInputDataBit(this->relayPort,this->pin);	
//		return status;
	}
		


