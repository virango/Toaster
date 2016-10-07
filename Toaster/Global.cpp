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
#include <QTimer>
#include "Global.h"

Global::Global()
  : mBeaconTimer(nullptr)
{
}

Global::~Global()
{

}

Global& Global::get()
{
  static Global global;
  return global;
}

void Global::requestAllValues()
{
  midiRequestOperationMode();
  midiRequestMonitorOutputVolume();
  midiRequestHeadphoneOutputVolume();
}

// slots
void Global::applyMainOutputVolume(int volume)
{
  midiApplyMainOutputVolume((unsigned short)volume);
}

void Global::applyHeadphoneOutputVolume(int volume)
{
  midiApplyHeadphoneOutputVolume((unsigned short)volume);
}

void Global::applyMonitorOutputVolume(int volume)
{
  midiApplyMonitorOutputVolume((unsigned short)volume);
}

void Global::applyDirectOutputVolume(int volume)
{
  midiApplyDirectOutputVolume((unsigned short)volume);
}

void Global::applySPDIFOutputVolume(int volume)
{
  midiApplySPDIFOutputVolume((unsigned short)volume);
}

void Global::applyMasterTune(double masterTune)
{
  midiApplyMasterTune(Utils::phys2Raw(masterTune+0.1, 32, 424));
}

void Global::applyMonitorCabOff(bool monitorCabOff)
{
  midiApplyMonitorCabOff(Utils::bool2Raw(monitorCabOff));
}

void Global::applySPDIFInputEnable(bool enabled)
{
  midiApplySPDIFInputEnable(Utils::bool2Raw(enabled));
}

void Global::applyMainOutputEQBass(double bass)
{
  midiApplyMainOutputEQBass(Utils::phys2Raw(bass, 10.0, -5.0));
}

void Global::applyMainOutputEQMiddle(double middle)
{
  midiApplyMainOutputEQMiddle(Utils::phys2Raw(middle, 10.0, -5.0));
}

void Global::applyMainOutputEQTreble(double treble)
{
  midiApplyMainOutputEQTreble(Utils::phys2Raw(treble, 10.0, -5.0));
}

void Global::applyMainOutputEQPresence(double presence)
{
  midiApplyMainOutputEQPresence(Utils::phys2Raw(presence, 10.0, -5.0));
}

void Global::applyMonitorOutputEQBass(double bass)
{
  midiApplyMonitorOutputEQBass(Utils::phys2Raw(bass, 10.0, -5.0));
}

void Global::applyMonitorOutputEQMiddle(double middle)
{
  midiApplyMonitorOutputEQMiddle(Utils::phys2Raw(middle, 10.0, -5.0));
}

void Global::applyMonitorOutputEQTreble(double treble)
{
  midiApplyMonitorOutputEQTreble(Utils::phys2Raw(treble, 10.0, -5.0));
}

void Global::applyMonitorOutputEQPresence(double presence)
{
  midiApplyMonitorOutputEQPresence(Utils::phys2Raw(presence, 10.0, -5.0));
}

void Global::applyMainOutputSource(int source)
{
  midiApplyMonitorOutputSource(source);
}

void Global::applySPDIFOutputSource(int source)
{
  midiApplySPDIFOutputSource(Utils::spdifSource2Raw(source));
}

void Global::applyMonitorOutputSource(int source)
{
  midiApplyMonitorOutputSource(source);
}

void Global::applyDirectOutputSource(int source)
{
  midiApplyDirectOutputSource(source);
}

void Global::applyAuxInToMain(double value)
{
  midiApplyAuxInToMain(Utils::phys2Raw(value, 10.0, 0));
}

void Global::applyAuxInToHeadphone(double value)
{
  midiApplyAuxInToHeadphone(Utils::phys2Raw(value, 10.0, 0));
}

void Global::applyConstantLatencyOnOff(bool onOff)
{
  midiApplyConstantLatencyOnOff(Utils::bool2Raw(onOff));
}

void Global::applySpace(double value)
{
  midiApplySpace(Utils::phys2Raw(value, 10.0, 0));
}

void Global::applyHeadphoneSpaceOnOff(bool onOff)
{
  midiApplyHeadphoneSpaceOnOff(Utils::bool2Raw(onOff));
}

void Global::applyWahPedalToPitch(bool onOff)
{
  midiApplyWahPedalToPitch(Utils::bool2Raw(onOff));
}

void Global::applyInputSource(int inputSource)
{
  midiApplyInputSource((unsigned short)inputSource);
}

void Global::applyReampSense(double reampSens)
{
  midiApplyReampSense(Utils::phys2Raw(reampSens, 24.0, -12.0));
}

void Global::applyPureCabOnOff(bool onOff)
{
  midiApplyPureCabOnOff(Utils::bool2Raw(onOff));
}

void Global::applyPureCab(double value)
{
  midiApplyPureCab(Utils::phys2Raw(value, 10.0, 0));
}

void Global::applyOperationMode(Global::OperationMode opMode)
{
  midiApplyOperationMode((unsigned short) opMode);
}

void Global::connect2KPA(const QString& connectName)
{
  if(mBeaconTimer == nullptr)
    mBeaconTimer = new QTimer(this);

  midiApplyConnectName(connectName);
  launchBeacon();
}

