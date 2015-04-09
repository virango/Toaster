#include "Rig.h"

Rig::Rig()
{
}

Rig::~Rig()
{
}

void Rig::requestAllValues()
{
  midiRequestTempo();
  midiRequestVolume();
  midiRequestTempoEnable();
}

// slots
void Rig::applyTempo(double tempo)
{
  midiApplyTempo(phys2Raw(tempo, 236.0, 20.0));
}

void Rig::applyVolume(double volume)
{
  midiApplyVolume(phys2Raw(volume, 108.0, -96.0));
}

void Rig::applyTempoEnable(bool tempoEnable)
{
  midiApplyTempoEnable(raw2Bool(tempoEnable));
}

// RigMidi
void Rig::midiTempoReceived(unsigned short rawVal)
{
  emit tempoReceived(raw2Phys(rawVal, 236.0, 20.0));
}

void Rig::midiVolumeReceived(unsigned short rawVal)
{
  emit volumeReceived(raw2Phys(rawVal, 108.0, -96.0));
}

void Rig::midiTempoEnableReceived(unsigned short rawVal)
{
  emit tempoEnableReceived(raw2Bool(rawVal));
}
