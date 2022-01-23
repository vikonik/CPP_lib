#ifndef _SPI_H_
#define _SPI_H_
#include "MDR1986VE1T.h"                // Device header
#include "MDR32F9Qx_ssp.h"              // Keil::Drivers:SSP
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT

#include "port.h"
class SPI : public PortMapIO{
	public:
SPI();		
SPI(MDR_SSP_TypeDef *spi);
SPI(MDR_SSP_TypeDef *spi, PortMapIO *MOSI, PortMapIO *MISO, PortMapIO *SCK);
SPI(MDR_SSP_TypeDef *spi, MDR_PORT_TypeDef *port, uint16_t MOSI, uint16_t MISO, uint16_t SCK, uint8_t regim);
	
	uint8_t transmit(uint8_t *data);
  void write_then_read(uint8_t *write_buffer,
                          size_t write_len, uint8_t *read_buffer,
                          size_t read_len, uint8_t sendvalue = 0xFF); 	
  void write(uint8_t *write_buffer, size_t write_len);

	private:
		void init(uint8_t regim);
    void initPort(MDR_PORT_TypeDef *port, uint16_t MOSI, uint16_t MISO, uint16_t SCK);

	MDR_SSP_TypeDef *spi;
	MDR_PORT_TypeDef *PORT;

	PortMapIO *mosi;
	PortMapIO *miso; 
	PortMapIO *sck;
	
	
};

#endif
