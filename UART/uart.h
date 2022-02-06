#ifndef _UART_H
#define _UART_H
#include "MDR32F9Qx_uart.h"             // Keil::Drivers:UART

class UART{
public:
UART(MDR_UART_TypeDef* UARTx, uint32_t UART_BaudRate, uint16_t UART_WordLength, uint16_t UART_StopBits,uint16_t UART_Parity, uint16_t UART_FIFOMode, uint16_t UART_HardwareFlowControl   );
/**/
void ITConfig(MDR_UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState);
/**/
void enableIRQ();
/**/
void sendByte(uint8_t byte);
/**/
void sendBytes(uint8_t *data, uint16_t size);
/**/
void sendString(char *data);
/**/
MDR_UART_TypeDef *getUart(){return currentUART;}
/**/
void disableUart(){UART_Cmd(currentUART,DISABLE);}
/**/
void changeSpeed(uint32_t newSpeed);

private:
  UART_InitTypeDef strucktUART_InitTypeDef;
MDR_UART_TypeDef* currentUART;

};

#endif
