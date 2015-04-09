#include "RigMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(RigMidi, AddressPage,     0x04)

RigMidi::RigMidi()
{

}

RigMidi::~RigMidi()
{

}

ByteArray RigMidi::getAddressPage()
{
  return sAddressPage;
}
