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
#ifndef EQMIDI_H
#define EQMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class EqMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)

  // parameter
  BYTEARRAYDECL(OnOff)
  BYTEARRAYDECL(Bass)
  BYTEARRAYDECL(Middle)
  BYTEARRAYDECL(Treble)
  BYTEARRAYDECL(Presence)

  EqMidi();
  ~EqMidi();

  // ISysExConsumer
  void consumeSysExMsg(const ByteArray& msg);
  unsigned char getId();

  // parameter
  // OnOff
  void midiRequestOnOff();
  void midiApplyOnOff(unsigned short rawVal);
  // Bass
  void midiRequestBass();
  void midiApplyBass(unsigned short rawVal);
  // Middle
  void midiRequestMiddle();
  void midiApplyMiddle(unsigned short rawVal);
  // Treble
  void midiRequestTreble();
  void midiApplyTreble(unsigned short rawVal);
  // Presence
  void midiRequestPresence();
  void midiApplyPresence(unsigned short rawVal);

  // receive callbacks for derived class
  virtual void midiOnOffReceived(unsigned short rawVal) = 0;
  virtual void midiBassReceived(unsigned short rawVal) = 0;
  virtual void midiMiddleReceived(unsigned short rawVal) = 0;
  virtual void midiTrebleReceived(unsigned short rawVal) = 0;
  virtual void midiPresenceReceived(unsigned short rawVal) = 0;

  // utility methods
  ByteArray getAddressPage();
};

#endif // EQMIDI_H
