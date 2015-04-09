#include "Amp.h"

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

// slots
void Amp::applyGain(double gain)
{
  midiApplyGain(phys2Raw(gain, 10.0, 0.0));
}

// AmpMidi callbacks
void Amp::midiGainReceived(unsigned short rawVal)
{
  emit gainReceived(raw2Phys(rawVal, 10.0, 0.0));
}
