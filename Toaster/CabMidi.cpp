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
#include "CabMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(CabMidi, AddressPage,     0x0C)
// parameter
BYTEARRAYDEF(CabMidi, OnOff,           0x02)
BYTEARRAYDEF(CabMidi, Volume,          0x03)
BYTEARRAYDEF(CabMidi, HighShift,       0x04)
BYTEARRAYDEF(CabMidi, LowShift,        0x05)
BYTEARRAYDEF(CabMidi, Character,       0x06)

CabMidi::CabMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

CabMidi::~CabMidi()
{
}

unsigned char CabMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void CabMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = extractRawVal(msg->at(10), msg->at(11));
    const char param = msg->at(9);
    if(param == sOnOff[0])
      midiOnOffReceived(rawVal);
    else if(param == sVolume[0])
      midiVolumeReceived(rawVal);
    else if(param == sHighShift[0])
      midiHighShiftReceived(rawVal);
    else if(param == sLowShift[0])
      midiLowShiftReceived(rawVal);
    else if(param == sCharacter[0])
      midiCharacterReceived(rawVal);  
  }
}

void CabMidi::midiRequestOnOff()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sOnOff));
}

void CabMidi::midiApplyOnOff(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sOnOff, rawVal));
}

void CabMidi::midiRequestVolume()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sVolume));
}

void CabMidi::midiApplyVolume(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sVolume, rawVal));
}

void CabMidi::midiRequestHighShift()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sHighShift));
}

void CabMidi::midiApplyHighShift(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sHighShift, rawVal));
}

void CabMidi::midiRequestLowShift()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sLowShift));
}

void CabMidi::midiApplyLowShift(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sLowShift, rawVal));
}

void CabMidi::midiRequestCharacter()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sCharacter));
}

void CabMidi::midiApplyCharacter(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sCharacter, rawVal));
}

ByteArray CabMidi::getAddressPage()
{
  return sAddressPage;
}
