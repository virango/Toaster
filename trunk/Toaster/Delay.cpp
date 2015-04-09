#include "Delay.h"

Delay::Delay()
{

}

Delay::~Delay()
{

}

void Delay::consumeSysExMsg(ByteArray* msg)
{
}

unsigned char Delay::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void Delay::requestValues()
{
}
