#include "NRPNBase.h"

BYTEARRAYDEF(NRPNBase, Header,           0xB0)
BYTEARRAYDEF(NRPNBase, AddressPageTag,   0x63)
BYTEARRAYDEF(NRPNBase, ParameterTag,     0x62)
BYTEARRAYDEF(NRPNBase, MSBValueTag,      0x06)
BYTEARRAYDEF(NRPNBase, LSBValueTag,      0x26)
BYTEARRAYDEF(NRPNBase, LowResValueTag,   0x77)

NRPNBase::NRPNBase()
{

}

NRPNBase::~NRPNBase()
{

}

ByteArray NRPNBase::createNRPNSingleParamSetCmd(const ByteArray& addressPage, const ByteArray& param, const ByteArray& val)
{
  ByteArray res;
  if(val.size() == 2 || val.size() == 1)
  {
    VEC_INSERT(res, sHeader);
    VEC_INSERT(res, sAddressPageTag);
    VEC_INSERT(res, addressPage);

    VEC_INSERT(res, sHeader);
    VEC_INSERT(res, sParameterTag);
    VEC_INSERT(res, param);

    if(val.size() == 2)
    {
      VEC_INSERT(res, sHeader);
      VEC_INSERT(res, sMSBValueTag);
      res.push_back(val[0]);

      VEC_INSERT(res, sHeader);
      VEC_INSERT(res, sLSBValueTag);
      res.push_back(val[1]);
    }
    else
    {
      VEC_INSERT(res, sHeader);
      VEC_INSERT(res, sLowResValueTag);
      res.push_back(val[0]);
    }
  }
  return res;
}
