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
#include "Reverb.h"

Reverb::Reverb()
{
}

Reverb::~Reverb()
{
}

Reverb& Reverb::get()
{
  static Reverb reverb;
  return reverb;
}

void Reverb::requestAllValues()
{
  midiRequestType();
  midiRequestOnOffCutsTail();
  midiRequestMix();
  midiRequestVolume();
  midiRequestDelRevBalance();
  midiRequestTime();
  midiRequestDamping();
  midiRequestBandwidth();
  midiRequestCenterFrequency();
  midiRequestPreDelay();
  midiRequestOnOffKeepsTail();
  midiRequestDucking();
}

// slots
void Reverb::applyType(::ReverbType type)
{
  midiApplyType((unsigned short) type);
  midiRequestType();
}

void Reverb::applyOnOffCutsTail(bool onOff)
{
  midiApplyOnOffCutsTail(bool2Raw(onOff));
  midiRequestOnOffCutsTail();
}

void Reverb::applyMix(int mix)
{
  midiApplyMix((unsigned short)mix);
}

void Reverb::applyVolume(double volume)
{
  midiApplyVolume(phys2Raw(volume, 10.0, -5.0));
}

void Reverb::applyDelRevBalance(double balance)
{
  midiApplyDelRevBalance(phys2Raw(balance, 200.0, -100.0));
}

void Reverb::applyTime(double time)
{
  midiApplyTime(phys2Raw(time, 10.0, 0.0));
}

void Reverb::applyDamping(double damping)
{
  midiApplyDamping(phys2Raw(damping, 10.0, 0.0));
}

void Reverb::applyBandwidth(double bandwidth)
{
  midiApplyBandwidth(phys2Raw(bandwidth, 10.0, 0.0));
}

void Reverb::applyCenterFrequency(double frequency)
{
  midiApplyCenterFrequency(phys2Raw(frequency, 10.0, -5));
}

void Reverb::applyPreDelay(double preDelay)
{
  midiApplyPreDelay(phys2Raw(preDelay, 320.0, 0.0));
}

void Reverb::applyOnOffKeepsTail(bool onOff)
{
  midiApplyOnOffKeepsTail(bool2Raw(onOff));
}

void Reverb::applyDucking(double ducking)
{
  midiApplyDucking(phys2Raw(ducking, 10.0, -5.0));
}

// ReverbMidi
void Reverb::midiTypeReceived(unsigned short rawVal)
{
  mReverbType = (::ReverbType) rawVal;
  emit typeReceived(mReverbType);
}

void Reverb::midiOnOffCutsTailReceived(unsigned short rawVal)
{
  emit onOffCutsTailReceived(raw2Bool(rawVal));
}

void Reverb::midiMixReceived(unsigned short rawVal)
{
  emit mixReceived((int)rawVal);
}

void Reverb::midiVolumeReceived(unsigned short rawVal)
{
  emit volumeReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Reverb::midiDelRevBalanceReceived(unsigned short rawVal)
{
  emit delRevBalanceReceived(raw2Phys(rawVal, 200.0, -100.0));
}

void Reverb::midiTimeReceived(unsigned short rawVal)
{
  emit timeReceived(raw2Phys(rawVal, 10.0, 0.0));
}

void Reverb::midiDampingReceived(unsigned short rawVal)
{
  emit dampingReceived(raw2Phys(rawVal, 10.0, 0.0));
}

void Reverb::midiBandwidthReceived(unsigned short rawVal)
{
  emit bandwidthReceived(raw2Phys(rawVal, 10.0, 0.0));
}

void Reverb::midiCenterFrequencyReceived(unsigned short rawVal)
{
  emit centerFrequencyReceived(raw2Phys(rawVal, 10.0, -5));
}

void Reverb::midiPreDelayReceived(unsigned short rawVal)
{
  emit preDelayReceived(raw2Phys(rawVal, 320.0, 0.0));
}

void Reverb::midiOnOffKeepsTailReceived(unsigned short rawVal)
{
  emit onOffKeepsTailReceived(raw2Bool(rawVal));
}

void Reverb::midiDuckingReceived(unsigned short rawVal)
{
  emit duckingReceived(raw2Phys(rawVal, 10.0, -5.0));
}
