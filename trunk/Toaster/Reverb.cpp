#include "Reverb.h"

Reverb::Reverb()
{

}

Reverb::~Reverb()
{

}

void Reverb::consumeSysExMsg(ByteArray* msg)
{
}

unsigned char Reverb::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void Reverb::requestValues()
{
}
