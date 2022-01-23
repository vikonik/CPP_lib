#include "touchScreen.h"
//#include "portMapin.h"
TOUCHSCREEN::TOUCHSCREEN( 
							PortMapIO *Xp,	
							PortMapIO *Xm,
							PortMapIO *Yp,		
							PortMapIO *Ym,
							DELAY *pause,
							ADC *adc
):Xp(Xp), Xm(Xm), Yp(Yp), Ym(Ym), pause(pause), adc(adc){


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

	Xp->setPinAsOff();
	Xm->setPinAsOff();
	Yp->setPinAsOff();
	Ym->setPinAsOff();

}
/*
Чтобы определить касание прикидываемся кнопкой 
Xp - подключаем к минусу
Xm - подключаем к минусу
Ym - читаем как кнопкукнопку
Yp - висит в воздухе и не мешает
*/
void TOUCHSCREEN::switchAsButton(){
	Xp->setPinAsOutput();
	Xm->setPinAsOutput();
	Ym->setPinAsInput();
	Yp->setPinAsOff();

	Xp->setLow();
	Xm->setLow();
	
}

/**/
void TOUCHSCREEN::switchAsDisplay(){
	Xp->setPinAsOutput();
	Xm->setPinAsOutput();
	Ym->setPinAsOutput();
	Yp->setPinAsOutput();

	
}
/*
Опрашиваем нашу кнопку
возвращаем 1 если кнопка нажата
0 если нет
*/
uint8_t TOUCHSCREEN::readButon(){
	return !Ym->getStatus();
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
Читаем показания по оси X или Y
*/
uint16_t TOUCHSCREEN::readAxis(uint16_t chanelADC){
	uint8_t cnt = 32;
	uint32_t tmp = 0;
	adc->setChannel(chanelADC);	
		pause->delay_ms(10);
	while(cnt--){
//		adc->Start();
		while(ADC1_GetFlagStatus(ADCx_FLAG_END_OF_CONVERSION) != SET){}//ждем пока не закончится преобразование
		tmp += adc->readData();	
	}
	return tmp/32;
}



/*
Вернет положение нажатия XY или -1 если нажатия нет
*/
uint32_t TOUCHSCREEN::getPos(){
	
	float dataX = 0.0;
	float dataY = 0.0;
	uint32_t retData = 0;

	//Ждем пока зарядится емкость
	pause->delay_ms(5);
	//Если кнопка нажата, то читаем координату
//	if(!this->readButon()) return -1;
	
	//из-за расположения экрана меняем местами x и Y
	switchToReadX();
	pause->delay_ms(5);
	dataY = (4096-readAxis(6)-475)/10;
	
	
	switchToReadY();
	pause->delay_ms(5);
	dataX =(readAxis(2)-270)/7.3;
	
	retData = (uint16_t)dataX;
	retData <<= 16;
	retData |= (uint16_t)dataY;
	
//	switchAsDisplay();
//pause->delay_ms(5);
	return retData;
}




