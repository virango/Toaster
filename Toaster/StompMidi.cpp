#include <vector>
#include "StompMidi.h"
#include "Midi.h"

// address pages
BYTEARRAYDEF(StompMidi, AddressPageA,       0x32)
BYTEARRAYDEF(StompMidi, AddressPageB,       0x33)
BYTEARRAYDEF(StompMidi, AddressPageC,       0x34)
BYTEARRAYDEF(StompMidi, AddressPageD,       0x35)
BYTEARRAYDEF(StompMidi, AddressPageX,       0x38)
BYTEARRAYDEF(StompMidi, AddressPageMOD,     0x3A)
// parameter
BYTEARRAYDEF(StompMidi, Type,               0x00)
BYTEARRAYDEF(StompMidi, OnOff,              0x03)

StompMidi::StompMidi(Instance instance)
  : mInstance(instance)
{
  SysExMsgDispatcher::get().addConsumer(this);
}

StompMidi::~StompMidi()
{
}

void StompMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = msg->at(10) << 8 | msg->at(11);
    const char fct = msg->at(9);
    if(fct == sOnOff[0])
      midiOnOffReceived(rawVal);
  }
}

unsigned char StompMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void StompMidi::midiApplyOnOff(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sOnOff, rawVal));
}

void StompMidi::midiRequestOnOff()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sOnOff));
}

void StompMidi::midiRequestType()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sType));
}

ByteArray StompMidi::getAddressPage()
{
  switch(mInstance)
  {
    case A:
      return sAddressPageA;
    case B:
      return sAddressPageB;
    case C:
      return sAddressPageC;
    case D:
      return sAddressPageD;
    case X:
      return sAddressPageX;
    case MOD:
      return sAddressPageMOD;
    default:
      return ByteArray();
  }
}

