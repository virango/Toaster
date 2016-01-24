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
#ifndef GLOBALMIDI_H
#define GLOBALMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class GlobalMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(MainOutputVolume)
  BYTEARRAYDECL(HeadphoneOutputVolume)
  BYTEARRAYDECL(MonitorOutputVolume)
  BYTEARRAYDECL(DirectOutputVolume)
  BYTEARRAYDECL(MasterTune)
  BYTEARRAYDECL(SPDIFInputEnable)
  BYTEARRAYDECL(MainOutputEQBass)
  BYTEARRAYDECL(MainOutputEQMiddle)
  BYTEARRAYDECL(MainOutputEQTreble)
  BYTEARRAYDECL(MainOutputEQPresence)
  BYTEARRAYDECL(MonitorOutputEQBass)
  BYTEARRAYDECL(MonitorOutputEQMiddle)
  BYTEARRAYDECL(MonitorOutputEQTreble)
  BYTEARRAYDECL(MonitorOutputEQPresence)
  BYTEARRAYDECL(WahPedalToPitch)
  BYTEARRAYDECL(OperationMode)
  BYTEARRAYDECL(ConnectName)

public:
  GlobalMidi();
  ~GlobalMidi();

  // ISysExConsumer
  unsigned char getId();
  void consumeSysExMsg(ByteArray* msg);

protected:
  // parameter
  // MainOutputVolume
  void midiRequestMainOutputVolume();
  void midiApplyMainOutputVolume(unsigned short rawVal);
  // HeadphoneOutputVolume
  void midiRequestHeadphoneOutputVolume();
  void midiApplyHeadphoneOutputVolume(unsigned short rawVal);
  // MonitorOutputVolume
  void midiRequestMonitorOutputVolume();
  void midiApplyMonitorOutputVolume(unsigned short rawVal);
  // DirectOutputVolume
  void midiRequestDirectOutputVolume();
  void midiApplyDirectOutputVolume(unsigned short rawVal);
  // MasterTune
  void midiRequestMasterTune();
  void midiApplyMasterTune(unsigned short rawVal);
  // SPDIFInputEnable
  void midiRequestSPDIFInputEnable();
  void midiApplySPDIFInputEnable(unsigned short rawVal);
  // MainOutputEQBass
  void midiRequestMainOutputEQBass();
  void midiApplyMainOutputEQBass(unsigned short rawVal);
  // MainOutputEQMiddle
  void midiRequestMainOutputEQMiddle();
  void midiApplyMainOutputEQMiddle(unsigned short rawVal);
  //MainOutputEQTreble
  void midiRequestMainOutputEQTreble();
  void midiApplyMainOutputEQTreble(unsigned short rawVal);
  // MainOutputEQPresence
  void midiRequestMainOutputEQPresence();
  void midiApplyMainOutputEQPresence(unsigned short rawVal);
  // MonitorOutputEQBass
  void midiRequestMonitorOutputEQBass();
  void midiApplyMonitorOutputEQBass(unsigned short rawVal);
  // MonitorOutputEQMiddle
  void midiRequestMonitorOutputEQMiddle();
  void midiApplyMonitorOutputEQMiddle(unsigned short rawVal);
  // MonitorOutputEQTreble
  void midiRequestMonitorOutputEQTreble();
  void midiApplyMonitorOutputEQTreble(unsigned short rawVal);
  // MonitorOutputEQPresence
  void midiRequestMonitorOutputEQPresence();
  void midiApplyMonitorOutputEQPresence(unsigned short rawVal);
  // WahPedalToPitch
  void midiRequestWahPedalToPitch();
  void midiApplyWahPedalToPitch(unsigned short rawVal);
  // OperationMode
  void midiRequestOperationMode();
  void midiApplyOperationMode(unsigned short rawVal);
  // ConnectName
  void midiApplyConnectName(const QString& connectName);

  void midiSendBeacon();

  // receive callbacks for derived class
  virtual void midiMainOutputVolumeReceived(unsigned short rawVal) = 0;
  virtual void midiHeadphoneOutputVolumeReceived(unsigned short rawVal) = 0;
  virtual void midiMonitorOutputVolumeReceived(unsigned short rawVal) = 0;
  virtual void midiDirectOutputVolumeReceived(unsigned short rawVal) = 0;
  virtual void midiMasterTuneReceived(unsigned short rawVal) = 0;
  virtual void midiSPDIFInputEnableReceived(unsigned short rawVal) = 0;
  virtual void midiMainOutputEQBassReceived(unsigned short rawVal) = 0;
  virtual void midiMainOutputEQMiddleReceived(unsigned short rawVal) = 0;
  virtual void midiMainOutputEQTrebleReceived(unsigned short rawVal) = 0;
  virtual void midiMainOutputEQPresenceReceived(unsigned short rawVal) = 0;
  virtual void midiMonitorOutputEQBassReceived(unsigned short rawVal) = 0;
  virtual void midiMonitorOutputEQMiddleReceived(unsigned short rawVal) = 0;
  virtual void midiMonitorOutputEQTrebleReceived(unsigned short rawVal) = 0;
  virtual void midiMonitorOutputEQPresenceReceived(unsigned short rawVal) = 0;
  virtual void midiWahPedalToPitchReceived(unsigned short rawVal) = 0;
  virtual void midiOperationModeReceived(unsigned short rawVal) = 0;

  ByteArray getAddressPage();
};

#endif // GLOBALMIDI_H
