#ifndef _HEF4051_H
#define _HEF4051_H
#include "port.h"

class HEF4051 : public PortMapIO{
public:
HEF4051(PortMapIO *S1, PortMapIO *S2, PortMapIO *S3,  PortMapIO *E);
void selectLine(uint8_t line);
void EN();
void DES();

private:
PortMapIO *S1;
PortMapIO *S2;
PortMapIO *S3;
PortMapIO *E;
//PortMapIO *Z;


};
#endif
