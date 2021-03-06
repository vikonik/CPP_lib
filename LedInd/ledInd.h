#ifndef _LED_H
#define _LED_H
#include "MDR1986VE1T.h"                // Device header
#include "MDR32F9Qx_port.h"
#include "port.h"
//#define NUM_OF_DIGIT	6//количество индикаторов

//#define CATODE //для индикаторов с общим катодом


//индикатор с общим катодом
//#define LED_DIGIT_PORT 	MDR_PORTB

//#define SEG_A	PORT_Pin_0//(1<<PD0)
//#define SEG_B	PORT_Pin_1//(1<<PD1)
//#define SEG_C	PORT_Pin_2//(1<<PD2)
//#define SEG_D	PORT_Pin_3//(1<<PD3)
//#define SEG_E	PORT_Pin_4//(1<<PD4)
//#define SEG_F	PORT_Pin_5//(1<<PD5)
//#define SEG_G	PORT_Pin_6//(1<<PD6)

//#ifdef CATODE
//	#define DIG_0		SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F
//	#define DIG_1		SEG_B + SEG_C
//	#define DIG_2		SEG_A + SEG_B + SEG_D + SEG_E + SEG_G
//	#define DIG_3		SEG_A + SEG_B + SEG_C + SEG_D +  SEG_G
//	#define DIG_4		SEG_B + SEG_C + SEG_F + SEG_G
//	#define DIG_5		SEG_A + SEG_C + SEG_D + SEG_F + SEG_G
//	#define DIG_6		SEG_A + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G
//	#define DIG_7		SEG_A + SEG_B +SEG_C 
//	#define DIG_8		SEG_A + SEG_B +SEG_C + SEG_D + SEG_E + SEG_F + SEG_G
//	#define DIG_9		SEG_A + SEG_B +SEG_C + SEG_D + SEG_F + SEG_G
//	#define PROBEL 	0
//	#else
//	#define DIG_0		!(SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F)
//	#define DIG_1		!(SEG_B + SEG_C)
//	#define DIG_2		!(SEG_A + SEG_B + SEG_D + SEG_E + SEG_G)
//	#define DIG_3		!(SEG_A + SEG_B + SEG_C + SEG_D +  SEG_G)
//	#define DIG_4		!(SEG_B + SEG_C + SEG_F + SEG_G)
//	#define DIG_5		!(SEG_A + SEG_C + SEG_D + SEG_F + SEG_G)
//	#define DIG_6		!(SEG_A + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G)
//	#define DIG_7		!(SEG_A + SEG_B +SEG_C)
//	#define DIG_8		!(SEG_A + SEG_B +SEG_C + SEG_D + SEG_E + SEG_F + SEG_G)
//	#define DIG_9		!(SEG_A + SEG_B +SEG_C + SEG_D + SEG_F + SEG_G)
//	#define PROBEL 	!0
//#endif

////#define LED_CATODE_DDR 		DDRB
//#define LED_CATODE_PORT 	MDR_PORTB
//#define LED_CATODE_1		PORT_Pin_0
//#define LED_CATODE_2		PORT_Pin_1
//#define LED_CATODE_3		PORT_Pin_2
//#define LED_CATODE_4		PORT_Pin_3


//массив с цифрами
//uint8_t myDigit[10]={
//	DIG_0,
//	DIG_1,
//	DIG_2,
//	DIG_3,
//	DIG_4,
//	DIG_5,
//	DIG_6,
//	DIG_7,
//	DIG_8,
//	DIG_9
//};

//const uint16_t ledEnable[NUM_OF_DIGIT] = {
//LED_CATODE_1,
//LED_CATODE_2,
//LED_CATODE_3,
//LED_CATODE_4,
//	0,
//	0
//};

//PORT_MODE_TypeDef *portsCatode,
//uint8_t DIG_0;
//uint8_t DIG_1;
//uint8_t DIG_2;
//uint8_t DIG_3;
//uint8_t DIG_4;
//uint8_t DIG_5;
//uint8_t DIG_6;
//uint8_t DIG_7;
//uint8_t DIG_8;
//uint8_t DIG_9;

// uint8_t myDigit[10]={
//	DIG_0,
//	DIG_1,
//	DIG_2,
//	DIG_3,
//	DIG_4,
//	DIG_5,
//	DIG_6,
//	DIG_7,
//	DIG_8,
//	DIG_9
//};


/**********************************************************************/
class LED_CODE{
	public:
		LED_CODE();
	
    LED_CODE(PortMapIO *seg_A, PortMapIO *seg_B,
          PortMapIO *seg_C, PortMapIO *seg_D, PortMapIO *seg_E,
          PortMapIO *seg_F, PortMapIO *seg_G, PortMapIO *seg_H,
          PortMapIO *seg_I, PortMapIO *seg_J);
	
	void initDigit();
	void setCode(uint8_t digit);
	private:
		
PortMapIO *seg_A; 
PortMapIO *seg_B;
PortMapIO *seg_C;
PortMapIO *seg_D;
PortMapIO *seg_E;
PortMapIO *seg_F;
PortMapIO *seg_G;
PortMapIO *seg_H;
PortMapIO *seg_I;
PortMapIO *seg_J;

//	uint8_t *digit = &myDigit;
	
};

/*********************************************************************************/
class LED_CATODE{
	public:
		LED_CATODE();
		LED_CATODE(PortMapIO *pinCatode);	
	
		void addCatode(PortMapIO *pinCatode){this->pinCatode = pinCatode;}
		void catodeOff(){pinCatode->setHigh();}
		void catodeOn(){pinCatode->setLow();}
    void setHi(){pinCatode->setHigh();}
    void setLow(){pinCatode->setLow();}
	private:
		PortMapIO *pinCatode;
	
	
};

/****************************************************************************/
class LED_DIGIT{
	public:
		LED_DIGIT(LED_CODE *ledCode, LED_CATODE *catode);
		LED_DIGIT(LED_CODE *ledCode, LED_CATODE *catode, uint8_t numDigit);
		LED_CODE *ledCode;
		LED_CATODE *catode;
	
	void showDigit(uint8_t _numDigit, uint16_t _digit);

	private:
		uint8_t numDigit;

};
#endif
