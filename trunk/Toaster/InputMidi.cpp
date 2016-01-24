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
#include "InputMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(InputMidi, AddressPage,     0x09)
// parameter
BYTEARRAYDEF(InputMidi, NoiseGate,       0x03)
BYTEARRAYDEF(InputMidi, CleanSense,      0x04)
BYTEARRAYDEF(InputMidi, DistortionSense, 0x05)

InputMidi::InputMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

InputMidi::~InputMidi()
{
}

void InputMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = extractRawVal(msg->at(10), msg->at(11));
    const char param = msg->at(9);
    if(param == sNoiseGate[0])
      midiNoiseGateReceived(rawVal);
    else if(param == sCleanSense[0])
      midiCleanSenseReceived(rawVal);
    else if(param == sDistortionSense[0])
      midiDistortionSenseReceived(rawVal);
  }
}

unsigned char InputMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void InputMidi::midiRequestNoiseGate()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sNoiseGate));
}

void InputMidi::midiApplyNoiseGate(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sNoiseGate, rawVal));
  Midi::get().sendCmd(createNRPNSingleParamSetCmd(getAddressPage(), sNoiseGate, packRawVal(rawVal)));
}

void InputMidi::midiRequestCleanSense()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sCleanSense));
}

void InputMidi::midiApplyCleanSense(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sCleanSense, rawVal));
  Midi::get().sendCmd(createNRPNSingleParamSetCmd(getAddressPage(), sCleanSense, packRawVal(rawVal)));
}

void InputMidi::midiRequestDistortionSense()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sDistortionSense));
}

void InputMidi::midiApplyDistortionSense(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sDistortionSense, rawVal));
  Midi::get().sendCmd(createNRPNSingleParamSetCmd(getAddressPage(), sDistortionSense, packRawVal(rawVal)));
}

ByteArray InputMidi::getAddressPage()
{
  return sAddressPage;
}

