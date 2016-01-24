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
  midiRequestDefinition();
  midiRequestClarity();
  midiRequestPowerSagging();
  midiRequestPick();
  midiRequestCompressor();
  midiRequestTubeShape();
  midiRequestTubeBias();
  midiRequestDirectMix();
}

// slots
void Amp::applyOnOff(bool onOff)
{
  midiApplyOnOff(bool2Raw(onOff));
}

void Amp::applyGain(double gain)
{
  midiApplyGain(phys2Raw(gain, 10.0, 0.0));
}

void Amp::applyDefinition(double definition)
{
  midiApplyDefinition(phys2Raw(definition, 10.0, 0.0));
}

void Amp::applyClarity(double clarity)
{
  midiApplyClarity(phys2Raw(clarity, 10.0, 0.0));
}

void Amp::applyPowerSagging(double powerSagging)
{
  midiApplyPowerSagging(phys2Raw(powerSagging, 10.0, 0.0));
}

void Amp::applyPick(double pick)
{
  midiApplyPick(phys2Raw(pick, 10.0, -5.0));
}

void Amp::applyCompressor(double compressor)
{
  midiApplyCompressor(phys2Raw(compressor, 10.0, 0.0));
}

void Amp::applyTubeShape(double tubeShape)
{
  midiApplyTubeShape(phys2Raw(tubeShape, 10.0, 0.0));
}

void Amp::applyTubeBias(double tubeBias)
{
  midiApplyTubeBias(phys2Raw(tubeBias, 10.0, 0.0));
}

void Amp::applyDirectMix(double directMix)
{
  midiApplyDirectMix(phys2Raw(directMix, 10.0, 0.0));
}

// AmpMidi callbacks
void Amp::midiOnOffReceived(unsigned short rawVal)
{
  emit onOffReceived(raw2Bool(rawVal));
}

void Amp::midiGainReceived(unsigned short rawVal)
{
  emit gainReceived(raw2Phys(rawVal, 10.0, 0.0));
}

void Amp::midiDefinitionReceived(unsigned short rawVal)
{
  emit definitionReceived(raw2Phys(rawVal, 10.0, 0.0));
}

void Amp::midiClarityReceived(unsigned short rawVal)
{
  emit clarityReceived(raw2Phys(rawVal, 10.0, 0.0));
}

void Amp::midiPowerSaggingReceived(unsigned short rawVal)
{
  emit powerSaggingReceived(raw2Phys(rawVal, 10.0, 0.0));
}

void Amp::midiPickReceived(unsigned short rawVal)
{
  emit pickReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Amp::midiCompressorReceived(unsigned short rawVal)
{
  emit compressorReceived(raw2Phys(rawVal, 10.0, 0.0));
}

void Amp::midiTubeShapeReceived(unsigned short rawVal)
{
  emit tubeShapeReceived(raw2Phys(rawVal, 10.0, 0.0));
}

void Amp::midiTubeBiasReceived(unsigned short rawVal)
{
  emit tubeBiasReceived(raw2Phys(rawVal, 10.0, 0.0));
}

void Amp::midiDirectMixReceived(unsigned short rawVal)
{
  emit directMixReceived(phys2Raw(rawVal, 10.0, 0.0));
}

