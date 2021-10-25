#include "ADC.h"
#include "MDR32F9Qx_adc.h"              // Keil::Drivers:ADC


ADC::ADC(){}


/*
Инициализация основных настроек АЦП
*/
void ADC::init(){
	ADC_InitTypeDef ADC_InitStructure;
	ADCx_InitTypeDef ADCx_InitStructure;
  ADC_DeInit();
  ADC_StructInit(&ADC_InitStructure);
	ADC_InitStructure.ADC_StartDelay = 0;
	ADC_InitStructure.ADC_TempSensor = ADC_TEMP_SENSOR_Disable;
	ADC_InitStructure.ADC_TempSensorAmplifier = ADC_TEMP_SENSOR_AMPLIFIER_Disable;
	ADC_InitStructure.ADC_TempSensorConversion = ADC_TEMP_SENSOR_CONVERSION_Disable;
	ADC_InitStructure.ADC_IntVRefConversion = ADC_VREF_CONVERSION_Enable;//ADC_VREF_CONVERSION_Disable
	ADC_InitStructure.ADC_IntVRefTrimming = 6;
	ADC_Init (&ADC_InitStructure); 
	
	ADCx_StructInit (&ADCx_InitStructure);
//Источник тактирования АЦП
	ADCx_InitStructure.ADC_ClockSource = ADC_CLOCK_SOURCE_CPU;
//Делитель подбираем таким образом, чтобы частота преобразования не превышала 500кГц
	ADCx_InitStructure.ADC_Prescaler = ADC_CLK_div_512;//
//Режим преобразования однократный/непрерываный
	ADCx_InitStructure.ADC_SamplingMode = ADC_SAMPLING_MODE_SINGLE_CONV;
//Разрешить пререключение каналов
	ADCx_InitStructure.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;
//Номер канала. При опросе нескольких каналов укзать номер первого опрашиваемого канала
	ADCx_InitStructure.ADC_ChannelNumber = 0;//ADC_CH_TEMP_SENSOR ;//ADC_CH_ADC2  
//Указать все опрашиваемые каналы
	ADCx_InitStructure.ADC_Channels = 0;
	ADCx_InitStructure.ADC_DelayGo = 7;
	ADCx_InitStructure.ADC_LevelControl = ADC_LEVEL_CONTROL_Disable;
	ADCx_InitStructure.ADC_LowLevel = 0;
	ADCx_InitStructure.ADC_HighLevel = 0;
	ADCx_InitStructure.ADC_VRefSource = ADC_VREF_SOURCE_INTERNAL;//;ADC_VREF_SOURCE_EXTERNAL
	ADCx_InitStructure.ADC_IntVRefSource = ADC_INT_VREF_SOURCE_EXACT;//ADC_INT_VREF_SOURCE_INEXACT
	ADC1_Init (&ADCx_InitStructure);  
	ADC1_Cmd( ENABLE );


}

/*
Включаем прерывание
*/
void ADC::IRQ_ON(){
  NVIC_EnableIRQ(ADC_IRQn);
  ADC1_ITConfig(ADC1_IT_END_OF_CONVERSION, ENABLE);
}
/*
Устанавливаем канал для преобразования
*/
void ADC::setChannel(uint32_t Channel){
  ADC1_SetChannel(Channel);
}

/*
Устанавливаем каналы для последовательного преобразования
*/
void ADC::setChannels(uint32_t ChannelMask){
  ADC1_SetChannels(ChannelMask);
}

/*
Запуск преобразования АЦП
*/
void ADC::Start(){
  MDR_ADC->ADC1_CFG |= ADC1_CFG_REG_GO;
}

/*

*/



