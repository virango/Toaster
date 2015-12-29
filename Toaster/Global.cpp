#include <QTimer>
#include "Global.h"

Global::Global()
  : mBeaconTimer(nullptr)
{
}

Global::~Global()
{

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

void Global::applySpdifInputEnable(bool enabled)
{
  midiApplySPDIFInputEnable(bool2Raw(enabled));
}

void Global::applyMainOutputEQBass(double bass)
{
  midiApplyMainOutputEQBass(phys2Raw(bass, 10.0, -5.0));
}

void Global::applyMainOutputEQMiddle(double middle)
{
  midiApplyMainOutputEQMiddle(phys2Raw(middle, 10.0, -5.0));
}

void Global::applyMainOutputEQTreble(double treble)
{
  midiApplyMainOutputEQTreble(phys2Raw(treble, 10.0, -5.0));
}

void Global::applyMainOutputEQPresence(double presence)
{
  midiApplyMainOutputEQPresence(phys2Raw(presence, 10.0, -5.0));
}

void Global::applyMonitorOutputEQBass(double bass)
{
  midiApplyMonitorOutputEQBass(phys2Raw(bass, 10.0, -5.0));
}

void Global::applyMonitorOutputEQMiddle(double middle)
{
  midiApplyMonitorOutputEQBass(phys2Raw(middle, 10.0, -5.0));
}

void Global::applyMonitorOutputEQTreble(double treble)
{
  midiApplyMonitorOutputEQTreble(phys2Raw(treble, 10.0, -5.0));
}

void Global::applyMonitorOutputEQPresence(double presence)
{
  midiApplyMonitorOutputEQPresence(phys2Raw(presence, 10.0, -5.0));
}

void Global::applyWahPedalToPitchReceived(bool onOff)
{
  midiApplyWahPedalToPitch(bool2Raw(onOff));
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

void Global::midiSPDIFInputEnableReceived(unsigned short rawVal)
{
  emit spdifInputEnableReceived(raw2Bool(rawVal));
}

void Global::midiMainOutputEQBassReceived(unsigned short rawVal)
{
  emit mainOutputEQBassReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMainOutputEQMiddleReceived(unsigned short rawVal)
{
  emit mainOutputEQMiddleReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMainOutputEQTrebleReceived(unsigned short rawVal)
{
  emit mainOutputEQTrebleReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMainOutputEQPresenceReceived(unsigned short rawVal)
{
  emit mainOutputEQPresenceReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMonitorOutputEQBassReceived(unsigned short rawVal)
{
  emit monitorOutputEQBassReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMonitorOutputEQMiddleReceived(unsigned short rawVal)
{
  emit monitorOutputEQMiddleReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMonitorOutputEQTrebleReceived(unsigned short rawVal)
{
  emit monitorOutputEQTrebleReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiMonitorOutputEQPresenceReceived(unsigned short rawVal)
{
  emit monitorOutputEQPresenceReceived(raw2Phys(rawVal, 10.0, -5.0));
}

void Global::midiWahPedalToPitchReceived(unsigned short rawVal)
{
  emit wahPedalToPitchReceived(raw2Bool(rawVal));
}

void Global::midiOperationModeReceived(unsigned short rawVal)
{
  emit operationModeReceived(rawVal);
}
