#include "OWI.h"

//#include "OWIUARTBitFunctions.h"
//#include "OWIBitFunctions.h"
#include "OWIdefs.h"	

OWI::OWI(UART *OWIuart):OWIuart(OWIuart){


}
/*
 *ƒл¤ отправки команды присутстви¤ нужно перевести UART на скорость 9600
 *ƒл¤ работы с шиной присутстви¤ нужно перевести UART на скорость 115200
 */

/* 
 *  »нициализаци¤ UART дл¤ сипользовани¤ 1-wire
 * 	¬се настройки пишем руками!!! 
 * 	ƒлина сообщении¤ 8 бит, стоповый 1, четновти нет
 */
void OWI::init(void)
{	
	
//    /* Enables the HSI clock on PORTB,PORTD */
// // RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC,ENABLE);
//	RST_CLK_PCLKcmd(RST_CLK_PCLK_UART2,ENABLE);
//  /* Fill PortInit structure*/
//  UsartPORT.PORT_PULL_UP = PORT_PULL_UP_OFF;
//  UsartPORT.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
//  UsartPORT.PORT_PD_SHM = PORT_PD_SHM_OFF;
//  UsartPORT.PORT_PD = PORT_PD_DRIVER;
//  UsartPORT.PORT_GFEN = PORT_GFEN_OFF;
//  UsartPORT.PORT_FUNC = PORT_FUNC_OVERRID;
//  UsartPORT.PORT_SPEED = PORT_SPEED_MAXFAST;
//  UsartPORT.PORT_MODE = PORT_MODE_DIGITAL;

//  /* Configure PORTB pins 13 (UART1_TX) as output */
//  UsartPORT.PORT_OE = PORT_OE_OUT;
//  UsartPORT.PORT_Pin = RS_TXD;
//  PORT_Init(MDR_PORTC, &UsartPORT);

//  /* Configure PORTB pins 14 (UART1_RX) as input */
//  UsartPORT.PORT_OE = PORT_OE_IN;
//  UsartPORT.PORT_Pin = RS_RXD;
//  PORT_Init(MDR_PORTC, &UsartPORT);


//  /* Initialize UART_InitStructure */
//	UART_InitStructure.UART_BaudRate                = 9600;//112200;//112200;//109000;57600
//  UART_InitStructure.UART_WordLength              = UART_WordLength8b;
//  UART_InitStructure.UART_StopBits                = UART_StopBits1;
//  UART_InitStructure.UART_Parity                  = UART_Parity_No;
//  UART_InitStructure.UART_FIFOMode                = UART_FIFO_OFF;
//  UART_InitStructure.UART_HardwareFlowControl     = UART_HardwareFlowControl_RXE | UART_HardwareFlowControl_TXE;

//	UART_BRGInit(MDR_UART2, UART_HCLKdiv1);
// 
//  /* Configure UART1 parameters*/
//  UART_Init (MDR_UART2,&UART_InitStructure);
//  /* Enable transmitter interrupt (UARTTXINTR) */
// // UART_ITConfig (MDR_UART1, UART_IT_RX, ENABLE);
//  /* Enables UART1 peripheral */
//  UART_Cmd(MDR_UART2,ENABLE);
}


/* 	‘ункци¤ пишет и читает данные с шины по одному биту
 *	јргументом ¤вл¤етс¤ передаваемый бит
 *  ‘ункци¤ возвращает прин¤тый бит
 */
uint8_t OWI::touchBit(uint8_t outValue)
{
this->OWIuart->sendByte(outValue);
//		return  UART_ReceiveData (this->OWIuart->getUart());
return  UART_ReceiveData (MDR_UART1);
}

/*! \brief Write a '1' bit to the bus(es). (Polled UART DRIVER)
 *
 *  Generates the waveform for transmission of a '1' bit on the 1-Wire
 *  bus.
 */
void OWI::writeBit1(void)
{
    touchBit(OWI_UART_WRITE1);
}


