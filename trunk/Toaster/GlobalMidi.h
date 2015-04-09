#ifndef GLOBALMIDI_H
#define GLOBALMIDI_H
#include "SysExBase.h"

class GlobalMidi : public SysExBase
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)

public:
  GlobalMidi();
  ~GlobalMidi();

  ByteArray getAddressPage();
};

#endif // GLOBALMIDI_H
