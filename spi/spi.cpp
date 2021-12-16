#include "spi.h"

/*
Пока что таботаем только на SPI_1
*/
SPI::SPI(){

};		

	SPI::SPI(MDR_SSP_TypeDef *spi, uint16_t wordLenght):spi(spi){
		init(wordLenght);
	}

SPI::SPI(MDR_SSP_TypeDef *spi,
 PortMapIO *MOSI, PortMapIO *MISO, PortMapIO *SCK, uint16_t wordLenght)
 :spi(spi), MOSI(MOSI),  MISO(MISO),  SCK(MISO){
	

	init(wordLenght);
}
 /**/

void SPI::init(uint16_t wordLenght){
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
	
	if(IS_SSP_WORD_LENGTH(wordLenght))
		SPI_InitStructure.SSP_WordLength = wordLenght;
	else
		SPI_InitStructure.SSP_WordLength = SSP_WordLength8b;
	
SSP_BRGInit(this->spi,SSP_HCLKdiv16);
	SSP_Init(this->spi, &SPI_InitStructure);	
	SSP_Cmd(this->spi, ENABLE);	
}

/**/
uint16_t SPI::transmit(uint16_t *data){
	SSP_SendData(this->spi, *data);
	while(SSP_GetFlagStatus(this->spi, SSP_FLAG_BSY));
	return(SSP_ReceiveData(this->spi));
}

/**/
void SPI::write_then_read(uint16_t *write_buffer,
                          size_t write_len, uint16_t *read_buffer,
                          size_t read_len, uint16_t sendvalue ) {
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
void SPI::write(uint16_t *write_buffer, size_t write_len) {
  uint32_t  cnt = write_len;
  while(cnt--){
    transmit(write_buffer++);
  }

}













