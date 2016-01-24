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
#include "Eq.h"

Eq::Eq()
{

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

void Eq::applyBass(double bass)
{
  midiApplyBass(phys2Raw(bass, 10.0, -5.0));
}

void Eq::applyMiddle(double middle)
{
  midiApplyMiddle(phys2Raw(middle, 10.0, -5.0));
}

void Eq::applyTreble(double treble)
{
  midiApplyTreble(phys2Raw(treble, 10.0, -5.0));
}

void Eq::applyPresence(double presence)
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

