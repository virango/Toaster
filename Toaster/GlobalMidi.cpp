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
#include "GlobalMidi.h"
#include "Midi.h"


// address page
BYTEARRAYDEF(GlobalMidi, AddressPage,     0x7F)
// parameter
BYTEARRAYDEF(GlobalMidi, MainOutputVolume,        0x00)
BYTEARRAYDEF(GlobalMidi, HeadphoneOutputVolume,   0x01)
BYTEARRAYDEF(GlobalMidi, MonitorOutputVolume,     0x02)
BYTEARRAYDEF(GlobalMidi, DirectOutputVolume,      0x03)
BYTEARRAYDEF(GlobalMidi, MasterTune,              0x05)
BYTEARRAYDEF(GlobalMidi, SPDIFInputEnable,        0x0B)
BYTEARRAYDEF(GlobalMidi, MainOutputEQBass,        0x0C)
BYTEARRAYDEF(GlobalMidi, MainOutputEQMiddle,      0x0D)
BYTEARRAYDEF(GlobalMidi, MainOutputEQTreble,      0x0E)
BYTEARRAYDEF(GlobalMidi, MainOutputEQPresence,    0x0F)
BYTEARRAYDEF(GlobalMidi, MonitorOutputEQBass,     0x11)
BYTEARRAYDEF(GlobalMidi, MonitorOutputEQMiddle,   0x12)
BYTEARRAYDEF(GlobalMidi, MonitorOutputEQTreble,   0x13)
BYTEARRAYDEF(GlobalMidi, MonitorOutputEQPresence, 0x14)
BYTEARRAYDEF(GlobalMidi, MainOutputSource,        0x16)
BYTEARRAYDEF(GlobalMidi, SPDIFOutputSource,       0x17)
BYTEARRAYDEF(GlobalMidi, MonitorOutputSource,     0x19)
BYTEARRAYDEF(GlobalMidi, DirectOutputSource,      0x1a)
BYTEARRAYDEF(GlobalMidi, WahPedalToPitch,         0x27)
BYTEARRAYDEF(GlobalMidi, OperationMode,           0x7E)
BYTEARRAYDEF(GlobalMidi, ConnectName,             0x7F)

GlobalMidi::GlobalMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

GlobalMidi::~GlobalMidi()
{
}

unsigned char GlobalMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void GlobalMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = extractRawVal(msg->at(10), msg->at(11));
    const char param = msg->at(9);
    if(param == sMainOutputVolume[0])
      midiMainOutputVolumeReceived(rawVal);
    else if(param == sHeadphoneOutputVolume[0])
      midiHeadphoneOutputVolumeReceived(rawVal);
    else if(param == sMonitorOutputVolume[0])
      midiMonitorOutputVolumeReceived(rawVal);
    else if(param == sDirectOutputVolume[0])
      midiDirectOutputVolumeReceived(rawVal);
    else if(param == sMasterTune[0])
      midiMasterTuneReceived(rawVal);
    else if(param == sSPDIFInputEnable[0])
      midiSPDIFInputEnableReceived(rawVal);
    else if(param == sMainOutputEQBass[0])
      midiMainOutputEQBassReceived(rawVal);
    else if(param == sMainOutputEQMiddle[0])
      midiMainOutputEQMiddleReceived(rawVal);
    else if(param == sMainOutputEQTreble[0])
      midiMainOutputEQTrebleReceived(rawVal);
    else if(param == sMainOutputEQPresence[0])
      midiMainOutputEQPresenceReceived(rawVal);
    else if(param == sMonitorOutputEQBass[0])
      midiMonitorOutputEQBassReceived(rawVal);
    else if(param == sMonitorOutputEQMiddle[0])
      midiMonitorOutputEQMiddleReceived(rawVal);
    else if(param == sMonitorOutputEQTreble[0])
      midiMonitorOutputEQTrebleReceived(rawVal);
    else if(param == sMonitorOutputEQPresence[0])
      midiMonitorOutputEQPresenceReceived(rawVal);
    else if(param == sMainOutputSource[0])
      midiMainOutputSourceReceived(rawVal);
    else if(param == sSPDIFOutputSource[0])
      midiSPDIFOutputSourceReceived(rawVal);
    else if(param == sMonitorOutputSource[0])
      midiMonitorOutputSourceReceived(rawVal);
    else if(param == sDirectOutputSource[0])
      midiDirectOutputSourceReceived(rawVal);
    else if(param == sWahPedalToPitch[0])
      midiWahPedalToPitchReceived(rawVal);
    else if(param == sOperationMode[0])
      midiOperationModeReceived(rawVal);
  }
}

void GlobalMidi::midiRequestMainOutputVolume()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMainOutputVolume));
}

void GlobalMidi::midiApplyMainOutputVolume(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMainOutputVolume, rawVal));
}

void GlobalMidi::midiRequestHeadphoneOutputVolume()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sHeadphoneOutputVolume));
}

void GlobalMidi::midiApplyHeadphoneOutputVolume(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sHeadphoneOutputVolume, rawVal));
}

