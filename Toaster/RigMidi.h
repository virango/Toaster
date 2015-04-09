#ifndef RIGMIDI_H
#define RIGMIDI_H
#include "SysExBase.h"

class RigMidi : public SysExBase
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)

public:
  RigMidi();
  ~RigMidi();

  ByteArray getAddressPage();
};

#endif // RIGMIDI_H
