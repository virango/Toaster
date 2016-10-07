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
#include "Delay.h"

Delay::Delay()
  : mDelayType(TapDelay)
{
}

Delay::~Delay()
{
}

Delay& Delay::get()
{
  static Delay delay;
  return delay;
}

void Delay::requestAllValues()
{
  midiRequestType();
  midiRequestOnOffCutsTail();
  midiRequestMix();
  midiRequestVolume();
  midiRequestTime();
  midiRequestRatio();
  midiRequestClockLeft();
  midiRequestClockRight();
  midiRequestFeedback();
  midiRequestBandwidth();
  midiRequestCenterFrequency();
  midiRequestModulation();
  midiRequestOnOffKeepsTail();
  midiRequestDucking();
}

// slots
void Delay::applyType(::DelayType type)
{
  midiApplyType((unsigned short) type);
  midiRequestType();
}

void Delay::applyOnOffCutsTail(bool onOffCutsTail)
{
  midiApplyOnOffCutsTail(Utils::bool2Raw(onOffCutsTail));
  midiRequestOnOffCutsTail();
}

void Delay::applyMix(int mix)
{
  midiApplyMix((unsigned short)mix);
}

void Delay::applyVolume(double volume)
{
  midiApplyVolume(Utils::phys2Raw(volume, 10.0, -5.0));
}

void Delay::applyTime(double time)
{
  midiApplyTime(Utils::phys2Raw(time, 1280, 0.0));
}

void Delay::applyRatio(::DelayRatio ratio)
{
  midiApplyRatio((unsigned short)ratio);
}

void Delay::applyClockLeft(::DelayClock clockLeft)
{
  midiApplyClockLeft((unsigned short)clockLeft);
}

void Delay::applyClockRight(::DelayClock clockRight)
{
  midiApplyClockRight((unsigned short)clockRight);
}

void Delay::applyFeedback(double feedback)
{
  midiApplyFeedback(Utils::phys2Raw(feedback, 200.0, 0.0));
}

void Delay::applyBandwidth(double bandwidth)
{
  midiApplyBandwidth(Utils::phys2Raw(bandwidth, 10.0, 0.0));
}

void Delay::applyCenterFrequency(double centerFrequency)
{
  midiApplyCenterFrequency(Utils::phys2Raw(centerFrequency, 10.0, -5));
}

void Delay::applyModulation(double modulation)
{
  midiApplyModulation(Utils::phys2Raw(modulation, 10.0, 0.0));
}

void Delay::applyOnOffKeepsTail(bool onOffKeepsTail)
{
  midiApplyOnOffKeepsTail(Utils::bool2Raw(onOffKeepsTail));
}

void Delay::applyDucking(double ducking)
{
  midiApplyDucking(Utils::phys2Raw(ducking, 10.0, -5.0));
}

// DelayMidi
void Delay::midiTypeReceived(unsigned short rawVal)
{
  mDelayType = (DelayType) rawVal;
  emit typeReceived(mDelayType);
}

void Delay::midiOnOffCutsTailReceived(unsigned short rawVal)
{
  emit onOffCutsTailReceived(Utils::raw2Bool(rawVal));
}

void Delay::midiMixReceived(unsigned short rawVal)
{
  emit mixReceived((int)rawVal);
}

void Delay::midiVolumeReceived(unsigned short rawVal)
{
  emit volumeReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}

void Delay::midiTimeReceived(unsigned short rawVal)
{
  emit timeReceived(Utils::raw2Phys(rawVal, 1280.0, 0.0));
}

void Delay::midiRatioReceived(unsigned short rawVal)
{
  emit ratioReceived((::DelayRatio)rawVal);
}

void Delay::midiClockLeftReceived(unsigned short rawVal)
{
  emit clockLeftReceived((::DelayClock)rawVal);
}

void Delay::midiClockRightReceived(unsigned short rawVal)
{
  emit clockRightReceived((::DelayClock)rawVal);
}

void Delay::midiFeedbackReceived(unsigned short rawVal)
{
  emit feedbackReceived(Utils::raw2Phys(rawVal, 200.0, 0.0));
}

void Delay::midiBandwidthReceived(unsigned short rawVal)
{
  emit bandwidthReceived(Utils::raw2Phys(rawVal, 10.0, 0.0));
}

void Delay::midiCenterFrequencyReceived(unsigned short rawVal)
{
  emit centerFrequencyReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}

void Delay::midiModulationReceived(unsigned short rawVal)
{
  emit modulationReceived(Utils::raw2Phys(rawVal, 10.0, 0.0));
}

void Delay::midiOnOffKeepsTailReceived(unsigned short rawVal)
{
  emit onOffKeepsTailReceived(Utils::raw2Bool(rawVal));
}

void Delay::midiDuckingReceived(unsigned short rawVal)
{
  emit duckingReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}
