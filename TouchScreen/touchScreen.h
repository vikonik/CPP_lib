#ifndef _TOUCH_SCREEN_H_
#define _TOUCH_SCREEN_H_
#include "MDR1986VE1T.h"                // Device header
#include "port.h"


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
							PortMapIO *touchButton	
	);
	
	void init();
	void switchToRead(PortMapIO *hot, PortMapIO *could, PortMapIO *read, PortMapIO *free);
	uint16_t grtPosX(){return posX;}
	uint16_t grtPosY(){return posY;}
	
	
	private:
		
	uint16_t posX;
	uint16_t posY;
		
	uint8_t readButon();	
	void switchAsButton();	
	void switchToReadX();
	void switchToReadY();
		
		PortMapIO *Xp;	
		PortMapIO *Xm;
		PortMapIO *Yp;		
		PortMapIO *Ym;	
		PortMapIO *touchButton;	
	
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
