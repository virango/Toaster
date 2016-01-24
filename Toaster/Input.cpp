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
#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

void Input::requestAllValues()
{
  midiRequestNoiseGate();
  midiRequestCleanSense();
  midiRequestDistortionSense();
}

// slots
void Input::applyNoiseGate(double noiseGate)
{
  midiApplyNoiseGate(phys2Raw(noiseGate, 10, 0));
}

void Input::applyCleanSense(double cleanSense)
{
  midiApplyCleanSense(phys2Raw(cleanSense, 24, -12));
}

void Input::applyDistortionSense(double distortionSense)
{
  midiApplyDistortionSense(phys2Raw(distortionSense, 24, -12));
}

// InputMidi callbacks
void Input::midiNoiseGateReceived(unsigned short rawVal)
{
  emit noiseGateReceived(raw2Phys(rawVal, 10, 0));
}

void Input::midiCleanSenseReceived(unsigned short rawVal)
{
  emit cleanSenseReceived(raw2Phys(rawVal, 24, -12));
}

void Input::midiDistortionSenseReceived(unsigned short rawVal)
{
  emit distortionSenseReceived(raw2Phys(rawVal, 24, -12));
}


