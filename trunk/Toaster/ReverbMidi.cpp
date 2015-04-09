#include "ReverbMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(ReverbMidi, AddressPage,     0x4B)

ReverbMidi::ReverbMidi()
{

}

ReverbMidi::~ReverbMidi()
{

}

ByteArray ReverbMidi::getAddressPage()
{
  return sAddressPage;
}
