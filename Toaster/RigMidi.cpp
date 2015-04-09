#include "RigMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(RigMidi, AddressPage,     0x04)
// parameter
BYTEARRAYDEF(RigMidi, Tempo,           0x00)
BYTEARRAYDEF(RigMidi, Volume,          0x01)
BYTEARRAYDEF(RigMidi, TempoEnable,     0x02)

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
    const char fct = msg->at(9);
    if(fct == sTempo[0])
      midiTempoReceived(rawVal);
    else if(fct == sVolume[0])
      midiVolumeReceived(rawVal);
    else if(fct == sTempoEnable[0])
      midiTempoEnableReceived(rawVal);
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

ByteArray RigMidi::getAddressPage()
{
  return sAddressPage;
}
