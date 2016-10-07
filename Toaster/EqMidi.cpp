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
#include "EqMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(EqMidi, AddressPage,     0x0B)

// parameter
BYTEARRAYDEF(EqMidi, OnOff,           0x02)
BYTEARRAYDEF(EqMidi, Bass,            0x04)
BYTEARRAYDEF(EqMidi, Middle,          0x05)
BYTEARRAYDEF(EqMidi, Treble,          0x06)
BYTEARRAYDEF(EqMidi, Presence,        0x07)

EqMidi::EqMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

EqMidi::~EqMidi()
{

}

unsigned char EqMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void EqMidi::consumeSysExMsg(const ByteArray& msg)
{
  if(msg.size() >= 12)
  {
    unsigned short rawVal = Utils::extractRawVal(msg[10], msg[11]);
    const char param = msg[9];
    if(param == sOnOff[0])
      midiOnOffReceived(rawVal);
    else if(param == sBass[0])
      midiBassReceived(rawVal);
    else if(param == sMiddle[0])
      midiMiddleReceived(rawVal);
    else if(param == sTreble[0])
      midiTrebleReceived(rawVal);
    else if(param == sPresence[0])
      midiPresenceReceived(rawVal);
  }
}

void EqMidi::midiRequestOnOff()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sOnOff));
}

void EqMidi::midiApplyOnOff(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sOnOff, rawVal));
}

void EqMidi::midiRequestBass()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sBass));
}

void EqMidi::midiApplyBass(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sBass, rawVal));
}

void EqMidi::midiRequestMiddle()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMiddle));
}

void EqMidi::midiApplyMiddle(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMiddle, rawVal));
}

void EqMidi::midiRequestTreble()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sTreble));
}

void EqMidi::midiApplyTreble(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sTreble, rawVal));
}

void EqMidi::midiRequestPresence()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sPresence));
}

void EqMidi::midiApplyPresence(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sPresence, rawVal));
}

ByteArray EqMidi::getAddressPage()
{
  return sAddressPage;
}

