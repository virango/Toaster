#include "TunerNoteMidi.h"

// address page
BYTEARRAYDEF(TunerNoteMidi, AddressPage,     0x7D)
// parameter
BYTEARRAYDEF(TunerNoteMidi, Note,            0x54)

TunerNoteMidi::TunerNoteMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

TunerNoteMidi::~TunerNoteMidi()
{
}

unsigned char TunerNoteMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void TunerNoteMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = extractRawVal(msg->at(10), msg->at(11));
    const char param = msg->at(9);
    if(param == sNote[0])
      midiNoteReceived(rawVal);
  }
}

ByteArray TunerNoteMidi::getAddressPage()
{
  return sAddressPage;
}
