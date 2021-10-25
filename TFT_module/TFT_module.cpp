#include "TFT_module.h"



TFT_MODULE::TFT_MODULE( MDR_PORT_TypeDef *_touchPortXp,		
												MDR_PORT_TypeDef *_touchPortXm,
												MDR_PORT_TypeDef *_touchPortYp,		
												MDR_PORT_TypeDef *_touchPortYm,
												uint16_t _pinXp,
												uint16_t _pinXm,
												uint16_t _pinYp,
												uint16_t _pinYm){

													
}
												

void TFT_MODULE::initTouch(){
//	Xp =  PortMapIO(touchPortXp, pinXp);
//	Ym =  PortMapIO(touchPortYm, pinYm);
//	
//	Xm = PortMapIO(touchPortXm, pinXm);
	
}


/**
* @brief  Переключаемся на работу с дисплеем
  *  
  *  
*/
void TFT_MODULE::switchToTFT(void){

}

/**
* @brief  Переключаемся на работу с тачскрином
  * @param  
  * @retval 
*/
void TFT_MODULE::switchToTouch(void){

}

/**/
//void TFT_MODULE::switchToTouchReadX(void){
////	Xp =  PortMapIO(touchPortXp, pinXp);
////	Xm =  PortMapIO(touchPortXm, pinXm);
////	Xp.setHigh();
////	Xm.setLow();
////	
//}
