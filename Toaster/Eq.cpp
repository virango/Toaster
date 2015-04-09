#include "Eq.h"

Eq::Eq()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

Eq::~Eq()
{

}

void Eq::requestAllValues()
{
  midiRequestOnOff();
  midiRequestBass();
  midiRequestMiddle();
  midiRequestTreble();
  midiRequestPresence();
}

// slots
void Eq::applyOnOff(bool onOff)
{
  midiApplyOnOff(bool2Raw(onOff));
}

void Eq::applyBassReceived(double bass)
{
  midiApplyBass(phys2Raw(bass, 10.0, -5.0));
}

void Eq::applyMiddleReceived(double middle)
{
  midiApplyMiddle(phys2Raw(middle, 10.0, -5.0));
}

void Eq::applyTrebleReceived(double treble)
{
  midiApplyTreble(phys2Raw(treble, 10.0, -5.0));
}

void Eq::applyPresenceReceived(double presence)
{
  midiApplyPresence(phys2Raw(presence, 10.0, -5.0));
}

// EqMidi callbacks
void Eq::midiOnOffReceived(unsigned short rawVal)
{
  emit onOffReceived(raw2Bool(rawVal));
}

void Eq::midiBassReceived(unsigned short rawVal)
{
  emit bassReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Eq::midiMiddleReceived(unsigned short rawVal)
{
  emit middleReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Eq::midiTrebleReceived(unsigned short rawVal)
{
  emit trebleReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Eq::midiPresenceReceived(unsigned short rawVal)
{
  emit presenceReceived(raw2Phys(rawVal, 10.0, -5.0));
}

