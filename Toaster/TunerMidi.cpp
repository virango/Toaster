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
#include "TunerMidi.h"

// address page
BYTEARRAYDEF(TunerMidi, AddressPage,     0x7D)
// parameter
BYTEARRAYDEF(TunerMidi, MuteSignal,      0x51)
BYTEARRAYDEF(TunerMidi, Note,            0x54)

TunerMidi::TunerMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

TunerMidi::~TunerMidi()
{
}

unsigned char TunerMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void TunerMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = extractRawVal(msg->at(10), msg->at(11));
    const char param = msg->at(9);
    if(param == sNote[0])
      midiNoteReceived(rawVal);
    else if(param == sMuteSignal[0])
      midiMuteSignalReceived(rawVal);
  }
}

void TunerMidi::midiRequestMuteSignal()
{
   Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMuteSignal));
}

void TunerMidi::midiApplyMuteSignal(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMuteSignal, rawVal));
}

ByteArray TunerMidi::getAddressPage()
{
  return sAddressPage;
}
