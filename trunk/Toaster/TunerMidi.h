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
#ifndef TUNERMIDI_H
#define TUNERMIDI_H

#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class TunerMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(MuteSignal)
  BYTEARRAYDECL(Note)

  TunerMidi();
  ~TunerMidi();

  void midiRequestMuteSignal();
  void midiApplyMuteSignal(unsigned short rawVal);

  // ISysExConsumer
  unsigned char getId();
  void consumeSysExMsg(ByteArray* msg);

  // receive callbacks for derived class
  virtual void midiNoteReceived(unsigned short rawVal) = 0;
  virtual void midiMuteSignalReceived(unsigned short rawVal) = 0;

  // utility methods
  ByteArray getAddressPage();
};

#endif // TUNERMIDI_H
