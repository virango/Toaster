#include "GlobalMidi.h"
#include "Midi.h"


// address page
BYTEARRAYDEF(GlobalMidi, AddressPage,     0x7F)

GlobalMidi::GlobalMidi()
{

}

GlobalMidi::~GlobalMidi()
{

}

ByteArray GlobalMidi::getAddressPage()
{
  return sAddressPage;
}
