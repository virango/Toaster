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


