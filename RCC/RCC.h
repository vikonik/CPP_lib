#ifndef _RCC_H
#define _RCC_H
#include "MDR1986VE1T.h"                // Device header

class RCC{
public:
RCC(uint8_t fclk_MHz);
void setSysClock(uint8_t fclk_MHz);
private:

};

#endif
