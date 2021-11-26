#ifndef _TOUCH_SCREEN_H_
#define _TOUCH_SCREEN_H_
#include "MDR1986VE1T.h"                // Device header
#include "port.h"
#include "delay.h"
#include "ADC.h"
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>


#ifdef __cplusplus
}
#endif


class TOUCHSCREEN : public PortMapIO{
	public:

	TOUCHSCREEN( 
							PortMapIO *Xp,	
							PortMapIO *Xm,
							PortMapIO *Yp,		
							PortMapIO *Ym,
							DELAY *pause,
							ADC *adc		
	);
	
	void init();
	void switchToRead(PortMapIO *hot, PortMapIO *could, PortMapIO *read, PortMapIO *free);
	uint16_t grtPosX(){return posX;}
	uint16_t grtPosY(){return posY;}
	
	
	private:
	uint16_t chanelADC_X;
	uint16_t chanelADC_Y;
	uint16_t posX;
	uint16_t posY;
		
	uint8_t readButon();	
	void switchAsButton();	
	void switchAsDisplay();
	void switchToReadX();
	void switchToReadY();
	uint16_t readAxis(uint16_t chanelADC);
	uint32_t getPos();
	
		
		PortMapIO *Xp;	
		PortMapIO *Xm;
		PortMapIO *Yp;		
		PortMapIO *Ym;	
		MDR_PORT_TypeDef *touchButton;	
	DELAY *pause;
	ADC *adc;
	
//		MDR_PORT_TypeDef *touchPortYp;		
//		MDR_PORT_TypeDef *touchPortYm;
//		MDR_PORT_TypeDef *touchPortXp;		
//		MDR_PORT_TypeDef *touchPortXm;
//		MDR_PORT_TypeDef *touchPortButton;
//		uint16_t pinXp;
//		uint16_t pinXm;
//		uint16_t pinYp;
//		uint16_t pinYm;	
//		uint16_t pinTouchButton;	
};


#endif
