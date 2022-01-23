#include "spi.h"

/*
Пока что таботаем только на SPI_1
*/
SPI::SPI(){

};		

	SPI::SPI(MDR_SSP_TypeDef *spi):spi(spi){
		init(0);
	}

SPI::SPI(MDR_SSP_TypeDef *spi,
 PortMapIO *MOSI, PortMapIO *MISO, PortMapIO *SCK)
 :spi(spi), mosi(MOSI),  miso(MISO),  sck(MISO){
	
	init(0);
}

SPI::SPI(MDR_SSP_TypeDef *spi, MDR_PORT_TypeDef *port, uint16_t MOSI, uint16_t MISO, uint16_t SCK, uint8_t regim)
:spi(spi){
  initPort( port, MOSI,  MISO,  SCK);
init(regim);
}
 /**/
void SPI::initPort(MDR_PORT_TypeDef *port, uint16_t MOSI, uint16_t MISO, uint16_t SCK){
  mosi = new PortMapIO(port, MOSI,PORT_OE_OUT,PORT_PULL_UP_OFF, PORT_PULL_DOWN_OFF,PORT_PD_SHM_OFF,PORT_PD_DRIVER,PORT_GFEN_OFF,PORT_FUNC_MAIN,PORT_SPEED_MAXFAST,PORT_MODE_DIGITAL );
  miso = new PortMapIO(port, MISO,PORT_OE_IN,PORT_PULL_UP_OFF, PORT_PULL_DOWN_OFF,PORT_PD_SHM_OFF,PORT_PD_DRIVER,PORT_GFEN_OFF,PORT_FUNC_MAIN,PORT_SPEED_MAXFAST,PORT_MODE_DIGITAL );
  sck  = new PortMapIO(port, SCK,PORT_OE_OUT,PORT_PULL_UP_OFF, PORT_PULL_DOWN_OFF,PORT_PD_SHM_OFF,PORT_PD_DRIVER,PORT_GFEN_OFF,PORT_FUNC_MAIN,PORT_SPEED_MAXFAST,PORT_MODE_DIGITAL );


//MDR_PORT_TypeDef *port, 
//											uint16_t PORT_Pin, 
//											PORT_OE_TypeDef PORT_OE, 
//											PORT_PULL_UP_TypeDef PORT_PULL_UP ,     
//											PORT_PULL_DOWN_TypeDef PORT_PULL_DOWN , 
//											PORT_PD_SHM_TypeDef PORT_PD_SHM ,       
//											PORT_PD_TypeDef PORT_PD,                
//											PORT_GFEN_TypeDef PORT_GFEN,            
//											PORT_FUNC_TypeDef PORT_FUNC ,           
//											PORT_SPEED_TypeDef PORT_SPEED ,         
//											PORT_MODE_TypeDef PORT_MODE )           
}
/**/
void SPI::init(uint8_t regim){
		SSP_InitTypeDef SPI_InitStructure;
		if(spi == MDR_SSP1)	RST_CLK_PCLKcmd(RST_CLK_PCLK_SSP1, ENABLE);	
    if(spi == MDR_SSP2) RST_CLK_PCLKcmd(RST_CLK_PCLK_SSP2, ENABLE);	
SSP_BRGInit(MDR_SSP2, SSP_HCLKdiv16 );
    SSP_StructInit(&SPI_InitStructure);	
    SPI_InitStructure.SSP_CPSDVSR	= 255;
    SPI_InitStructure.SSP_FRF = SSP_FRF_SPI_Motorola;
    SPI_InitStructure.SSP_HardwareFlowControl = SSP_HardwareFlowControl_None;
    SPI_InitStructure.SSP_Mode = SSP_ModeMaster;
    SPI_InitStructure.SSP_SCR = 0;
switch(regim){
case 1:
    SPI_InitStructure.SSP_SPH = SSP_SPH_2Edge;
    SPI_InitStructure.SSP_SPO = SSP_SPO_Low;
break;
case 2:
    SPI_InitStructure.SSP_SPH = SSP_SPH_1Edge;
    SPI_InitStructure.SSP_SPO = SSP_SPO_High;
break;
case 3:
    SPI_InitStructure.SSP_SPH = SSP_SPH_2Edge;
    SPI_InitStructure.SSP_SPO = SSP_SPO_High;
break;
default:
    SPI_InitStructure.SSP_SPH = SSP_SPH_1Edge;
    SPI_InitStructure.SSP_SPO = SSP_SPO_Low;
break;

}

    SPI_InitStructure.SSP_WordLength = SSP_WordLength8b;
	

    SSP_Init(this->spi, &SPI_InitStructure);	
    SSP_Cmd(this->spi, ENABLE);	
}

/**/
uint8_t SPI::transmit(uint8_t *data){
	SSP_SendData(this->spi, *data);
	while(SSP_GetFlagStatus(this->spi, SSP_FLAG_BSY));
	return(SSP_ReceiveData(this->spi));
}

/**/
void SPI::write_then_read(uint8_t *write_buffer,
                          size_t write_len, uint8_t *read_buffer,
                          size_t read_len, uint8_t sendvalue ) {
  uint32_t  cnt = write_len;
  while(cnt--){
    transmit(write_buffer++);
  }

  cnt = read_len;
  while(cnt--){
    *(read_buffer++) =  transmit(&sendvalue);
  }
}

/**/
void SPI::write(uint8_t *write_buffer, size_t write_len) {
  uint32_t  cnt = write_len;
  while(cnt--){
    transmit(write_buffer++);
  }

}













