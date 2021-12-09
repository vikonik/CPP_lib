/*
Предполагается, что все сегметты имеют один порт
*/
#include "ledind.h"

/***********************************************************************/
LED_CODE::LED_CODE(){

}

LED_CODE::LED_CODE( 
          PortMapIO *seg_A, PortMapIO *seg_B,
          PortMapIO *seg_C, PortMapIO *seg_D, PortMapIO *seg_E,
          PortMapIO *seg_F, PortMapIO *seg_G, PortMapIO *seg_H,
          PortMapIO *seg_I, PortMapIO *seg_J)
:         seg_A(seg_A),  seg_B(seg_B),
           seg_C(seg_C),  seg_D(seg_D),  seg_E(seg_E),
           seg_F(seg_F),  seg_G(seg_G),  seg_H(seg_H),
           seg_I(seg_I),  seg_J(seg_J)
{

}



/*
Устанавливаем код цыфры
*/
void LED_CODE::setCode(uint8_t digit){
		seg_A->setLow();
		seg_B->setLow();
		seg_C->setLow();
		seg_D->setLow();
		seg_E->setLow();
		seg_F->setLow();
		seg_G->setLow();
    seg_H->setLow();
    seg_I->setLow();
    seg_J->setLow();
uint8_t dgt = digit & 0x0F;
switch(dgt){
	case 0://SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F
		seg_A->setHigh();
		seg_B->setHigh();
		seg_C->setHigh();
		seg_D->setHigh();
		seg_E->setHigh();
		seg_F->setHigh();

		break;
	
	case 1://SEG_B + SEG_C
		seg_B->setHigh();
		seg_C->setHigh();
		break;	
	
	case 2://SEG_A + SEG_B + SEG_D + SEG_E + SEG_G
		seg_A->setHigh();
		seg_B->setHigh();
		seg_D->setHigh();
		seg_E->setHigh();
		seg_G->setHigh();
		break;	
	
	case 3://SEG_A + SEG_B + SEG_C + SEG_D +  SEG_G
		seg_A->setHigh();
		seg_B->setHigh();
		seg_C->setHigh();
		seg_D->setHigh();
		seg_G->setHigh();
		break;	

	case 4://SEG_B + SEG_C + SEG_F + SEG_G
		seg_B->setHigh();
		seg_C->setHigh();
		seg_F->setHigh();
		seg_G->setHigh();
		break;	

	case 5://SEG_A + SEG_C + SEG_D + SEG_F + SEG_G
		seg_A->setHigh();
		seg_C->setHigh();
		seg_D->setHigh();
		seg_F->setHigh();
		seg_G->setHigh();
		break;	
	
	case 6://SEG_A + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G
		seg_A->setHigh();
		seg_C->setHigh();
		seg_D->setHigh();
		seg_E->setHigh();
		seg_F->setHigh();
		seg_G->setHigh();
		break;	

	case 7://SEG_A + SEG_B +SEG_C 
		seg_A->setHigh();
		seg_B->setHigh();	
		seg_C->setHigh();
		break;

	case 8://SEG_A + SEG_B +SEG_C + SEG_D + SEG_E + SEG_F + SEG_G
		seg_A->setHigh();
		seg_B->setHigh();	
		seg_C->setHigh();
		seg_D->setHigh();
		seg_E->setHigh();
		seg_F->setHigh();
		seg_G->setHigh();
		break;	

	case 9://SEG_A + SEG_B +SEG_C + SEG_D + SEG_F + SEG_G
		seg_A->setHigh();
		seg_B->setHigh();	
		seg_C->setHigh();
		seg_D->setHigh();
		seg_F->setHigh();
		seg_G->setHigh();
		break;	

	default : break;
}

if(digit & 0x80){
switch(digit){
//Управление светодиодами
case 0x80:
		seg_A->setLow();
		seg_B->setLow();
		seg_C->setLow();
		seg_D->setLow();
		seg_E->setLow();
		seg_F->setLow();
		seg_G->setLow();
    seg_H->setLow();
    seg_I->setLow();
    seg_J->setLow();
break;
case 0x81:
		seg_A->setHigh();
		seg_B->setLow();
		seg_C->setLow();
		seg_D->setLow();
		seg_E->setLow();
		seg_F->setLow();
		seg_G->setLow();
    seg_H->setLow();
    seg_I->setLow();
    seg_J->setLow();
break;
case 0x82:
		seg_A->setHigh();
		seg_B->setHigh();
		seg_C->setLow();
		seg_D->setLow();
		seg_E->setLow();
		seg_F->setLow();
		seg_G->setLow();
    seg_H->setLow();
    seg_I->setLow();
    seg_J->setLow();
break;
case 0x83:
		seg_A->setHigh();
		seg_B->setHigh();
		seg_C->setHigh();
		seg_D->setLow();
		seg_E->setLow();
		seg_F->setLow();
		seg_G->setLow();
    seg_H->setLow();
    seg_I->setLow();
    seg_J->setLow();
break;
case 0x84:
		seg_A->setHigh();
		seg_B->setHigh();
		seg_C->setHigh();
		seg_D->setHigh();
		seg_E->setLow();
		seg_F->setLow();
		seg_G->setLow();
    seg_H->setLow();
    seg_I->setLow();
    seg_J->setLow();
break;
case 0x85:
		seg_A->setHigh();
		seg_B->setHigh();
		seg_C->setHigh();
		seg_D->setHigh();
		seg_E->setHigh();
		seg_F->setLow();
		seg_G->setLow();
    seg_H->setLow();
    seg_I->setLow();
    seg_J->setLow();
break;
case 0x86:
		seg_A->setHigh();
		seg_B->setHigh();
		seg_C->setHigh();
		seg_D->setHigh();
		seg_E->setHigh();
		seg_F->setHigh();
		seg_G->setLow();
    seg_H->setLow();
    seg_I->setLow();
    seg_J->setLow();
break;
case 0x87:
		seg_A->setHigh();
		seg_B->setHigh();
		seg_C->setHigh();
		seg_D->setHigh();
		seg_E->setHigh();
		seg_F->setHigh();
		seg_G->setHigh();
    seg_H->setLow();
    seg_I->setLow();
    seg_J->setLow();
break;

case 0x88:
		seg_A->setHigh();
		seg_B->setHigh();
		seg_C->setHigh();
		seg_D->setHigh();
		seg_E->setHigh();
		seg_F->setHigh();
		seg_G->setHigh();
		seg_H->setHigh();
    seg_I->setLow();
    seg_J->setLow();
break;
case 0x89:
		seg_A->setHigh();
		seg_B->setHigh();
		seg_C->setHigh();
		seg_D->setHigh();
		seg_E->setHigh();
		seg_F->setHigh();
		seg_G->setHigh();
		seg_H->setHigh();
    seg_I->setHigh();
    seg_J->setLow();
break;
case 0x8A:
		seg_A->setHigh();
		seg_B->setHigh();
		seg_C->setHigh();
		seg_D->setHigh();
		seg_E->setHigh();
		seg_F->setHigh();
		seg_G->setHigh();
		seg_H->setHigh();
    seg_I->setHigh();
    seg_J->setHigh();
break;
	default : break;
}
}

uint8_t led = digit & 0x30;
switch(led){
case (0x10):
seg_I->setHigh();
break;

case (0x20):
seg_J->setHigh();
break;

default : 
break;
}
}
/****************************************************************************/

LED_CATODE::LED_CATODE(){}
LED_CATODE::LED_CATODE(PortMapIO *pinCatode):pinCatode(pinCatode){}

/********************************************************/
	
	
	LED_DIGIT::LED_DIGIT(LED_CODE *ledCode, LED_CATODE *catode)
	:ledCode(ledCode),catode(catode)
{

}	
	
	LED_DIGIT::LED_DIGIT(LED_CODE *ledCode, LED_CATODE *catode, uint8_t numDigit)
	:ledCode(ledCode),catode(catode),numDigit(numDigit)
{

}	
	
/*
numDigit - номер индикатора
digit - выводимое число
*/
void LED_DIGIT::showDigit(uint8_t _numDigit, uint16_t _digit){
if(_numDigit > this->numDigit)return;
			this->ledCode->setCode(_digit);
	for(int i = 0; i < this->numDigit; i++){
		if(i == _numDigit){
			(&this->catode[i])->catodeOn();
		}
		else{
			(&this->catode[i])->catodeOff();
		}
	}
}
	

	
