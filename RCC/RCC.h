#ifndef _RCC_H
#define _RCC_H
#include "MDR32F9Qx_config.h"

class RCC{
public:
RCC(uint8_t fclk_MHz);
void setSysClock(uint8_t fclk_MHz);
private:

};

#endif
