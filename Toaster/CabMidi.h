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
#ifndef CABMIDI_H
#define CABMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class CabMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(OnOff)
  BYTEARRAYDECL(Volume)
  BYTEARRAYDECL(HighShift)
  BYTEARRAYDECL(LowShift)
  BYTEARRAYDECL(Character)

public:
  CabMidi();
  ~CabMidi();
  
  // ISysExConsumer
  unsigned char getId();
  void consumeSysExMsg(const ByteArray& msg);

protected:
  // parameter
  // OnOff 
  void midiRequestOnOff();
  void midiApplyOnOff(unsigned short rawVal);
  // Volume 
  void midiRequestVolume();
  void midiApplyVolume(unsigned short rawVal);
  // HighShift 
  void midiRequestHighShift();
  void midiApplyHighShift(unsigned short rawVal);
  // LowShift 
  void midiRequestLowShift();
  void midiApplyLowShift(unsigned short rawVal);
  // Character 
  void midiRequestCharacter();
  void midiApplyCharacter(unsigned short rawVal);
  
  // receive callbacks for derived class
  virtual void midiOnOffReceived(unsigned short rawVal) = 0;
  virtual void midiVolumeReceived(unsigned short rawVal) = 0;
  virtual void midiHighShiftReceived(unsigned short rawVal) = 0;
  virtual void midiLowShiftReceived(unsigned short rawVal) = 0;
  virtual void midiCharacterReceived(unsigned short rawVal) = 0;
  
  // utility methods
  ByteArray getAddressPage();
};

#endif // CABMIDI_H
