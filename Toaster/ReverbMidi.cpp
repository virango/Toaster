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
#include "ReverbMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(ReverbMidi, AddressPage,     0x4B)
// parameter
BYTEARRAYDEF(ReverbMidi, Type,            0x00)
BYTEARRAYDEF(ReverbMidi, OnOffCutsTail,   0x02)
BYTEARRAYDEF(ReverbMidi, Mix,             0x03)
BYTEARRAYDEF(ReverbMidi, Volume,          0x04)
BYTEARRAYDEF(ReverbMidi, DelRevBalance,   0x05)
BYTEARRAYDEF(ReverbMidi, Time,            0x06)
BYTEARRAYDEF(ReverbMidi, Damping,         0x07)
BYTEARRAYDEF(ReverbMidi, Bandwidth,       0x08)
BYTEARRAYDEF(ReverbMidi, CenterFrequency, 0x09)
BYTEARRAYDEF(ReverbMidi, PreDelay,        0x0A)
BYTEARRAYDEF(ReverbMidi, OnOffKeepsTail,  0x0B)
BYTEARRAYDEF(ReverbMidi, Ducking,         0x0C)

ReverbMidi::ReverbMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

ReverbMidi::~ReverbMidi()
{

}

unsigned char ReverbMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void ReverbMidi::consumeSysExMsg(const ByteArray& msg)
{
  if(msg.size() >= 12)
  {
    unsigned short rawVal = Utils::extractRawVal(msg[10], msg[11]);
    const char param = msg[9];
    if(param == sType[0])
      midiTypeReceived(rawVal);
    else if(param == sOnOffCutsTail[0])
      midiOnOffCutsTailReceived(rawVal);
    else if(param == sMix[0])
      midiMixReceived(rawVal);
    else if(param == sVolume[0])
      midiVolumeReceived(rawVal);
    else if(param == sDelRevBalance[0])
      midiDelRevBalanceReceived(rawVal);
    else if(param == sTime[0])
      midiTimeReceived(rawVal);
    else if(param == sDamping[0])
      midiDampingReceived(rawVal);
    else if(param == sBandwidth[0])
      midiBandwidthReceived(rawVal);
    else if(param == sCenterFrequency[0])
      midiCenterFrequencyReceived(rawVal);
    else if(param == sPreDelay[0])
      midiPreDelayReceived(rawVal);
    else if(param == sOnOffKeepsTail[0])
      midiOnOffKeepsTailReceived(rawVal);
    else if(param == sDucking[0])
      midiDuckingReceived(rawVal);
  }
}

void ReverbMidi::midiRequestType()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sType));
}

void ReverbMidi::midiApplyType(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sType, rawVal));
}

void ReverbMidi::midiRequestOnOffCutsTail()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sOnOffCutsTail));
}

void ReverbMidi::midiApplyOnOffCutsTail(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sOnOffCutsTail, rawVal));
}

void ReverbMidi::midiRequestMix()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMix));
}

void ReverbMidi::midiApplyMix(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMix, rawVal));
}

void ReverbMidi::midiRequestVolume()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sVolume));
}

void ReverbMidi::midiApplyVolume(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sVolume, rawVal));
}

void ReverbMidi::midiRequestDelRevBalance()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sDelRevBalance));
}

void ReverbMidi::midiApplyDelRevBalance(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sDelRevBalance, rawVal));
}

void ReverbMidi::midiRequestTime()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sTime));
}

void ReverbMidi::midiApplyTime(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sTime, rawVal));
}

void ReverbMidi::midiRequestDamping()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sDamping));
}

void ReverbMidi::midiApplyDamping(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sDamping, rawVal));
}

void ReverbMidi::midiRequestBandwidth()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sBandwidth));
}

void ReverbMidi::midiApplyBandwidth(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sBandwidth, rawVal));
}

void ReverbMidi::midiRequestCenterFrequency()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sCenterFrequency));
}

void ReverbMidi::midiApplyCenterFrequency(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sCenterFrequency, rawVal));
}

void ReverbMidi::midiRequestPreDelay()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sPreDelay));
}

void ReverbMidi::midiApplyPreDelay(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sPreDelay, rawVal));
}

void ReverbMidi::midiRequestOnOffKeepsTail()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sOnOffKeepsTail));
}

void ReverbMidi::midiApplyOnOffKeepsTail(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sOnOffKeepsTail, rawVal));
}

void ReverbMidi::midiRequestDucking()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sDucking));
}

void ReverbMidi::midiApplyDucking(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sDucking, rawVal));
}

ByteArray ReverbMidi::getAddressPage()
{
  return sAddressPage;
}
