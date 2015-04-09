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

void AmpMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = msg->at(10) << 8 | msg->at(11);
    const char fct = msg->at(9);
    if(fct == sOnOff[0])
      midiOnOffReceived(rawVal);
    else if(fct == sGain[0])
      midiGainReceived(rawVal);
    else if(fct == sDefinition[0])
      midiDefinitionReceived(rawVal);
  }
}

unsigned char AmpMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

ByteArray AmpMidi::getAddressPage()
{
  return sAddressPage;
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