/*! \brief  Write a '0' to the bus(es). (Polled UART DRIVER)
 *
 *  Generates the waveform for transmission of a '0' bit on the 1-Wire(R)
 *  bus.
 */
void OWI::writeBit0(void)
{
    touchBit(OWI_UART_WRITE0);
}


/*! \brief  Read a bit from the bus(es). (Polled UART DRIVER)
 *
 *  Generates the waveform for reception of a bit on the 1-Wire(R) bus(es).
 *
 *  \return The value read from the bus (0 or 1).
 */
uint8_t OWI::readBit(void)
{
     // Return 1 if the value received matches the value sent.
     // Return 0 else. (A slave held the bus low).
     return (touchBit(OWI_UART_READ_BIT) == OWI_UART_READ_BIT);
}


/*	Определяем наличие устройства на шине
 *
 */
uint8_t OWI::detectPresence(void)
{
	uint8_t data = 0;
  this->OWIuart->changeSpeed(9600);
	data = touchBit(0xF0);
	this->OWIuart->changeSpeed(115200);
    
    // Return 0 if the value received matches the value sent.
    // return 1 else. (Presence detected)
    return (data != 0xF0); 
}

/*******************************************/

void OWI::sendByte(uint8_t data)
{
    unsigned char temp;
    unsigned char i;
    
    // Do once for each bit
    for (i = 0; i < 8; i++)
    {
        // Determine if lsb is '0' or '1' and transmit corresponding
        // waveform on the bus.
        temp = data & 0x01;
        if (temp)
        {
            writeBit1();
        }
        else
        {
            writeBit0();
        }
        // Right shift the data to get next bit.
        data >>= 1;
    }
}


/*! \brief  Receives one byte of data from the 1-Wire(R) bus.
 *
 *  This function automates the task of receiving a complete byte 
 *  of data from the 1-Wire bus.
 *
 *  \param  pin     A bitmask of the bus to read from.
 *  
 *  \return     The byte read from the bus.
 */
unsigned char OWI::receiveByte(void)
{
    unsigned char data;
    unsigned char i;

    // Clear the temporary input variable.
    data = 0x00;
    
    // Do once for each bit
    for (i = 0; i < 8; i++)
    {
        // Shift temporary input variable right.
        data >>= 1;
        // Set the msb if a '1' value is read from the bus.
        // Leave as it is ('0') else.
        if (readBit())
        {
            // Set msb
            data |= 0x80;
        }
    }
    return data;
}


/*! \brief  Sends the SKIP ROM command to the 1-Wire bus(es).
 *
 *  \param  pins    A bitmask of the buses to send the SKIP ROM command to.
 */
void OWI::skipRom(void)
{
    // Send the SKIP ROM command on the bus.
    sendByte(OWI_ROM_SKIP);
}


/*! \brief  Sends the READ ROM command and reads back the ROM id.
 *
 *  \param  romValue    A pointer where the id will be placed.
 *
 *  \param  pin     A bitmask of the bus to read from.
 */
void OWI::readRom(uint8_t * romValue)
{
    unsigned char bytesLeft = 8;

    // Send the READ ROM command on the bus.
    sendByte(OWI_ROM_READ);
    
    // Do 8 times.
    while (bytesLeft > 0)
    {
        // Place the received data in memory.
        *romValue++ = receiveByte();
       
			bytesLeft--;
			
    }
}

/*
Запускаем преобразование температуры и читаем её значение
data - массив куда скинуть температуру, старший байт градусы, младший дробная часть
*/
void OWI::readTemp(uint8_t *data){
uint8_t bytesLeft = 9;//читаем всю память
	
detectPresence();
skipRom();
sendByte(0x44);	//Запустили преобразование температуры
	
detectPresence();
skipRom();
sendByte(OWI_ROM_SCRATCHPAD);
    while (bytesLeft > 0)
    {
        // Place the received data in memory.
        *data++ =  /*debug[bytesLeft] = */receiveByte();
        bytesLeft--;
    }
detectPresence();		
}
	
	
	
	
	
