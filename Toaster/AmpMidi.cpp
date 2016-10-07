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
#include "AmpMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(AmpMidi, AddressPage,     0x0A)
// parameter
BYTEARRAYDEF(AmpMidi, OnOff,           0x02)
BYTEARRAYDEF(AmpMidi, Gain,            0x04)
BYTEARRAYDEF(AmpMidi, Definition,      0x06)
BYTEARRAYDEF(AmpMidi, Clarity,         0x07)
BYTEARRAYDEF(AmpMidi, PowerSagging,    0x08)
BYTEARRAYDEF(AmpMidi, Pick,            0x09)
BYTEARRAYDEF(AmpMidi, Compressor,      0x0A)
BYTEARRAYDEF(AmpMidi, TubeShape,       0x0B)
BYTEARRAYDEF(AmpMidi, TubeBias,        0x0C)
BYTEARRAYDEF(AmpMidi, DirectMix,       0x0F)

AmpMidi::AmpMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

AmpMidi::~AmpMidi()
{
}

unsigned char AmpMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void AmpMidi::consumeSysExMsg(const ByteArray& msg)
{
  if(msg.size() >= 12)
  {
    unsigned short rawVal = Utils::extractRawVal(msg[10], msg[11]);
    const char param = msg[9];
    if(param == sOnOff[0])
      midiOnOffReceived(rawVal);
    else if(param == sGain[0])
      midiGainReceived(rawVal);
    else if(param == sDefinition[0])
      midiDefinitionReceived(rawVal);
    else if(param == sClarity[0])
      midiClarityReceived(rawVal);
    else if(param == sPowerSagging[0])
      midiPowerSaggingReceived(rawVal);
    else if(param == sPick[0])
      midiPickReceived(rawVal);
    else if(param == sCompressor[0])
      midiCompressorReceived(rawVal);
    else if(param == sTubeShape[0])
      midiTubeShapeReceived(rawVal);
    else if(param == sTubeBias[0])
      midiTubeBiasReceived(rawVal);
    else if(param == sDirectMix[0])
      midiDirectMixReceived(rawVal);      
  }
}

void AmpMidi::midiRequestOnOff()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sOnOff));
}

void AmpMidi::midiApplyOnOff(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sOnOff, rawVal));
}

void AmpMidi::midiRequestGain()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sGain));
}

void AmpMidi::midiApplyGain(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sGain, rawVal));
}

void AmpMidi::midiRequestDefinition()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sDefinition));
}

void AmpMidi::midiApplyDefinition(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sDefinition, rawVal));
}

void AmpMidi::midiRequestClarity()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sClarity));
}

void AmpMidi::midiApplyClarity(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sClarity, rawVal));
}

void AmpMidi::midiRequestPowerSagging()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sPowerSagging));
}

void AmpMidi::midiApplyPowerSagging(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sPowerSagging, rawVal));
}

void AmpMidi::midiRequestPick()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sPick));
}

void AmpMidi::midiApplyPick(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sPick, rawVal));
}

void AmpMidi::midiRequestCompressor()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sCompressor));
}

void AmpMidi::midiApplyCompressor(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sCompressor, rawVal));
}

void AmpMidi::midiRequestTubeShape()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sTubeShape));
}

void AmpMidi::midiApplyTubeShape(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sTubeShape, rawVal));
}

void AmpMidi::midiRequestTubeBias()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sTubeBias));
}

void AmpMidi::midiApplyTubeBias(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sTubeBias, rawVal));
}

void AmpMidi::midiRequestDirectMix()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sDirectMix));
}

void AmpMidi::midiApplyDirectMix(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sDirectMix, rawVal));
}

ByteArray AmpMidi::getAddressPage()
{
  return sAddressPage;
}
