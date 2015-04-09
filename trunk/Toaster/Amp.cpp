#include "Amp.h"
#include "Midi.h"

Amp::Amp()
{
}

Amp::~Amp()
{
}

void Amp::requestAllValues()
{
  midiRequestOnOff();
  midiRequestGain();
}

void Amp::applyGain(double gain)
{
  unsigned short rawVal = (gain * 0x8000) / 10;
  midiApplyGain(rawVal);
}

void Amp::midiGainReceived(unsigned short rawVal)
{
  double physVal = (rawVal * 10.0) / 0x8000;
  emit gainReceived(physVal);
}