/*! \brief  Sends the MATCH ROM command and the ROM id to match against.
 *
 *  \param  romValue    A pointer to the ID to match against.
 *
 *  \param  pins    A bitmask of the buses to perform the MATCH ROM command on.
 */
void OWI::matchRom(uint8_t * romValue, uint8_t pins)
{
    unsigned char bytesLeft = 8;   
    
    // Send the MATCH ROM command.
    sendByte(OWI_ROM_MATCH);

    // Do once for each byte.
    while (bytesLeft > 0)
    {
        // Transmit 1 byte of the ID to match.
        sendByte(*romValue++);
        bytesLeft--;
    }
}


/*! \brief  Sends the SEARCH ROM command and returns 1 id found on the 
 *          1-Wire(R) bus.
 *
 *  \param  bitPattern      A pointer to an 8 byte char array where the 
 *                          discovered identifier will be placed. When 
 *                          searching for several slaves, a copy of the 
 *                          last found identifier should be supplied in 
 *                          the array, or the search will fail.
 *
 *  \param  lastDeviation   The bit position where the algorithm made a 
 *                          choice the last time it was run. This argument 
 *                          should be 0 when a search is initiated. Supplying 
 *                          the return argument of this function when calling 
 *                          repeatedly will go through the complete slave 
 *                          search.
 *
 *  \param  pin             A bit-mask of the bus to perform a ROM search on.
 *
 *  \return The last bit position where there was a discrepancy between slave addresses the last time this function was run. 
 *		Returns OWI_ROM_SEARCH_FAILED if an error was detected (e.g. a device was connected to the bus during the search), 
 *		or OWI_ROM_SEARCH_FINISHED when there are no more devices to be discovered.
 *
 *  \note   See main.c for an example of how to utilize this function.
 */
unsigned char OWI::searchRom(uint8_t * bitPattern, uint8_t lastDeviation, uint8_t pin)
{
    unsigned char currentBit = 1;
    unsigned char newDeviation = 0;
    unsigned char bitMask = 0x01;
    unsigned char bitA;
    unsigned char bitB;

    // Send SEARCH ROM command on the bus.
    sendByte(OWI_ROM_SEARCH);
    
    // Walk through all 64 bits.
    while (currentBit <= 64)
    {
        // Read bit from bus twice.
        bitA = readBit();
        bitB = readBit();

        if (bitA && bitB)
        {
            // Both bits 1 (Error).
            newDeviation = OWI_ROM_SEARCH_FAILED;
            return newDeviation;//доаисал аргумент. Изначально его нбыло
        }
        else if (bitA ^ bitB)
        {
            // Bits A and B are different. All devices have the same bit here.
            // Set the bit in bitPattern to this value.
            if (bitA)
            {
                (*bitPattern) |= bitMask;
            }
            else
            {
                (*bitPattern) &= ~bitMask;
            }
        }
        else // Both bits 0
        {
            // If this is where a choice was made the last time,
            // a '1' bit is selected this time.
            if (currentBit == lastDeviation)
            {
                (*bitPattern) |= bitMask;
            }
            // For the rest of the id, '0' bits are selected when
            // discrepancies occur.
            else if (currentBit > lastDeviation)
            {
                (*bitPattern) &= ~bitMask;
                newDeviation = currentBit;
            }
            // If current bit in bit pattern = 0, then this is
            // out new deviation.
            else if ( !(*bitPattern & bitMask)) 
            {
                newDeviation = currentBit;
            }
            // IF the bit is already 1, do nothing.
            else
            {
            
            }
        }
                
        
        // Send the selected bit to the bus.
        if ((*bitPattern) & bitMask)
        {
            writeBit1();
        }
        else
        {
            writeBit0();
        }

        // Increment current bit.    
        currentBit++;

        // Adjust bitMask and bitPattern pointer.    
        bitMask <<= 1;
        if (!bitMask)
        {
            bitMask = 0x01;
            bitPattern++;
        }
    }
    return newDeviation;
}





//
