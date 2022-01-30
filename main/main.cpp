#include "MDR32F9Qx_config.h"           // Keil::Device:Startup
#include "port.h"
#include "spi.h"
#include "w25qxx.h"
#include "delay.h"
#include "MDR32F9Qx_it.h"
PortMapIO *cs_w25qxx ;
SPI *spi;
DELAY *pause;
extern 	uint32_t tickDelay;
uint16_t a = 0;
uint8_t buf1[256];
uint8_t buf2[512];
uint8_t PageStatus = 0;
uint8_t init1 = 0;
uint8_t init2 = 0;

int main(void){

pause = new DELAY;
 cs_w25qxx = new PortMapIO(MDR_PORTC, PORT_Pin_8);
 spi = new SPI(MDR_SSP1, MDR_PORTC,PORT_Pin_5, PORT_Pin_6, PORT_Pin_7, 0,PORT_FUNC_ALTER);
init1 = W25qxx_Init();
	W25qxx_ResetChip();
init2 = W25qxx_Init();

//for(int i = 0; i < w25qxx.BlockCount; i++){
//if(W25qxx_IsEmptyBlock(i,0,0))PageStatus++;
//}


W25qxx_EraseSector(W25qxx_PageToSector(0));
for(int i = 0; i < 256; i++)buf1[i] = i;
//W25qxx_WriteByte(buf1[1], 0);
//W25qxx_WriteByte(buf1[2], 1);
//W25qxx_WriteByte(buf1[3], 2);
W25qxx_WritePage(buf1,0,0,0);
//for(int i = 0; i < 256; i++)buf1[i] = 0;
W25qxx_ReadPage(buf2, 0, 0, 0);
//W25qxx_Init();
while(1){
a++;
}
}
