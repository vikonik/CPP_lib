#include "spi.h"

/*
Пока что таботаем только на SPI_1
*/
SPI::SPI(){

};		

	SPI::SPI(MDR_SSP_TypeDef *spi):spi(spi){
		init();
	}

SPI::SPI(MDR_SSP_TypeDef *spi,
 PortMapIO *MOSI, PortMapIO *MISO, PortMapIO *SCK)
 :spi(spi), MOSI(MOSI),  MISO(MISO),  SCK(MISO){
	
	init();
}
 /**/

void SPI::init(){
		SSP_InitTypeDef SPI_InitStructure;
		if(spi == MDR_SSP1)	RST_CLK_PCLKcmd(RST_CLK_PCLK_SSP1, ENABLE);	
	if(spi == MDR_SSP2) RST_CLK_PCLKcmd(RST_CLK_PCLK_SSP2, ENABLE);	
	SSP_StructInit(&SPI_InitStructure);	
	SPI_InitStructure.SSP_CPSDVSR	= 2;
	SPI_InitStructure.SSP_FRF = SSP_FRF_SPI_Motorola;
	SPI_InitStructure.SSP_HardwareFlowControl = SSP_HardwareFlowControl_None;
	SPI_InitStructure.SSP_Mode = SSP_ModeMaster;
	SPI_InitStructure.SSP_SCR = 0;
	SPI_InitStructure.SSP_SPH = SSP_SPH_1Edge;
	SPI_InitStructure.SSP_SPO = SSP_SPO_Low;
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













