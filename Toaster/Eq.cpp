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

Eq& Eq::get()
{
  static Eq eq;
  return eq;
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
  midiApplyOnOff(Utils::bool2Raw(onOff));
}

void Eq::applyBass(double bass)
{
  midiApplyBass(Utils::phys2Raw(bass, 10.0, -5.0));
}

void Eq::applyMiddle(double middle)
{
  midiApplyMiddle(Utils::phys2Raw(middle, 10.0, -5.0));
}

void Eq::applyTreble(double treble)
{
  midiApplyTreble(Utils::phys2Raw(treble, 10.0, -5.0));
}

void Eq::applyPresence(double presence)
{
  midiApplyPresence(Utils::phys2Raw(presence, 10.0, -5.0));
}

// EqMidi callbacks
void Eq::midiOnOffReceived(unsigned short rawVal)
{
  emit onOffReceived(Utils::raw2Bool(rawVal));
}

void Eq::midiBassReceived(unsigned short rawVal)
{
  emit bassReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}

void Eq::midiMiddleReceived(unsigned short rawVal)
{
  emit middleReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}

void Eq::midiTrebleReceived(unsigned short rawVal)
{
  emit trebleReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}

void Eq::midiPresenceReceived(unsigned short rawVal)
{
  emit presenceReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}

