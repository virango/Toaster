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
#include "VirtualUnknownParam.h"
#include "VirtualModule.h"

VirtualUnknownParam::VirtualUnknownParam(FunctionCode type, ParamId id, VirtualModule* module)
  : VirtualParam(id, module)
  , mType(type)
{

}

bool VirtualUnknownParam::load(const ByteArray& buf)
{
  bool rc = false;
  int bufSize = buf.size();

  if(bufSize >= 13)
  {
    unsigned short len = bufSize - 12;
    for(unsigned short i = 0; i < len; ++i)
      mBlob.push_back(buf[10+i]);

    rc = true;
  }

  return rc;
}

void VirtualUnknownParam::setValue(const ByteArray& cmd)
{

}

ByteArray VirtualUnknownParam::createResponse(bool includeLen)
{
  ByteArray response;
  if(mModule != nullptr)
  {
    ByteArray func;
    func.append((unsigned char) mType);
    func.append(0x00);
    ByteArray ap(1, mModule->getAddressPage());
    ByteArray param(1, (unsigned char) mId);
    response = createParamSetCmd(func, ap, param, mBlob, includeLen);
  }
  return response;
}

ByteArray VirtualUnknownParam::createResponse(const ByteArray&, bool includeLen)
{
  return createResponse(includeLen);
}
