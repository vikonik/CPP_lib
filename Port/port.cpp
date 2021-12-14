#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT


#include "port.h"

PortMapIO::PortMapIO()
{

}
PortMapIO::PortMapIO (MDR_PORT_TypeDef *port, uint16_t pin):m_port(port), m_pin(pin) {
	this->init();

}



PortMapIO::PortMapIO (MDR_PORT_TypeDef *_port, 
											uint16_t _pin, 
											PORT_OE_TypeDef _PORT_OE, 
											PORT_PULL_UP_TypeDef _PORT_PULL_UP , 
											PORT_PULL_DOWN_TypeDef _PORT_PULL_DOWN , 
											PORT_PD_SHM_TypeDef _PORT_PD_SHM , 
											PORT_PD_TypeDef _PORT_PD, 
											PORT_GFEN_TypeDef _PORT_GFEN, 
											PORT_FUNC_TypeDef _PORT_FUNC , 
											PORT_SPEED_TypeDef _PORT_SPEED , 
											PORT_MODE_TypeDef _PORT_MODE )
:m_port(_port), m_pin(_pin)
{
enablePort();
											
this->fullInitPin(_PORT_OE, 
							 _PORT_PULL_UP, _PORT_PULL_DOWN, _PORT_PD_SHM, 
							 _PORT_PD, _PORT_GFEN, _PORT_FUNC, _PORT_SPEED, _PORT_MODE);


}
/**/
void PortMapIO::enablePort(){
				//Инициализация пина
		
		if (m_port == MDR_PORTA)
			RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);	

		if (m_port ==  MDR_PORTB)
			RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);	

		if (m_port ==  MDR_PORTC)
			RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);	

		if (m_port ==  MDR_PORTD)
			RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);	

		if (m_port ==  MDR_PORTE)
			RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE, ENABLE);	

		if (m_port ==  MDR_PORTF)
			RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTF, ENABLE);	
}

void PortMapIO::init(){
	m_status=0;
	enablePort();
PORT_InitTypeDef prt;
		PORT_StructInit(&prt);
		prt.PORT_FUNC = PORT_FUNC_PORT;
		prt.PORT_GFEN = PORT_GFEN_OFF;
		prt.PORT_MODE = PORT_MODE_DIGITAL;
		prt.PORT_OE = PORT_OE_OUT;
		prt.PORT_PD = PORT_PD_DRIVER;
		prt.PORT_PD_SHM = PORT_PD_SHM_OFF;
		prt.PORT_Pin = this->m_pin;
		prt.PORT_PULL_DOWN = PORT_PULL_DOWN_ON;
		prt.PORT_PULL_UP = PORT_PULL_UP_OFF;
		prt.PORT_SPEED = PORT_SPEED_MAXFAST;
		PORT_Init(this->m_port,&prt);


}


void PortMapIO::togglePin()
{

//	HAL_GPIO_TogglePin(m_port,_pin);
//	m_status=!m_status;
}

void PortMapIO::setLow()
{
	PORT_ResetBits(this->m_port,this->m_pin);	
	m_status=0;
}

void PortMapIO::setHigh()
{
	PORT_SetBits(this->m_port,this->m_pin);	
	m_status=1;
}

uint8_t PortMapIO::getStatus()
{
	return PORT_ReadInputDataBit(this->m_port,this->m_pin);
//	return _status;
}

/**/
void PortMapIO::PortMapIoPORT_Write(uint16_t *data){
	
	PORT_Write(this->m_port,*data);
}

uint16_t PortMapIO::PortMapIoPORT_Read(){
	return PORT_ReadInputData(this->m_port);
}


/*
Инициализация вывода с полной нвтсройкой
*/
void PortMapIO::fullInitPin( 
							PORT_OE_TypeDef _PORT_OE, 
							PORT_PULL_UP_TypeDef _PORT_PULL_UP, 
							PORT_PULL_DOWN_TypeDef _PORT_PULL_DOWN, 
							PORT_PD_SHM_TypeDef _PORT_PD_SHM, 
							PORT_PD_TypeDef _PORT_PD, 
							PORT_GFEN_TypeDef _PORT_GFEN, 
							PORT_FUNC_TypeDef _PORT_FUNC, 
							PORT_SPEED_TypeDef _PORT_SPEED, 
							PORT_MODE_TypeDef _PORT_MODE)
{
								
  PORT_InitTypeDef PortStructInit;
	PORT_StructInit(&PortStructInit);
	PortStructInit.PORT_Pin = this->m_pin;						
	PortStructInit.PORT_OE = _PORT_OE;
	PortStructInit.PORT_PULL_UP	= _PORT_PULL_UP;						
	PortStructInit.PORT_PULL_DOWN = _PORT_PULL_DOWN;		
	PortStructInit.PORT_PD_SHM =	_PORT_PD_SHM;	
	PortStructInit.PORT_PD =	_PORT_PD;
	PortStructInit.PORT_GFEN = _PORT_GFEN;					
	PortStructInit.PORT_FUNC = _PORT_FUNC;
	PortStructInit.PORT_SPEED = _PORT_SPEED;							
	PortStructInit.PORT_MODE = _PORT_MODE;
PORT_Init(this->m_port,&PortStructInit);

}

