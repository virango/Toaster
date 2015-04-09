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
  unsigned short rawVal = (noiseGate * 0x8000) / 10;
  midiApplyNoiseGate(rawVal);
}

void Input::applyCleanSense(double cleanSense)
{
  unsigned short rawVal = ((cleanSense + 12.0) * 0x8000) / 24;
  midiApplyCleanSense(rawVal);
}

void Input::applyDistortionSense(double cleanSense)
{
  unsigned short rawVal = ((cleanSense + 12.0) * 0x8000) / 24;
  midiApplyDistortionSense(rawVal);
}

// InputMidi callbacks
void Input::midiNoiseGateReceived(unsigned short rawVal)
{
  double physVal = (rawVal * 10.0) / 0x8000;
  emit noiseGateReceived(physVal);
}

void Input::midiCleanSenseReceived(unsigned short rawVal)
{
  double physVal = (rawVal * 24.0) / 0x8000;
  emit cleanSenseReceived(physVal);
}

void Input::midiDistortionSenseReceived(unsigned short rawVal)
{
  double physVal = (rawVal * 24.0) / 0x8000;
  emit distortionSenseReceived(physVal);
}


