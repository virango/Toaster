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
  BYTEARRAYDECL(SPDIFOutputVolume)
  BYTEARRAYDECL(MasterTune)
  BYTEARRAYDECL(MonitorCabOff)
  BYTEARRAYDECL(SPDIFInputEnable)
  BYTEARRAYDECL(MainOutputEQBass)
  BYTEARRAYDECL(MainOutputEQMiddle)
  BYTEARRAYDECL(MainOutputEQTreble)
  BYTEARRAYDECL(MainOutputEQPresence)
  BYTEARRAYDECL(MonitorOutputEQBass)
  BYTEARRAYDECL(MonitorOutputEQMiddle)
  BYTEARRAYDECL(MonitorOutputEQTreble)
  BYTEARRAYDECL(MonitorOutputEQPresence)
  BYTEARRAYDECL(MainOutputSource)
  BYTEARRAYDECL(SPDIFOutputSource)
  BYTEARRAYDECL(MonitorOutputSource)
  BYTEARRAYDECL(DirectOutputSource)
  BYTEARRAYDECL(AuxInToMain)
  BYTEARRAYDECL(AuxInToHeadphone)
  BYTEARRAYDECL(ConstantLatencyOnOff)
  BYTEARRAYDECL(Space)
  BYTEARRAYDECL(HeadphoneSpaceOnOff)
  BYTEARRAYDECL(WahPedalToPitch)
  BYTEARRAYDECL(InputSource)
  BYTEARRAYDECL(ReampSense)
  BYTEARRAYDECL(PureCabOnOff)
  BYTEARRAYDECL(PureCab)
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
  // SPDIFOutputVolume
  void midiRequestSPDIFOutputVolume();
  void midiApplySPDIFOutputVolume(unsigned short rawVal);
  // MasterTune
  void midiRequestMasterTune();
  void midiApplyMasterTune(unsigned short rawVal);
  // MonitorCabOff
  void midiRequestMonitorCabOff();
  void midiApplyMonitorCabOff(unsigned short);
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
  // MainOutputSource
  void midiRequestMainOutputSource();
  void midiApplyMainOutputSource(unsigned short rawVal);
  // SPDIFOutputSource
  void midiRequestSPDIFOutputSource();
  void midiApplySPDIFOutputSource(unsigned short rawVal);
  // MonitorOutputSource
  void midiRequestMonitorOutputSource();
  void midiApplyMonitorOutputSource(unsigned short rawVal);
  // DirectOutputSource
  void midiRequestDirectOutputSource();
  void midiApplyDirectOutputSource(unsigned short rawVal);
  // AuxInToMain
  void midiRequestAuxInToMain();
  void midiApplyAuxInToMain(unsigned short rawVal);
  // AuxInToHeadphone
  void midiRequestAuxInToHeadphone();
  void midiApplyAuxInToHeadphone(unsigned short rawVal);
  // ConstantLatencyOnOff
  void midiRequestConstantLatencyOnOff();
  void midiApplyConstantLatencyOnOff(unsigned short rawVal);
  // Space
  void midiRequestSpace();
  void midiApplySpace(unsigned short rawVal);
  // HeadphoneSpaceOnOff
  void midiRequestHeadphoneSpaceOnOff();
  void midiApplyHeadphoneSpaceOnOff(unsigned short rawVal);
  // WahPedalToPitch
  void midiRequestWahPedalToPitch();
  void midiApplyWahPedalToPitch(unsigned short rawVal);
  // InputSource
  void midiRequestInputSource();
  void midiApplyInputSource(unsigned short rawVal);
  // ReampSens
  void midiRequestReampSense();
  void midiApplyReampSense(unsigned short rawVal);
  // PureCabOnOff
  void midiRequestPureCabOnOff();
  void midiApplyPureCabOnOff(unsigned short rawVal);
  // PureCab
  void midiRequestPureCab();
  void midiApplyPureCab(unsigned short rawVal);
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
  virtual void midiSPDIFOutputVolumeReceived(unsigned short rawVal) = 0;
  virtual void midiMasterTuneReceived(unsigned short rawVal) = 0;
  virtual void midiMonitorCabOffReceived(unsigned short rawVal) = 0;
  virtual void midiSPDIFInputEnableReceived(unsigned short rawVal) = 0;
  virtual void midiMainOutputEQBassReceived(unsigned short rawVal) = 0;
  virtual void midiMainOutputEQMiddleReceived(unsigned short rawVal) = 0;
  virtual void midiMainOutputEQTrebleReceived(unsigned short rawVal) = 0;
  virtual void midiMainOutputEQPresenceReceived(unsigned short rawVal) = 0;
  virtual void midiMonitorOutputEQBassReceived(unsigned short rawVal) = 0;
  virtual void midiMonitorOutputEQMiddleReceived(unsigned short rawVal) = 0;
  virtual void midiMonitorOutputEQTrebleReceived(unsigned short rawVal) = 0;
  virtual void midiMonitorOutputEQPresenceReceived(unsigned short rawVal) = 0;
  virtual void midiMainOutputSourceReceived(unsigned short rawVal) = 0;
  virtual void midiSPDIFOutputSourceReceived(unsigned short rawVal) = 0;
  virtual void midiMonitorOutputSourceReceived(unsigned short rawVal) = 0;
  virtual void midiDirectOutputSourceReceived(unsigned short rawVal) = 0;
  virtual void midiAuxInToMainReceived(unsigned short rawVal) = 0;
  virtual void midiAuxInToHeadphoneReceived(unsigned short rawVal) = 0;
  virtual void midiConstantLatencyOnOffReceived(unsigned short rawVal) = 0;
  virtual void midiSpaceReceived(unsigned short rawVal) = 0;
  virtual void midiHeadphoneSpaceOnOffReceived(unsigned short rawVal) = 0;
  virtual void midiWahPedalToPitchReceived(unsigned short rawVal) = 0;
  virtual void midiInputSourceReceived(unsigned short rawVal) = 0;
  virtual void midiReampSensReceived(unsigned short rawVal) = 0;
  virtual void midiPureCabOnOffReceived(unsigned short rawVal) = 0;
  virtual void midiPureCabReceived(unsigned short rawVal) = 0;
  virtual void midiOperationModeReceived(unsigned short rawVal) = 0;

  ByteArray getAddressPage();
};

#endif // GLOBALMIDI_H
