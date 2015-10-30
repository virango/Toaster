#include "TunerIndexMidi.h"

// address page
BYTEARRAYDEF(TunerIndexMidi, AddressPage,     0x7C)
// parameter
BYTEARRAYDEF(TunerIndexMidi, Index,           0x0F)

TunerIndexMidi::TunerIndexMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

TunerIndexMidi::~TunerIndexMidi()
{
}

unsigned char TunerIndexMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void TunerIndexMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = extractRawVal(msg->at(10), msg->at(11));
    const char param = msg->at(9);
    if(param == sIndex[0])
      midiIndexReceived(rawVal);
  }
}

ByteArray TunerIndexMidi::getAddressPage()
{
  return sAddressPage;
}
