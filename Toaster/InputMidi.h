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
#ifndef INPUTMIDI_H
#define INPUTMIDI_H
#include "SysExBase.h"
#include "NRPNBase.h"
#include "SysExMsgDispatcher.h"

class InputMidi : public SysExBase, public NRPNBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(NoiseGate)
  BYTEARRAYDECL(CleanSense)
  BYTEARRAYDECL(DistortionSense)

  InputMidi();
  ~InputMidi();

  // ISysExConsumer
  void consumeSysExMsg(const ByteArray& msg);
  unsigned char getId();

  // parameter
  // Noise Gate
  void midiRequestNoiseGate();
  void midiApplyNoiseGate(unsigned short rawVal);
  // Clean Sense
  void midiRequestCleanSense();
  void midiApplyCleanSense(unsigned short rawVal);
  // Distortion Sense
  void midiRequestDistortionSense();
  void midiApplyDistortionSense(unsigned short rawVal);


  // receive callbacks for derived class
  virtual void midiNoiseGateReceived(unsigned short rawVal) = 0;
  virtual void midiCleanSenseReceived(unsigned short rawVal) = 0;
  virtual void midiDistortionSenseReceived(unsigned short rawVal) = 0;

  // utility methods
  ByteArray getAddressPage();
};

#endif // INPUTMIDI_H
