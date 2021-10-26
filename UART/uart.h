#ifndef _UART_H
#define _UART_H
#include "MDR32F9Qx_uart.h"             // Keil::Drivers:UART

class UART{
public:
UART(MDR_UART_TypeDef* UARTx, uint32_t UART_BaudRate, uint16_t UART_WordLength, uint16_t UART_StopBits,uint16_t UART_Parity, uint16_t UART_FIFOMode, uint16_t UART_HardwareFlowControl   );

private:
MDR_UART_TypeDef* currentUART;

};

#endif