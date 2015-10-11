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
  midiRequestStompsEnable();
  midiRequestStackEnable();
  midiRequestEffectsEnable();
}

// slots
void Rig::applyTempo(double tempo)
{
  midiApplyTempo(phys2Raw(tempo, 236.0, 20.0));
}

void Rig::applyVolume(double volume)
{
  midiApplyVolume(volume2Raw(volume));
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
  emit volumeReceived(raw2Volume(rawVal, 108.0, -96.0));
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

