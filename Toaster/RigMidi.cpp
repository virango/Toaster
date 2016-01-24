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
#include "RigMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(RigMidi, AddressPage,     0x04)
// parameter
BYTEARRAYDEF(RigMidi, Tempo,           0x00)
BYTEARRAYDEF(RigMidi, Volume,          0x01)
BYTEARRAYDEF(RigMidi, TempoEnable,     0x02)
BYTEARRAYDEF(RigMidi, StompsEnable,    0x40)
BYTEARRAYDEF(RigMidi, StackEnable,     0x41)
BYTEARRAYDEF(RigMidi, EffectsEnable,   0x42)

RigMidi::RigMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

RigMidi::~RigMidi()
{
}

unsigned char RigMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void RigMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = extractRawVal(msg->at(10), msg->at(11));
    const char param = msg->at(9);
    if(param == sTempo[0])
      midiTempoReceived(rawVal);
    else if(param == sVolume[0])
      midiVolumeReceived(rawVal);
    else if(param == sTempoEnable[0])
      midiTempoEnableReceived(rawVal);
    else if(param == sStompsEnable[0])
      midiStompsEnableReceived(rawVal);
    else if(param == sStackEnable[0])
      midiStackEnableReceived(rawVal);
    else if(param == sEffectsEnable[0])
      midiEffectsEnableReceived(rawVal);
  }
}

void RigMidi::midiRequestTempo()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sTempo));
}

void RigMidi::midiApplyTempo(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sTempo, rawVal));
}

void RigMidi::midiRequestVolume()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sVolume));
}

void RigMidi::midiApplyVolume(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sVolume, rawVal));
}

void RigMidi::midiRequestTempoEnable()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sTempoEnable));
}

void RigMidi::midiApplyTempoEnable(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sTempoEnable, rawVal));
}

void RigMidi::midiRequestStompsEnable()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sStompsEnable));
}

void RigMidi::midiApplyStompsEnable(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sStompsEnable, rawVal));
}

void RigMidi::midiRequestStackEnable()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sStackEnable));
}

void RigMidi::midiApplyStackEnable(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sStackEnable, rawVal));
}

void RigMidi::midiRequestEffectsEnable()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sEffectsEnable));
}

void RigMidi::midiApplyEffectsEnable(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sEffectsEnable, rawVal));
}

ByteArray RigMidi::getAddressPage()
{
  return sAddressPage;
}
