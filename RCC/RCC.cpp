#include "RCC.h"
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK

RCC::RCC(uint8_t fclk_MHz){
  RST_CLK_DeInit();
  setSysClock(fclk_MHz);
}


/*
Настройка тактирования микроконтроллера
на вход частота в мегогерцах
*/
void RCC::setSysClock(uint8_t fclk_MHz)
{
	/*
	Сначала заведем внутренний генератор, если этого не сделать то в режиме отладки выпадает в Hard Falout
	*/
	if(RST_CLK_HSIstatus() == SUCCESS){
		/* Select HSI clock on the CPU clock MUX */
			RST_CLK_CPUclkSelection(RST_CLK_CPUclkHSI );
	}
	else{
			while(1);	
	}
	
	/*
	не знаю надо или нет
	*/
MDR_RST_CLK->PER_CLOCK |=0x08;	
MDR_EEPROM->CMD = (3<<3);
MDR_RST_CLK->PER_CLOCK &=~0x08;		
	
	/*
		Теперь заводим внешний ГЕНЕРАТОР, у нас не резонатор а генератор.
		поэтому конфигурим как RST_CLK_HSE_Bypass
		частота работы 8МГц
	*/
	RST_CLK_HSEconfig(RST_CLK_HSE_ON );
	if (RST_CLK_HSEstatus() == SUCCESS) /* Good HSE clock */
		{
			/* Select HSE clock as CPU_PLL input clock source */
			/* Set PLL multiplier to 1 */
uint32_t tmp = fclk_MHz * 1000000 / HSE_Value; 
if(tmp > 16) tmp = 16;

			RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, tmp-1);
			/* Enable CPU_PLL */
			RST_CLK_CPU_PLLcmd(ENABLE);
			/* Switch LED2 on and wait for PLL ready status */
			if (RST_CLK_HSEstatus() == SUCCESS) /* Good CPU PLL */
			{

				/* Set CPU_C3_prescaler to 2 */
				RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1 );
				RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
				/* Set CPU_C2_SEL to CPU_PLL output instead of CPU_C1 clock */
				RST_CLK_CPU_PLLuse(ENABLE);
				

			}
			else /* CPU_PLL timeout */
			{

			}
			
		}
		else /* HSE timeout */
		{

		}
		SystemCoreClockUpdate();//Обновили переменную содержащую сведения о частоте
	//ystemCoreClock = SystemCoreClock * (RST_CLK_CPU_PLLmul10 + 1);

}
