#ifndef _ADC_H_
#define _ADC_H_
#include "MDR32F9Qx_adc.h"              // Keil::Drivers:ADC

#include "port.h"




/*
Предполагается, что выводы уже настроены
*/
class ADC: public PortMapIO{
	public:
ADC();
ADC(PortMapIO *adcPin);

void init();//
void IRQ_ON();
void setChannel(uint32_t Channel);
void setChannels(uint32_t ChannelMask);
void Start();
void Stop();
void switchToSinglConversion();
void switchToCicliclConversion();
uint16_t readData();
	private:
		PortMapIO *adcPin;
};
#endif
