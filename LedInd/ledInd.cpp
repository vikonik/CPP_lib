/*
Предполагается, что все сегметты имеют один порт
*/
#include "ledind.h"

LED_IND::LED_IND(){


}

	LED_IND::LED_IND(PortMapIO *pinCatode, 
          PortMapIO *seg_A, PortMapIO *seg_B,
          PortMapIO *seg_C, PortMapIO *seg_D, PortMapIO *seg_E,
          PortMapIO *seg_F, PortMapIO *seg_G, PortMapIO *seg_H)
/*: pinCatode(pinCatode), 
           seg_A(seg_A),  seg_B(seg_B),
           seg_C(seg_C),  seg_D(seg_D),  seg_E(seg_E),
           seg_F(seg_F),  seg_G(seg_G),  seg_H(seg_H)*/
{

}

//void LED_IND::initCatode(){

//}


void LED_IND::initDigit(){
//DIG_0 = seg_A->getPin() + seg_B->getPin()  + seg_C->getPin()  + seg_D->getPin()  + seg_E->getPin()  + seg_F->getPin() ;

}
