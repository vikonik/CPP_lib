#ifndef _ADC_H_
#define _ADC_H_
#include "port.h"




/*
Предполагается, что выводы уже настроены
*/
class ADC: public PortMapIO{
ADC();


void init();//
void IRQ_ON();
void setChannel(uint32_t Channel);
void setChannels(uint32_t ChannelMask);
void Start();

};
#endif