void GlobalMidi::midiRequestMonitorOutputVolume()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMonitorOutputVolume));
}

void GlobalMidi::midiApplyMonitorOutputVolume(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMonitorOutputVolume, rawVal));
}

void GlobalMidi::midiRequestDirectOutputVolume()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sDirectOutputVolume));
}

void GlobalMidi::midiApplyDirectOutputVolume(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sDirectOutputVolume, rawVal));
}

void GlobalMidi::midiRequestMasterTune()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMasterTune));
}

void GlobalMidi::midiApplyMasterTune(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMasterTune, rawVal));
}

void GlobalMidi::midiRequestSPDIFInputEnable()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sSPDIFInputEnable));
}

void GlobalMidi::midiApplySPDIFInputEnable(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sSPDIFInputEnable, rawVal));
}

void GlobalMidi::midiRequestMainOutputEQBass()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMainOutputEQBass));
}

void GlobalMidi::midiApplyMainOutputEQBass(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMainOutputEQBass, rawVal));
}

void GlobalMidi::midiRequestMainOutputEQMiddle()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMainOutputEQMiddle));
}

void GlobalMidi::midiApplyMainOutputEQMiddle(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMainOutputEQMiddle, rawVal));
}

void GlobalMidi::midiRequestMainOutputEQTreble()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMainOutputEQTreble));
}

void GlobalMidi::midiApplyMainOutputEQTreble(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMainOutputEQTreble, rawVal));
}

void GlobalMidi::midiRequestMainOutputEQPresence()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMainOutputEQPresence));
}

void GlobalMidi::midiApplyMainOutputEQPresence(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMainOutputEQPresence, rawVal));
}

void GlobalMidi::midiRequestMonitorOutputEQBass()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMonitorOutputEQBass));
}

void GlobalMidi::midiApplyMonitorOutputEQBass(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMonitorOutputEQBass, rawVal));
}

void GlobalMidi::midiRequestMonitorOutputEQMiddle()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMonitorOutputEQMiddle));
}

void GlobalMidi::midiApplyMonitorOutputEQMiddle(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMonitorOutputEQMiddle, rawVal));
}

void GlobalMidi::midiRequestMonitorOutputEQTreble()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMonitorOutputEQTreble));
}

void GlobalMidi::midiApplyMonitorOutputEQTreble(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMonitorOutputEQTreble, rawVal));
}

void GlobalMidi::midiRequestMonitorOutputEQPresence()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMonitorOutputEQPresence));
}

void GlobalMidi::midiApplyMonitorOutputEQPresence(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMonitorOutputEQPresence, rawVal));
}

void GlobalMidi::midiRequestMainOutputSource()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMainOutputSource));
}

void GlobalMidi::midiApplyMainOutputSource(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMainOutputSource, rawVal));
}

void GlobalMidi::midiRequestSPDIFOutputSource()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sSPDIFOutputSource));
}

void GlobalMidi::midiApplySPDIFOutputSource(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sSPDIFOutputSource, rawVal));
}

void GlobalMidi::midiRequestMonitorOutputSource()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMonitorOutputSource));
}

void GlobalMidi::midiApplyMonitorOutputSource(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMonitorOutputSource, rawVal));
}

void GlobalMidi::midiRequestDirectOutputSource()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sDirectOutputSource));
}

void GlobalMidi::midiApplyDirectOutputSource(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sDirectOutputSource, rawVal));
}

void GlobalMidi::midiRequestWahPedalToPitch()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sWahPedalToPitch));
}

void GlobalMidi::midiApplyWahPedalToPitch(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sWahPedalToPitch, rawVal));
}

void GlobalMidi::midiRequestOperationMode()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sOperationMode));
}

void GlobalMidi::midiApplyOperationMode(unsigned short rawVal)
{

  if(rawVal == 1)
  {
    ByteArray cc;
    cc.push_back(0xB0);
    cc.push_back(31);
    cc.push_back(1);
    Midi::get().sendCmd(cc);
  }
  else
  {
    ByteArray cc;
    cc.push_back(0xB0);
    cc.push_back(31);
    cc.push_back(0);
    Midi::get().sendCmd(cc);
    Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sOperationMode, rawVal));
  }

}


void GlobalMidi::midiApplyConnectName(const QString& connectName)
{
  Midi::get().sendCmd(createStringParamSetCmd(getAddressPage(), sConnectName, connectName));
}

void GlobalMidi::midiSendBeacon()
{
  ByteArray ap;
  ByteArray param;
  ByteArray value;

  // todo: move it to a better place (an extra class?)
  // but first: find out what module ap==0x40 is (it's not in the public spec)
  ap.push_back(0x40);
  param.push_back(0x02);
  value.push_back(0x6f); // todo: check ack  (fct==0x7e, ap==0x7f, param==counter)
                         // 0x6f ==> ack received, 0x6e ack not received
                         // with 0x6f the kpa periodically sends some info
  value.push_back(0x5);
  Midi::get().sendCmd(createReservedFct7E(ap, param, value));
}

ByteArray GlobalMidi::getAddressPage()
{
  return sAddressPage;
}
