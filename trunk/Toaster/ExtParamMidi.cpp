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
#include "ExtParamMidi.h"
#include "Midi.h"

const unsigned int ExtParamMidi::sBrowserView = 0x1863c;

ExtParamMidi::ExtParamMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

ExtParamMidi::~ExtParamMidi()
{
  //SysExMsgDispatcher::get().removeConsumer(this);
}

unsigned char ExtParamMidi::getId()
{
  return sExtParamChange[0];
}

void ExtParamMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 19)
  {
    unsigned int param = extractRawVal(ByteArray(msg->begin() + 9, msg->end()));
    unsigned int rawVal = extractRawVal(ByteArray(msg->begin() + 14, msg->end()));
    if(param == sBrowserView)
      midiBrowserViewReceived(rawVal);
  }
}

void ExtParamMidi::midiRequestBrowserView()
{
  Midi::get().sendCmd(createExtParamGetCmd(sBrowserView));
}

void ExtParamMidi::midiApplyBrowserView(unsigned int rawVal)
{
  Midi::get().sendCmd(createExtParamSetCmd(sBrowserView, rawVal));
}
