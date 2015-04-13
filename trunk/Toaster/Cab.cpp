#include "Cab.h"

Cab::Cab()
{
}

Cab::~Cab()
{
}

void Cab::requestAllValues()
{
  midiRequestOnOff();
  midiRequestVolume();
  midiRequestHighShift();
  midiRequestLowShift();
  midiRequestCharacter();
}

// slots
void Cab::applyOnOff(bool onOff)
{         
  midiApplyOnOff(bool2Raw(onOff));
}         

void Cab::applyVolume(double volume)
{         
  midiApplyVolume(phys2Raw(volume, 24.0, -12.0));
}         

void Cab::applyHighShift(double highShift)
{         
  midiApplyHighShift(phys2Raw(highShift, 10.0, -5.0));
}         

void Cab::applyLowShift(double lowShift)
{         
  midiApplyLowShift(phys2Raw(lowShift, 10.0, -5.0));
}         

void Cab::applyCharacter(double character)
{
  midiApplyCharacter(phys2Raw(character, 10.0, -5.0));
}

// CabMidi
void Cab::midiOnOffReceived(unsigned short rawVal)
{
  emit onOffReceived(raw2Bool(rawVal));
}

void Cab::midiVolumeReceived(unsigned short rawVal)
{
  emit volumeReceived(raw2Phys(rawVal, 24.0, -12.0));
}

void Cab::midiHighShiftReceived(unsigned short rawVal)
{
  emit highShiftReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Cab::midiLowShiftReceived(unsigned short rawVal)
{
  emit lowShiftReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Cab::midiCharacterReceived(unsigned short rawVal)
{
  emit characterReceived(raw2Phys(rawVal, 10.0, -5.0));
}
