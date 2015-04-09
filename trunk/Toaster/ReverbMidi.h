#ifndef REVERBMIDI_H
#define REVERBMIDI_H
#include "SysExBase.h"

class ReverbMidi
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)

public:
  ReverbMidi();
  ~ReverbMidi();

  ByteArray getAddressPage();
};

#endif // REVERBMIDI_H
