#include "Cab.h"

Cab::Cab()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

Cab::~Cab()
{
}

void Cab::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = msg->at(10) << 8 | msg->at(11);
    const char fct = msg->at(9);
    if(fct == sOnOff[0])
    {
      bool onOff = rawVal != 0;
      emit onOffReceived(onOff);
    }
  }
}

unsigned char Cab::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void Cab::requestValues()
{
}
