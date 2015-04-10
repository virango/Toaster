#include "Cab.h"

Cab::Cab()
{
}

Cab::~Cab()
{
}

void Cab::requestValues()
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
  misiApplyVolume(phys2Raw(volume, , ));
}         

void Cab::applyHighShift(double highShift)
{         
  midiApplyHightShift(phys2Raw(highShift, , ));
}         

void Cab::applyLowShift(double lowShift)
{         
  midiApplyLowShift(phys2Raw(lowShift, , ));
}         

void Cab::applyCharacter(double character)
{
  midiApplyCharacter(phys2Raw(character, , ));
}

// CabMidi
void Cab::midiOnOffReceived(unsigned short rawVal)
{
  emit onOffReceived(raw2Bool(rawVal));
}

void Cab::midiVolumeReceived(unsigned short rawVal)
{
  emit volumeReceived(raw2Phys(rawVal, , ));
}

void Cab::midiHighShiftReceived(unsigned short rawVal)
{
  emit highShiftReceived(raw2Phys(rawVal, , ));
}

void Cab::midiLowShiftReceived(unsigned short rawVal)
{
  emit lowShiftReceived(raw2Phys(rawVal, , ));
}

void Cab::midiCharacterReceived(unsigned short rawVal)
{
  emit characterReceived(raw2Phys(rawVal, , ));
}
