#include "SysExBase.h"

BYTEARRAYDEF(SysExBase, Header,                 0xF0,0x00,0x20,0x33,0x02,0x7F) // syx: 0x0F; manufacturerID: 0x00,0x20,0x33; productType: 0x02; deviceID: 0x7D
BYTEARRAYDEF(SysExBase, Eox,                    0xF7)
BYTEARRAYDEF(SysExBase, SingleParamChange,      0x01,0x00)
BYTEARRAYDEF(SysExBase, MultiParamChange,       0x02,0x00)
BYTEARRAYDEF(SysExBase, StringParam,            0x03,0x00)
BYTEARRAYDEF(SysExBase, BLOB,                   0x04,0x00)
BYTEARRAYDEF(SysExBase, ExtParamChange,         0x06,0x00)
BYTEARRAYDEF(SysExBase, ExtStringParamChange,   0x07,0x00)
BYTEARRAYDEF(SysExBase, ReqSingleParamVal,      0x41,0x00)
BYTEARRAYDEF(SysExBase, ReqMultiParamVals,      0x42,0x00)
BYTEARRAYDEF(SysExBase, ReqStringParam,         0x43,0x00)
BYTEARRAYDEF(SysExBase, ReqExtStringParam,      0x47,0x00)

SysExBase::SysExBase()
{
}

SysExBase::~SysExBase()
{
}

ByteArray SysExBase::createSingleParamGetCmd(const ByteArray& addressPage, const ByteArray& param)
{
  ByteArray res;
  VEC_INSERT(res, sHeader);
  VEC_INSERT(res, sReqSingleParamVal);
  VEC_INSERT(res, addressPage);
  VEC_INSERT(res, param);
  VEC_INSERT(res, sEox);
  return res;
}

ByteArray SysExBase::createStringParamGetCmd(const ByteArray& addressPage, const ByteArray& param)
{
  ByteArray res;
  VEC_INSERT(res, sHeader);
  VEC_INSERT(res, sReqStringParam);
  VEC_INSERT(res, addressPage);
  VEC_INSERT(res, param);
  VEC_INSERT(res, sEox);
  return res;
}

ByteArray SysExBase::createSingleParamSetCmd(const ByteArray& addressPage, const ByteArray& param, const ByteArray& val)
{
  ByteArray res;
  VEC_INSERT(res, sHeader);
  VEC_INSERT(res, sSingleParamChange);
  VEC_INSERT(res, addressPage);
  VEC_INSERT(res, param);
  VEC_INSERT(res, val);
  VEC_INSERT(res, sEox);
  return res;
}

ByteArray SysExBase::createStringParamSetCmd(const ByteArray& addressPage, const ByteArray& param, const ByteArray& val)
{
  ByteArray res;
  VEC_INSERT(res, sHeader);
  VEC_INSERT(res, sStringParam);
  VEC_INSERT(res, addressPage);
  VEC_INSERT(res, param);
  VEC_INSERT(res, val);
  VEC_INSERT(res, sEox);
  return res;
}

ByteArray SysExBase::createSingleParamSetCmd(const ByteArray& addressPage, const ByteArray& param, unsigned short rawVal)
{
  return createSingleParamSetCmd(addressPage, param, packRawVal(rawVal));
}
