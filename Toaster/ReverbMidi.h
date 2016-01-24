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
#ifndef REVERBMIDI_H
#define REVERBMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class ReverbMidi: public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(Type)
  BYTEARRAYDECL(OnOffCutsTail)
  BYTEARRAYDECL(Mix)
  BYTEARRAYDECL(Volume)
  BYTEARRAYDECL(DelRevBalance)
  BYTEARRAYDECL(Time)
  BYTEARRAYDECL(Damping)
  BYTEARRAYDECL(Bandwidth)
  BYTEARRAYDECL(CenterFrequency)
  BYTEARRAYDECL(PreDelay)
  BYTEARRAYDECL(OnOffKeepsTail)
  BYTEARRAYDECL(Ducking)

  ReverbMidi();
  ~ReverbMidi();

  // ISysExConsumer
  unsigned char getId();
  void consumeSysExMsg(ByteArray* msg);
  // parameter
  // Type
  void midiRequestType();
  void midiApplyType(unsigned short rawVal);
  // OnOffCutsTail
  void midiRequestOnOffCutsTail();
  void midiApplyOnOffCutsTail(unsigned short rawVal);
  // Mix
  void midiRequestMix();
  void midiApplyMix(unsigned short rawVal);
  // Volume
  void midiRequestVolume();
  void midiApplyVolume(unsigned short rawVal);
  // DelRevBalance
  void midiRequestDelRevBalance();
  void midiApplyDelRevBalance(unsigned short rawVal);
  // Time
  void midiRequestTime();
  void midiApplyTime(unsigned short rawVal);
  // Damping
  void midiRequestDamping();
  void midiApplyDamping(unsigned short rawVal);
  // Bandwidth
  void midiRequestBandwidth();
  void midiApplyBandwidth(unsigned short rawVal);
  // CenterFrequency
  void midiRequestCenterFrequency();
  void midiApplyCenterFrequency(unsigned short rawVal);
  // PreDelay
  void midiRequestPreDelay();
  void midiApplyPreDelay(unsigned short rawVal);
  // OnOffKeepsTail
  void midiRequestOnOffKeepsTail();
  void midiApplyOnOffKeepsTail(unsigned short rawVal);
  // Ducking
  void midiRequestDucking();
  void midiApplyDucking(unsigned short rawVal);

  // receive callbacks for derived class
  virtual void midiTypeReceived(unsigned short rawVal) = 0;
  virtual void midiOnOffCutsTailReceived(unsigned short rawVal) = 0;
  virtual void midiMixReceived(unsigned short rawVal) = 0;
  virtual void midiVolumeReceived(unsigned short rawVal) = 0;
  virtual void midiDelRevBalanceReceived(unsigned short rawVal) = 0;
  virtual void midiTimeReceived(unsigned short rawVal) = 0;
  virtual void midiDampingReceived(unsigned short rawVal) = 0;
  virtual void midiBandwidthReceived(unsigned short rawVal) = 0;
  virtual void midiCenterFrequencyReceived(unsigned short rawVal) = 0;
  virtual void midiPreDelayReceived(unsigned short rawVal) = 0;
  virtual void midiOnOffKeepsTailReceived(unsigned short rawVal) = 0;
  virtual void midiDuckingReceived(unsigned short rawVal) = 0;

  ByteArray getAddressPage();
};

#endif // REVERBMIDI_H
