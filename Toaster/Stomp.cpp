#include "Stomp.h"

Stomp::Stomp(StompMidi::Instance instance)
  : QObject(0)
  , StompMidi(instance)
{

}

Stomp::~Stomp()
{
}

void Stomp::requestAllValues()
{
  midiRequestOnOff();
  midiRequestType();
}

// slots
void Stomp::applyOnOff(bool onOff)
{
  unsigned short rawVal = onOff ? 1 : 0;
  midiApplyOnOff(rawVal);
}

void Stomp::applyType(FXType type)
{
  unsigned short rawVal = (unsigned short) type;
  midiApplyType(rawVal);
}

// StompMidi callbacks
void Stomp::midiOnOffReceived(unsigned short rawVal)
{
  bool onOff = rawVal != 0;
  emit onOffReceived(onOff);
}

void Stomp::midiTypeReceived(unsigned short rawVal)
{
  FXType type = (FXType)rawVal;
  emit typeReceived(type);
}
