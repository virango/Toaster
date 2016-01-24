/*  This file is part of Toaster, the editor and remote control for Kemper profiling amplifier.
*
*   Copyright (C) 2016  Thomas Langer
*
*   Toaster is free software: you can redistribute it and/or modify it under the terms of the
*   GNU General Public License as published by the Free Software Foundation, either version 3
*   of the License, or (at your option) any later version.
*
*   Toaster is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
*   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*   See the GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along with Toaster.
*   If not, see <http://www.gnu.org/licenses/>.
*/
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
BYTEARRAYDEF(SysExBase, ReqExtParam,            0x46,0x00)
BYTEARRAYDEF(SysExBase, ReqExtStringParam,      0x47,0x00)
BYTEARRAYDEF(SysExBase, ReqParamAsString,       0x7C,0x00)

// these two functions are marked as reserved in the public midi spec
BYTEARRAYDEF(SysExBase, ReservedFct7E,          0x7E,0x00)
BYTEARRAYDEF(SysExBase, ReservedFct7F,          0x7F,0x00)

SysExBase::SysExBase()
{
}

SysExBase::~SysExBase()
{
}

// single parameter
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

ByteArray SysExBase::createSingleParamSetCmd(const ByteArray& addressPage, const ByteArray& param, unsigned short rawVal)
{
  return createSingleParamSetCmd(addressPage, param, packRawVal(rawVal));
}

// string parameter
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

ByteArray SysExBase::createStringParamSetCmd(const ByteArray& addressPage, const ByteArray& param, const QString& strVal)
{
  return createStringParamSetCmd(addressPage, param, packString(strVal));
}

// value as string
ByteArray SysExBase::createValueAsStringGetCmd(const ByteArray& addressPage, const ByteArray& param, const ByteArray& val)
{
  ByteArray res;
  VEC_INSERT(res, sHeader);
  VEC_INSERT(res, sReqParamAsString);
  VEC_INSERT(res, addressPage);
  VEC_INSERT(res, param);
  VEC_INSERT(res, val);
  VEC_INSERT(res, sEox);
  return res;
}

ByteArray SysExBase::createValueAsStringGetCmd(const ByteArray& addressPage, const ByteArray& param, unsigned short rawVal)
{
  return createValueAsStringGetCmd(addressPage, param, packRawVal(rawVal));
}

// extended parameter
ByteArray SysExBase::createExtParamGetCmd(const ByteArray& param)
{
  ByteArray res;
  VEC_INSERT(res, sHeader);
  VEC_INSERT(res, sReqExtParam);
  VEC_INSERT(res, param);
  VEC_INSERT(res, sEox);
  return res;
}

ByteArray SysExBase::createExtParamSetCmd(const ByteArray& param, const ByteArray& val)
{
  ByteArray res;
  VEC_INSERT(res, sHeader);
  VEC_INSERT(res, sExtParamChange);
  VEC_INSERT(res, param);
  VEC_INSERT(res, val);
  VEC_INSERT(res, sEox);
  return res;
}

ByteArray SysExBase::createExtParamGetCmd(unsigned int param)
{
  return createExtParamGetCmd(packRawVal(param));
}

ByteArray SysExBase::createExtParamSetCmd(unsigned int param, unsigned int val)
{
  return createExtParamSetCmd(packRawVal(param), packRawVal(val));
}


// extended string parameter
ByteArray SysExBase::createExtStringParamGetCmd(const ByteArray& param)
{
  ByteArray res;
  VEC_INSERT(res, sHeader);
  VEC_INSERT(res, sReqExtStringParam);
  VEC_INSERT(res, param);
  VEC_INSERT(res, sEox);
  return res;
}

ByteArray SysExBase::createExtStringParamGetCmd(unsigned int param)
{
return createExtStringParamGetCmd(packRawVal(param));
}

// reserved functions
ByteArray SysExBase::createReservedFct7E(const ByteArray& addressPage, const ByteArray& param, const ByteArray& val)
{
  ByteArray res;
  VEC_INSERT(res, sHeader);
  VEC_INSERT(res, sReservedFct7E);
  VEC_INSERT(res, addressPage);
  VEC_INSERT(res, param);
  VEC_INSERT(res, val);
  VEC_INSERT(res, sEox);
  return res;
}

ByteArray SysExBase::createReservedFct7F(const ByteArray& addressPage, const ByteArray& param, const ByteArray& val)
{
  ByteArray res;
  VEC_INSERT(res, sHeader);
  VEC_INSERT(res, sReservedFct7E);
  VEC_INSERT(res, addressPage);
  VEC_INSERT(res, param);
  VEC_INSERT(res, val);
  VEC_INSERT(res, sEox);
  return res;
}
