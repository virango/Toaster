#include "Delay.h"

Delay::Delay()
{
}

Delay::~Delay()
{
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
void Delay::applyType(DelayType type)
{
  midiApplyType((unsigned short) type);
}

void Delay::applyOnOffCutsTail(bool onOffCutsTail)
{
  midiApplyOnOffCutsTail(bool2Raw(onOffCutsTail));
}

void Delay::applyMix(double mix)
{
  midiApplyMix(phys2Raw(mix, , ));
}

void Delay::applyVolume(double volume)
{
  midiApplyVolume(phys2Raw(volume, , ));
}

void Delay::applyTime(double time)
{
  midiApplyTime(phys2Raw(time, , ));
}

void Delay::applyRatio(double ratio)
{
  midiApplyRatio(phys2Raw(ratio, , ));
}

void Delay::applyClockLeft(double clockLeft)
{
  midiApplyClockLeft(phys2Raw(clockLeft, , ));
}

void Delay::applyClockRight(double clockRight)
{
  midiApplyClockRight(phys2Raw(clockRight, , ));
}

void Delay::applyFeedback(double feedback)
{
  midiApplyFeedback(phys2Raw(feedback, , ));
}

void Delay::applyBandwidth(double bandwidth)
{
  midiApplyBandwidth(phys2Raw(bandwidth, , ));
}

void Delay::applyCenterFrequency(double centerFrequency)
{
  midiApplyCenterFrequency(phys2Raw(centerFrequency, , ));
}

void Delay::applyModulation(double modulation)
{
  midiApplyModulation(phys2Raw(modulation, , ));
}

void Delay::applyOnOffKeepsTail(bool onOffKeepsTail)
{
  midiApplyOnOffKeepsTail(bool2Raw(onOffKeepsTail));
}

void Delay::applyDucking(double ducking)
{
  midiApplyDucking(phys2Raw(ducking, , ));
}

// DelayMidi
void Delay::midiTypeReceived(unsigned short rawVal)
{
  emit typeReceived((DelayType) rawVal);
}

void Delay::midiOnOffCutsTailReceived(unsigned short rawVal)
{
  emit onOffCutsTailReceived(raw2bool(rawVal));
}

void Delay::midiMixReceived(unsigned short rawVal)
{
  emit mixReceived(raw2Phys(rawVal, ,));
}

void Delay::midiVolumeReceived(unsigned short rawVal)
{
  emit volumeReceived(raw2Phys(rawVal, ,));
}

void Delay::midiTimeReceived(unsigned short rawVal)
{
  emit timeReceived(raw2Phys(rawVal, ,));
}

void Delay::midiRatioReceived(unsigned short rawVal)
{
  emit ratioReceived(raw2Phys(rawVal, ,));
}

void Delay::midiClockLeftReceived(unsigned short rawVal)
{
  emit clockLeftReceived(raw2Phys(rawVal, ,));
}

void Delay::midiClockRightReceived(unsigned short rawVal)
{
  emit clockRightReceived(raw2Phys(rawVal, ,));
}

void Delay::midiFeedbackReceived(unsigned short rawVal)
{
  emit feedbackReceived(raw2Phys(rawVal, ,));
}

void Delay::midiBandwidthReceived(unsigned short rawVal)
{
  emit bandwidthReceived(raw2Phys(rawVal, ,));
}

void Delay::midiCenterFrequencyReceived(unsigned short rawVal)
{
  emit centerFrequencyReceived(raw2Phys(rawVal, ,));
}

void Delay::midiModulationReceived(unsigned short rawVal)
{
  emit modulationReceived(raw2Phys(rawVal, ,));
}

void Delay::midiOnOffKeepsTailReceived(unsigned short rawVal)
{
  emit onOffKeepsTailReceived(raw2bool(rawVal)));
}

void Delay::midiDuckingReceived(unsigned short rawVal)
{
  emit duckingReceived(raw2Phys(rawVal, ,));
}