/*
Переключение пина на вход
*/
void PortMapIO::setPinAsInput(){
	this->m_port->ANALOG |= this->m_pin;
	this->m_port->OE &= ~this->m_pin;
	this->m_port->PD |= this->m_pin;//Открытый сток
	this->m_port->PULL &= ~this->m_pin;//Убираем подтяжку от нуля	
	this->m_port->PULL |= (this->m_pin << 16);//Подтяжка к "1"
	this->m_port->FUNC &= ~(3 << ((this->m_pin-1)*2));
}

/*
Отключаем пин
*/
void PortMapIO::setPinAsOff(){
	this->m_port->ANALOG &= ~this->m_pin;
	this->m_port->OE &= ~this->m_pin;//Вход
	this->m_port->PD &= ~this->m_pin;//Открытый сток
	this->m_port->PULL &= ~this->m_pin;//Убираем подтяжку от нуля	
	this->m_port->PULL &= ~(this->m_pin << 16);//Убираем подтяжку от "1"	
	this->m_port->FUNC &= ~(3 << ((this->m_pin-1)*2));
}

/*
Переключение пина на выход
*/
void PortMapIO::setPinAsOutput(){
	this->m_port->ANALOG |= this->m_pin;
	this->m_port->OE |= this->m_pin;//Выход
	this->m_port->PD &= ~(this->m_pin);//Режим драйвер
	this->m_port->PULL |= this->m_pin;//Ставим подтяжку к нулю	
	this->m_port->PULL &= ~(this->m_pin << 16);//Убираем подтяжку от "1"	
	this->m_port->FUNC &= ~(3 << ((this->m_pin-1)*2));
}

/*
Переключение пина как аналоговый
*/
void PortMapIO::setPinAsAnalog(){
	this->m_port->OE &= ~this->m_pin;//Вход
	this->m_port->PULL &= ~(this->m_pin);//Убираем подтяжку от "0"
	this->m_port->PULL &= ~(this->m_pin << 16);//Убираем подтяжку от "1"	
	this->m_port->FUNC &= ~(3 << ((this->m_pin-1)*2));
	
	this->m_port->ANALOG &= ~this->m_pin;
	this->m_port->GFEN &= ~this->m_pin;
	

}
/*
Переключаемся на альтернативную функутю
digital 1 цифровой, 0 аналоговый
OE - 1 выход, 0 вход

*/
void PortMapIO::setPinAsAlternative(uint8_t digital, uint8_t OE){
if(digital)
	this->m_port->ANALOG |= this->m_pin;
else
	this->m_port->ANALOG &= ~this->m_pin;	

if(OE)
	this->m_port->OE |= this->m_pin;
else
	this->m_port->OE &= ~this->m_pin;	

	this->m_port->PULL &= ~(this->m_pin);//Убираем подтяжку от "0"
	this->m_port->PULL &= ~(this->m_pin << 16);//Убираем подтяжку от "1"	
	this->m_port->FUNC |= (2 << ((this->m_pin-1)*2));
}
/*
Переключение фугнкции пина
*/
//void PortMapIO::setPinFunction(){}


//	initPin(MDR_PORTA, MCU_SSR_INT | MCU_SSR_EXT0 | MCU_SSR_EXT1 | MCU_SWLP_OUT_0|MCU_SWLP_OUT_1|MCU_SWHP_OUT_0|MCU_SWHP_OUT_1, PORT_OE_OUT, 
//		PORT_PULL_UP_OFF, PORT_PULL_DOWN_ON, PORT_PD_SHM_OFF, 
//		PORT_PD_DRIVER, PORT_GFEN_OFF, PORT_FUNC_PORT,
//		PORT_SPEED_FAST,PORT_MODE_DIGITAL);
