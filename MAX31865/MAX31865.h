#ifndef _MAX31865_H
#define _MAX31865_H
#include "MDR1986VE1T.h"                // Device header

#include "spi.h"
#include "port.h"
#include "delay.h"
#define MAX31865_CONFIG_REG 0x00
#define MAX31865_CONFIG_BIAS 0x80
#define MAX31865_CONFIG_MODEAUTO 0x40
#define MAX31865_CONFIG_MODEOFF 0x00
#define MAX31865_CONFIG_1SHOT 0x20 
#define MAX31865_CONFIG_3WIRE 0x10
#define MAX31865_CONFIG_24WIRE 0x00
#define MAX31865_CONFIG_FAULTSTAT 0x02
#define MAX31865_CONFIG_FILT50HZ 0x01
#define MAX31865_CONFIG_FILT60HZ 0x00

#define MAX31865_RTDMSB_REG 0x01
#define MAX31865_RTDLSB_REG 0x02
#define MAX31865_HFAULTMSB_REG 0x03
#define MAX31865_HFAULTLSB_REG 0x04
#define MAX31865_LFAULTMSB_REG 0x05
#define MAX31865_LFAULTLSB_REG 0x06
#define MAX31865_FAULTSTAT_REG 0x07

#define MAX31865_FAULT_HIGHTHRESH 0x80
#define MAX31865_FAULT_LOWTHRESH 0x40
#define MAX31865_FAULT_REFINLOW 0x20
#define MAX31865_FAULT_REFINHIGH 0x10
#define MAX31865_FAULT_RTDINLOW 0x08
#define MAX31865_FAULT_OVUV 0x04

#define RTD_A 3.9083e-3
#define RTD_B -5.775e-7

#define MAX31865_EN   spi_cs->setLow()
#define MAX31865_DES  spi_cs->setHigh()

typedef enum max31865_numwires {
  MAX31865_2WIRE = 0,
  MAX31865_3WIRE = 1,
  MAX31865_4WIRE = 0
} max31865_numwires_t;

/*! Interface class for the MAX31865 RTD Sensor reader */
class  MAX31865 : public SPI, public PortMapIO, public DELAY{
public:

   MAX31865(SPI *spi, PortMapIO *spi_cs);

  bool begin(max31865_numwires_t x = MAX31865_2WIRE);

  uint8_t readFault(void);
  void clearFault(void);
  uint16_t readRTD();

  void setWires(max31865_numwires_t wires);
  void autoConvert(bool b);
  void enable50Hz(bool b);
  void enableBias(bool b);

  double temperature(double RTDnominal, double refResistor);

private:
   SPI *spi_dev;
   PortMapIO *spi_cs;

  void readRegisterN(uint8_t addr, uint8_t buffer[], uint8_t n);

  uint8_t readRegister8(uint8_t addr);
  uint16_t readRegister16(uint8_t addr);

  void writeRegister8(uint8_t addr, uint8_t reg);
};


#endif
