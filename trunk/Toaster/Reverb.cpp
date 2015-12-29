#include "Reverb.h"

Reverb::Reverb()
{

}

Reverb::~Reverb()
{

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
