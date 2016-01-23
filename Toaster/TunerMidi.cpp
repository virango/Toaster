#include "TunerMidi.h"

// address page
BYTEARRAYDEF(TunerMidi, AddressPage,     0x7D)
// parameter
BYTEARRAYDEF(TunerMidi, MuteSignal,      0x51)
BYTEARRAYDEF(TunerMidi, Note,            0x54)

TunerMidi::TunerMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

TunerMidi::~TunerMidi()
{
}

unsigned char TunerMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void TunerMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = extractRawVal(msg->at(10), msg->at(11));
    const char param = msg->at(9);
    if(param == sNote[0])
      midiNoteReceived(rawVal);
    else if(param == sMuteSignal[0])
      midiMuteSignalReceived(rawVal);
  }
}

void TunerMidi::midiRequestMuteSignal()
{
   Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMuteSignal));
}

void TunerMidi::midiApplyMuteSignal(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMuteSignal, rawVal));
}

ByteArray TunerMidi::getAddressPage()
{
  return sAddressPage;
}
