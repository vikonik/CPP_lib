#ifndef _SPI_H_
#define _SPI_H_
#include "MDR32F9Qx_config.h"           // Keil::Device:Startup

#include "MDR32F9Qx_ssp.h"              // Keil::Drivers:SSP
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT

#include "port.h"
class SPI : public PortMapIO{
	public:
SPI();		
SPI(MDR_SSP_TypeDef *spi,uint16_t wordLenght);
SPI(MDR_SSP_TypeDef *spi, PortMapIO *MOSI, PortMapIO *MISO, PortMapIO *SCK, uint16_t wordLenght);
	
	uint16_t transmit(uint16_t *data);
	
  void write_then_read(uint16_t *write_buffer,
                          size_t write_len, uint16_t *read_buffer,
                          size_t read_len, uint16_t sendvalue = 0xFFFF); 	
	
  void write(uint16_t *write_buffer, size_t write_len);

	private:
		void init(uint16_t wordLenght);
	MDR_SSP_TypeDef *spi;	
	PortMapIO *MOSI;
	PortMapIO *MISO; 
	PortMapIO *SCK;
	
	
};

#endif
