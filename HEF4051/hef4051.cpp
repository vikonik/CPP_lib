#include "hef4051.h"


HEF4051::HEF4051(PortMapIO *S1, PortMapIO *S2, PortMapIO *S3,  PortMapIO *E)
:S1(S1), S2(S2), S3(S3), E(E)
{

}

void HEF4051::selectLine(uint8_t line)
{
  uint8_t tmp = line;
  uint8_t s1,s2,s3;
  s1 = tmp%2;
  tmp /= 2;
  s2 = tmp%2;
  s3 = tmp / 2;
  (!!s1) ? S1->setHigh() : S1->setLow();
  (!!s2) ? S2->setHigh() : S2->setLow();
  (!!s3) ? S3->setHigh() : S3->setLow();

}

/**/
void HEF4051::EN(){
  E->setLow();
}

/**/
void HEF4051::DES(){
  E->setHigh();
}
