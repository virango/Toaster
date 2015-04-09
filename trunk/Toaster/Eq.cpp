#include "Eq.h"

Eq::Eq()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

Eq::~Eq()
{

}

void Eq::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = extractRawVal(msg->at(10), msg->at(11));
    const char fct = msg->at(9);
    if(fct == sOnOff[0])
    {
      bool onOff = rawVal != 0;
      emit onOffReceived(onOff);
    }
    else
    {
      // the range of all parameter below is [-5..5]
      double physVal = ((rawVal * 10.0) / 0x8000) - 5;
      if(fct == sBass[0])
        emit bassReceived(physVal);
      else if(fct == sMiddle[0])
        emit middleReceived(physVal);
      else if(fct == sTreble[0])
        emit trebleReceived(physVal);
      else if(fct == sPresence[0])
        emit presenceReceived(physVal);
    }
  }
}

unsigned char Eq::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void Eq::requestValues()
{
  getOnOff();
  getBass();
  getMiddle();
  getTreble();
  getPresence();
}
