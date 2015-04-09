#ifndef CABMIDI_H
#define CABMIDI_H
#include "SysExBase.h"

class CabMidi : public SysExBase
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter

public:
  CabMidi();
  ~CabMidi();

  ByteArray getAddressPage();
};

#endif // CABMIDI_H