void Global::disconnectFromKPA()
{
  if(mBeaconTimer)
    mBeaconTimer->stop();
}

void Global::launchBeacon()
{
  sendBeacon();
  if(mBeaconTimer)
  {
    mBeaconTimer->setSingleShot(false);
    connect(mBeaconTimer, SIGNAL(timeout()), this, SLOT(sendBeacon()) );
    mBeaconTimer->start(5000);
  }
}

void Global::sendBeacon()
{
  midiSendBeacon();
}

// GlobalMidi
void Global::midiMainOutputVolumeReceived(unsigned short rawVal)
{
  emit mainOutputVolumeReceived((int)rawVal);
}

void Global::midiHeadphoneOutputVolumeReceived(unsigned short rawVal)
{
  emit headphoneOutputVolumeReceived((int)rawVal);
}

void Global::midiMonitorOutputVolumeReceived(unsigned short rawVal)
{
  emit monitorOutputVolumeReceived((int)rawVal);
}

void Global::midiDirectOutputVolumeReceived(unsigned short rawVal)
{
  emit directOutputVolumeReceived((int)rawVal);
}

void Global::midiSPDIFOutputVolumeReceived(unsigned short rawVal)
{
  emit spdifOutputVolumeReceived((int)rawVal);
}

void Global::midiMasterTuneReceived(unsigned short rawVal)
{
  long tmp = ((long)((Utils::raw2Phys(rawVal, 32, 424)) * 10));
  double newVal = tmp / 10.0;
  emit masterTuneReceived(newVal);
}

void Global::midiMonitorCabOffReceived(unsigned short rawVal)
{
  emit monitorCabOffReceived(Utils::raw2Bool(rawVal));
}

void Global::midiSPDIFInputEnableReceived(unsigned short rawVal)
{
  emit spdifInputEnableReceived(Utils::raw2Bool(rawVal));
}

void Global::midiMainOutputEQBassReceived(unsigned short rawVal)
{
  emit mainOutputEQBassReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMainOutputEQMiddleReceived(unsigned short rawVal)
{
  emit mainOutputEQMiddleReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMainOutputEQTrebleReceived(unsigned short rawVal)
{
  emit mainOutputEQTrebleReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMainOutputEQPresenceReceived(unsigned short rawVal)
{
  emit mainOutputEQPresenceReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMonitorOutputEQBassReceived(unsigned short rawVal)
{
  emit monitorOutputEQBassReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMonitorOutputEQMiddleReceived(unsigned short rawVal)
{
  emit monitorOutputEQMiddleReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMonitorOutputEQTrebleReceived(unsigned short rawVal)
{
  emit monitorOutputEQTrebleReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMonitorOutputEQPresenceReceived(unsigned short rawVal)
{
  emit monitorOutputEQPresenceReceived(Utils::raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMainOutputSourceReceived(unsigned short rawVal)
{
  emit mainOutputSourceReceived(rawVal);
}

void Global::midiSPDIFOutputSourceReceived(unsigned short rawVal)
{
  emit spdifOutputSourceReceived(Utils::raw2SPDIFSource(rawVal));
}

void Global::midiMonitorOutputSourceReceived(unsigned short rawVal)
{
  emit monitorOutputSourceReceived(rawVal);
}

void Global::midiDirectOutputSourceReceived(unsigned short rawVal)
{
  emit directOutputSourceReceived(rawVal);
}

void Global::midiAuxInToMainReceived(unsigned short rawVal)
{
  emit auxInToMainReceived(Utils::raw2Phys(rawVal, 10.0, 0));
}

void Global::midiAuxInToHeadphoneReceived(unsigned short rawVal)
{
  emit auxInToHeadphoneReceived(Utils::raw2Phys(rawVal, 10.0, 0));
}

void Global::midiConstantLatencyOnOffReceived(unsigned short rawVal)
{
  emit constantLatencyOnOffReceived(Utils::raw2Bool(rawVal));
}

void Global::midiSpaceReceived(unsigned short rawVal)
{
  emit spaceReceived(Utils::raw2Phys(rawVal, 10.0, 0));
}

void Global::midiHeadphoneSpaceOnOffReceived(unsigned short rawVal)
{
  emit headphoneSpaceOnOffReceived(Utils::raw2Bool(rawVal));
}

void Global::midiWahPedalToPitchReceived(unsigned short rawVal)
{
  emit wahPedalToPitchReceived(Utils::raw2Bool(rawVal));
}

void Global::midiInputSourceReceived(unsigned short rawVal)
{
  emit inputSourceReceived(rawVal);
}

void Global::midiReampSensReceived(unsigned short rawVal)
{
  emit reampSensReceived(Utils::raw2Phys(rawVal, 24.0, -12));
}

void Global::midiPureCabOnOffReceived(unsigned short rawVal)
{
  emit pureCabOnOffReceived(Utils::raw2Bool(rawVal));
}

void Global::midiPureCabReceived(unsigned short rawVal)
{
  emit pureCabReceived(Utils::raw2Phys(rawVal, 10.0, 0));
}

void Global::midiOperationModeReceived(unsigned short rawVal)
{
  emit operationModeReceived(rawVal);
}
