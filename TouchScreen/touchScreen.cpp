#include "touchScreen.h"

TOUCHSCREEN::TOUCHSCREEN( 
							PortMapIO *Xp,	
							PortMapIO *Xm,
							PortMapIO *Yp,		
							PortMapIO *Ym,
							PortMapIO *touchPortButton
):Xp(Xp), Xm(Xm), Yp(Yp), Ym(Ym), touchButton(touchButton){


}





//TOUCHSCREEN::TOUCHSCREEN( MDR_PORT_TypeDef *_touchPortXp,		
//						MDR_PORT_TypeDef *_touchPortXm,
//						MDR_PORT_TypeDef *_touchPortYp,		
//						MDR_PORT_TypeDef *_touchPortYm,
//						MDR_PORT_TypeDef *touchPortButton,
//						uint16_t _pinXp, uint16_t _pinXm, uint16_t _pinYp, uint16_t _pinYm, uint16_t _pinTouchButton)
//						:touchPortXp(_touchPortXp), touchPortXm(_touchPortXm),touchPortYp(_touchPortYp), touchPortYm(_touchPortYm),
//  					pinXp(_pinXp), pinXm(_pinXm), pinYp(_pinYp), pinYm(_pinYm), pinTouchButton(_pinTouchButton)
//{

//							 
//}

/**/
void TOUCHSCREEN::init(){
//	Xp = PortMapIO(touchPortXp, pinXp);
//	Xm = PortMapIO(touchPortXm, pinXm);	
//	Yp = PortMapIO(touchPortYp, pinYp);
//	Ym = PortMapIO(touchPortYm, pinYm);
//	  touchButton = PortMapIO(touchPortButton, pinTouchButton);
	
	Xp->setPinAsOff();
	Xm->setPinAsOff();
	Yp->setPinAsOff();
	Ym->setPinAsOff();
	touchButton->setPinAsOff();
}
/*
Чтобы определить касание прикидываемся кнопкой 
*/
void TOUCHSCREEN::switchAsButton(){
	Xp->setPinAsOutput();
	Xm->setPinAsOutput();
	Xp->setHigh();	
	touchButton->setPinAsInput();
}

/*
Опрашиваем нашу кнопку
*/
uint8_t TOUCHSCREEN::readButon(){
	return Yp->getStatus();
}

/*
Переключаемся на чтение координаты X
*/
void TOUCHSCREEN::switchToReadX(){
	Xp->setPinAsOutput();
	Xm->setPinAsOutput();
	Yp->setPinAsAnalog();
	Ym->setPinAsOff();
	Xp->setHigh();
	Xm->setLow();
}

/*
Переключаемся на чтение координаты Y
*/
void TOUCHSCREEN::switchToReadY(){
	Yp->setPinAsOutput();
	Ym->setPinAsOutput();
	Xp->setPinAsAnalog();
	Xm->setPinAsOff();
	Yp->setHigh();
	Ym->setLow();
}



/**
  * @brief  Переключаемся на чтение координаты
	* @param  hot - пин для подключения к питанию
	*					could - пин для подключения к земле
	*					read - пин для чтения значения
	*					free - свободно болтающийся пин
  * @retval 
*/
void TOUCHSCREEN::switchToRead(PortMapIO *hot, PortMapIO *could, PortMapIO *read, PortMapIO *free){
	
	hot->setPinAsOutput();
	could->setPinAsOutput();
	read->setPinAsAnalog();
	free->setPinAsOff();
	hot->setHigh();
	could->setLow();
}

/*
читаем данные с АЦП
*/
//void TOUCHSCREEN::getPos(){
//	uint16_t dataX = 0;
//	uint16_t dataY = 0;
//	
//	switchToReadX();
////	dataX = 
//	
//	
//	switchToReadY();
//	//	dataY = 
//	
//}




