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
