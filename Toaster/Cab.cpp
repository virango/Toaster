/*  This file is part of Toaster, the editor and remote control for Kemper profiling amplifier.
*
*   Copyright (C) 2016  Thomas Langer
*
*   Toaster is free software: you can redistribute it and/or modify it under the terms of the
*   GNU General Public License as published by the Free Software Foundation, either version 3
*   of the License, or (at your option) any later version.
*
*   Toaster is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
*   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*   See the GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along with Toaster.
*   If not, see <http://www.gnu.org/licenses/>.
*/
#include "Cab.h"

Cab::Cab()
{
}

Cab::~Cab()
{
}

Cab& Cab::get()
{
  static Cab cab;
  return cab;
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
