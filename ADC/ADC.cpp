#include "ADC.h"
#include "MDR32F9Qx_adc.h"              // Keil::Drivers:ADC
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK


ADC::ADC(){
  RST_CLK_PCLKcmd(RST_CLK_PCLK_ADC, ENABLE);	
}

	ADC::ADC(PortMapIO *adcPin):adcPin(adcPin){RST_CLK_PCLKcmd(RST_CLK_PCLK_ADC, ENABLE);	}

/*
Инициализация основных настроек АЦП
*/
void ADC::init(){
	RST_CLK_PCLKcmd(RST_CLK_PCLK_ADC,ENABLE);
	RST_CLK_ADCclkSelection(RST_CLK_ADCclkCPU_C1);
	RST_CLK_ADCclkPrescaler(RST_CLK_ADCclkDIV1);
	RST_CLK_ADCclkEnable(ENABLE);
	ADC_InitTypeDef ADC_InitStructure;
	ADCx_InitTypeDef ADCx_InitStructure;
  ADC_StructInit(&ADC_InitStructure);
	ADCx_StructInit (&ADCx_InitStructure);
  ADC_DeInit();

ADC_InitStructure.ADC_IntVRefConversion = ADC_VREF_CONVERSION_Disable;
ADC_InitStructure.ADC_IntVRefTrimming = 7;
//ADC_InitStructure.ADC_StartDelay = 15;
ADC_InitStructure.ADC_TempSensor = ADC_TEMP_SENSOR_Disable;
ADC_InitStructure.ADC_TempSensorAmplifier = ADC_TEMP_SENSOR_AMPLIFIER_Disable;
ADC_InitStructure.ADC_TempSensorConversion = ADC_TEMP_SENSOR_CONVERSION_Disable;
	ADC_Init (&ADC_InitStructure); 
	

////Источник тактирования АЦП
//	ADCx_InitStructure.ADC_ClockSource = ADC_CLOCK_SOURCE_CPU;
////Делитель подбираем таким образом, чтобы частота преобразования не превышала 500кГц
//	ADCx_InitStructure.ADC_Prescaler = ADC_CLK_div_512;//
////Режим преобразования однократный/непрерываный
//	ADCx_InitStructure.ADC_SamplingMode = ADC_SAMPLING_MODE_CICLIC_CONV;//ADC_SAMPLING_MODE_SINGLE_CONV;
////Разрешить пререключение каналов
//	ADCx_InitStructure.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;
////Номер канала. При опросе нескольких каналов укзать номер первого опрашиваемого канала
//	ADCx_InitStructure.ADC_ChannelNumber = 0;//ADC_CH_TEMP_SENSOR ;//ADC_CH_ADC2  
////Указать все опрашиваемые каналы
//	ADCx_InitStructure.ADC_Channels = 0;
//	ADCx_InitStructure.ADC_DelayGo = 7;
//	ADCx_InitStructure.ADC_LevelControl = ADC_LEVEL_CONTROL_Disable;
//	ADCx_InitStructure.ADC_LowLevel = 0;
//	ADCx_InitStructure.ADC_HighLevel = 0;
//	ADCx_InitStructure.ADC_VRefSource = ADC_VREF_SOURCE_INTERNAL;//;ADC_VREF_SOURCE_EXTERNAL
//	ADCx_InitStructure.ADC_IntVRefSource = ADC_INT_VREF_SOURCE_EXACT;//ADC_INT_VREF_SOURCE_INEXACT



ADCx_InitStructure.ADC_ChannelNumber = ADC_CH_ADC3;
ADCx_InitStructure.ADC_Channels = 0;
ADCx_InitStructure.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;
ADCx_InitStructure.ADC_ClockSource = ADC_CLOCK_SOURCE_CPU;
ADCx_InitStructure.ADC_DelayGo = 7;
ADCx_InitStructure.ADC_HighLevel = 0;
ADCx_InitStructure.ADC_IntVRefSource = ADC_INT_VREF_SOURCE_INEXACT;
ADCx_InitStructure.ADC_LevelControl = ADC_LEVEL_CONTROL_Disable;
ADCx_InitStructure.ADC_LowLevel = 0;
ADCx_InitStructure.ADC_Prescaler = ADC_CLK_div_64;
ADCx_InitStructure.ADC_SamplingMode = ADC_SAMPLING_MODE_CYCLIC_CONV;//  ADC_SAMPLING_MODE_SINGLE_CONV
ADCx_InitStructure.ADC_VRefSource = ADC_VREF_SOURCE_INTERNAL;



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
  ADC1_SetChannel((ADCx_Channel_Number)Channel);
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
Остановка преобразования АЦП
*/
void ADC::Stop(){
  MDR_ADC->ADC1_CFG &= ~ADC1_CFG_REG_GO;
}
/*
Включить одиночные проебразования
*/
void ADC::switchToSinglConversion(){
MDR_ADC->ADC1_CFG &= ~ADC1_CFG_REG_SAMPLE;
}
/*
Включить последовательное проебразования
*/
void ADC::switchToCicliclConversion(){
MDR_ADC->ADC1_CFG |= ADC1_CFG_REG_SAMPLE;
}
/*
Чтение данных от АЦП
*/
uint16_t ADC::readData(){
uint32_t tmp = ADC1_GetResult();
	return (uint16_t)(tmp & 0x00000FFF);
}


