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
#include "Rig.h"

Rig::Rig()
{
}

Rig::~Rig()
{
}

Rig& Rig::get()
{
  static Rig rig;
  return rig;
}

void Rig::requestAllValues()
{
  midiRequestTempo();
  midiRequestVolume();
  midiRequestTempoEnable();
  midiRequestStompsEnable();
  midiRequestStackEnable();
  midiRequestEffectsEnable();
}

// slots
void Rig::applyTempo(double tempo)
{
  midiApplyTempo(phys2Raw(tempo, 236.0, 20.0));
}

void Rig::applyVolume(int volume)
{
  midiApplyVolume((unsigned short)volume);
}

void Rig::applyTempoEnable(bool tempoEnable)
{
  midiApplyTempoEnable(raw2Bool(tempoEnable));
}

void Rig::applyStompsEnable(bool stompsEnable)
{
  midiApplyStompsEnable(raw2Bool(stompsEnable));
}


void Rig::applyStackEnable(bool stackEnable)
{
  midiApplyStackEnable(raw2Bool(stackEnable));
}


void Rig::applyEffectsEnable(bool effectsEnable)
{
  midiApplyEffectsEnable(raw2Bool(effectsEnable));
}

// RigMidi
void Rig::midiTempoReceived(unsigned short rawVal)
{
  emit tempoReceived(raw2Phys(rawVal, 236.0, 20.0));
}

void Rig::midiVolumeReceived(unsigned short rawVal)
{
  emit volumeReceived((int)rawVal);
}

void Rig::midiTempoEnableReceived(unsigned short rawVal)
{
  emit tempoEnableReceived(raw2Bool(rawVal));
}

void Rig::midiStompsEnableReceived(unsigned short rawVal)
{
  emit stompsEnableReceived(raw2Bool(rawVal));
}

void Rig::midiStackEnableReceived(unsigned short rawVal)
{
  emit stackEnableReceived(raw2Bool(rawVal));
}

void Rig::midiEffectsEnableReceived(unsigned short rawVal)
{
  emit effectsEnableReceived(raw2Bool(rawVal));
}

