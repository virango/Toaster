#include "Rig.h"

Rig::Rig()
{

}

Rig::~Rig()
{

}

void Rig::consumeSysExMsg(ByteArray* msg)
{
}

unsigned char Rig::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void Rig::requestValues()
{
}
