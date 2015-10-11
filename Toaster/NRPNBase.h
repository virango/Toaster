#ifndef NRPNBASE_H
#define NRPNBASE_H
#include "Commons.h"

class NRPNBase
{
protected:
  BYTEARRAYDECL(Header)
  BYTEARRAYDECL(AddressPageTag)
  BYTEARRAYDECL(ParameterTag)
  BYTEARRAYDECL(MSBValueTag)
  BYTEARRAYDECL(LSBValueTag)
  BYTEARRAYDECL(LowResValueTag)


  ByteArray createNRPNSingleParamSetCmd(const ByteArray& addressPage, const ByteArray& param, const ByteArray& val);

  NRPNBase();
  ~NRPNBase();

};

#endif // NRPNBASE_H
