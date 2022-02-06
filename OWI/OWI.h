#ifndef _OWI_H
#define _OWI_H
#include "uart.h"
#include "stdint.h"

class OWI{
public:
  OWI(UART *OWIuart);
  void init(void);
uint8_t touchBit(uint8_t outValue);
  void writeBit1(void);
  void writeBit0(void);
  uint8_t readBit(void);
  uint8_t detectPresence(void);
void sendByte(uint8_t data);
unsigned char receiveByte(void);
void skipRom(void);
void readRom(uint8_t * romValue);
void matchRom(uint8_t * romValue, uint8_t pins);
unsigned char searchRom(uint8_t * bitPattern, uint8_t lastDeviation, uint8_t pin);

/****************OWI Hight level function**************/
void OWI_SendByte(unsigned char data);
unsigned char OWI_ReceiveByte(void);
void OWI_SkipRom(void);
void OWI_ReadRom(uint8_t * romValue);
void OWI_MatchRom(unsigned char * romValue, unsigned char pins);
unsigned char OWI_SearchRom(unsigned char * bitPattern, unsigned char lastDeviation, unsigned char pins);

void readTemp(uint8_t *data);
/******************************************************/
private:
  UART *OWIuart;


};
#endif
