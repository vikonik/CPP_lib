#include "uart.h"

UART::UART(MDR_UART_TypeDef* UARTx, uint32_t UART_BaudRate, uint16_t UART_WordLength, uint16_t UART_StopBits,uint16_t UART_Parity, uint16_t UART_FIFOMode, uint16_t UART_HardwareFlowControl )
:currentUART(UARTx)
{
  UART_InitTypeDef uart;
  UART_DeInit(UARTx);
  UART_StructInit(&uart);
  UART_BRGInit(UARTx,UART_HCLKdiv128);
  uart.UART_BaudRate = UART_BaudRate;
  uart.UART_WordLength = UART_WordLength;
  uart.UART_StopBits = UART_StopBits;
  uart.UART_Parity = UART_Parity;
  uart.UART_FIFOMode = UART_FIFOMode;
  uart.UART_HardwareFlowControl = UART_HardwareFlowControl;
  UART_Init(UARTx, &uart);
  UART_Cmd(UARTx, ENABLE);
}

/**
  * @brief  Enables or disables the specified UART interrupts.
  * @param  UARTx: Select the UART peripheral.
  *         This parameter can be one of the following values:
  *         UART1, UART2.
  * @param  UART_IT: specifies the UART interrupt sources to be enabled or disabled.
  *         This parameter can be one of the following values:
  *           @arg UART_IT_OE:  Buffer overflow interrupt (UARTOEINTR).
  *           @arg UART_IT_BE:  Line break interrupt (UARTBEINTR).
  *           @arg UART_IT_PE:  Parity error interrupt (UARTPEINTR).
  *           @arg UART_IT_FE:  Frame structure error interrupt (UARTFEINTR).
  *           @arg UART_IT_RT:  Data input timeout interrupt (UARTRTINTR).
  *           @arg UART_IT_TX:  Transmitter interrupt (UARTTXINTR).
  *           @arg UART_IT_RX:  Receiver interrupt (UARTRXINTR).
  *           @arg UART_IT_DSR: Line nUARTDSR change interrupt (UARTDSRINTR).
  *           @arg UART_IT_DCD: Line nUARTDCD change interrupt (UARTDCDINTR).
  *           @arg UART_IT_CTS: Line nUARTCTS change interrupt (UARTCTSINTR).
  *           @arg UART_IT_RI:  Line nUARTRI change interrupt (UARTRIINTR).
  * @param  NewState: new state of the specified UARTx interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART::ITConfig(MDR_UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState){
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  assert_param(IS_UART_CONFIG_IT(UART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    UARTx->IMSC |= UART_IT;
  }
  else
  {
    UARTx->IMSC &= ~UART_IT;
  }
}

/**/
void UART::enableIRQ(){
  if(currentUART == MDR_UART1)
    NVIC_EnableIRQ(UART1_IRQn);
  if(currentUART == MDR_UART2)
    NVIC_EnableIRQ(UART2_IRQn);

}

/**/
void UART::sendByte(uint8_t byte){
	/* Check TXFE flag*/
   while (UART_GetFlagStatus (currentUART,UART_FLAG_BUSY)){};//UART_FLAG_TXFE!= SET UART_FLAG_BUSY

   /* Send Data from UART1 */
   UART_SendData (currentUART,byte);//MDR_UART2
	while (UART_GetFlagStatus (currentUART,UART_FLAG_BUSY)){};
}

/**/
void UART::sendBytes(uint8_t *data, uint16_t size){

	while (size--){
    sendByte((uint8_t)*data++);
	}
  while (UART_GetFlagStatus (currentUART,UART_FLAG_BUSY ) );//UART_FLAG_TXFE!= SET
}
/**/
void UART::sendString(char *data){
	while (*data){
    sendByte((uint8_t)*data++);
	}
	while (UART_GetFlagStatus (currentUART,UART_FLAG_BUSY ) );//UART_FLAG_TXFE!= SET
}

/**/






