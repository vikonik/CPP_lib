#include "MDR32F9Qx_config.h"           // Keil::Device:Startup
#include "port.h"
#include "spi.h"
#include "delay.h"
#include "MDR32F9Qx_it.h"
#include "RCC.h"
#include "uart.h"
#include "OWI.h"
extern 	uint32_t tickDelay;
DELAY *pause;
#define PORT_UART     MDR_PORTC
#define PIN_UART_RX   PORT_Pin_4
#define PIN_UART_TX   PORT_Pin_3

uint8_t detectPresent = 0;
uint8_t TEM[9];	
uint8_t TEMP_H = 0;
uint8_t TEMP_L=0;
uint32_t temperature = 0;


int main(void){
RCC rcc(144);
PortMapIO *uartRX = new PortMapIO(MDR_PORTC, 
PIN_UART_RX,PORT_OE_IN,
PORT_PULL_UP_OFF,PORT_PULL_DOWN_OFF,
PORT_PD_SHM_OFF, PORT_PD_OPEN,
PORT_GFEN_OFF,PORT_FUNC_MAIN, 
PORT_SPEED_MAXFAST,PORT_MODE_DIGITAL);

PortMapIO *uartTX = new PortMapIO(MDR_PORTC, 
PIN_UART_TX,PORT_OE_OUT,
PORT_PULL_UP_OFF,PORT_PULL_DOWN_OFF,
PORT_PD_SHM_OFF, PORT_PD_DRIVER,
PORT_GFEN_OFF,PORT_FUNC_MAIN, 
PORT_SPEED_MAXFAST,PORT_MODE_DIGITAL);

UART *uart = new UART(MDR_UART1,9600,UART_WordLength8b,UART_StopBits1,UART_Parity_No,UART_FIFO_OFF,UART_HardwareFlowControl_RXE|UART_HardwareFlowControl_TXE);
OWI *owi = new OWI(uart);


//uart->sendByte(0xF0);
//detectPresent = UART_ReceiveData(MDR_UART1);
//uart->sendByte(0xF0);
detectPresent = owi->detectPresence();

while(1){
//
owi->readTemp(TEM);
temperature = TEM[1];
temperature <<= 8;
temperature |= TEM[0];
temperature *= 625;

TEMP_H = temperature/10000;
temperature -= (TEMP_H * 10000);
TEMP_L = temperature/100;
//
for(int i=0; i< 0xFFFF; i++);

}
}
