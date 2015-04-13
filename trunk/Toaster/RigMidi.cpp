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
