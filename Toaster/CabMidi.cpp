#include "CabMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(CabMidi, AddressPage,     0x0C)

CabMidi::CabMidi()
{

}

CabMidi::~CabMidi()
{

}

ByteArray CabMidi::getAddressPage()
{
  return sAddressPage;
}
