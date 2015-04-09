#include "DelayMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(DelayMidi, AddressPage,     0x4A)

DelayMidi::DelayMidi()
{

}

DelayMidi::~DelayMidi()
{

}

ByteArray DelayMidi::getAddressPage()
{
  return sAddressPage;
}
