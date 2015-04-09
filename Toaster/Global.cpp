#include "Global.h"

Global::Global()
{

}

Global::~Global()
{

}

void Global::consumeSysExMsg(ByteArray* msg)
{
}

unsigned char Global::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void Global::requestValues()
{
}
