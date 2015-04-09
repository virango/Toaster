#ifndef DELAYMIDI_H
#define DELAYMIDI_H
#include "SysExBase.h"

class DelayMidi : public SysExBase
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)

public:
  DelayMidi();
  ~DelayMidi();

  ByteArray getAddressPage();
};

#endif // DELAYMIDI_H
