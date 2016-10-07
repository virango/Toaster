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
#include <QVector>
#include "Utils.h"
#include "VirtualMultiParam.h"
#include "VirtualModule.h"

VirtualMultiParam::VirtualMultiParam(ParamId id, VirtualModule* module)
  : VirtualParam(id, module)
  , mFirst(-1)
  , mLast(-1)
{
}

bool VirtualMultiParam::load(const ByteArray& buf)
{
  bool rc = false;
  int bufSize = buf.size();

  if(bufSize >= 11)
  {
    int noOfParams = (bufSize - 10) / 2;
    mFirst = buf[8];
    mLast = mFirst + (noOfParams - 1);
    int valIdx = 9;
    while(noOfParams)
    {
      unsigned short val = Utils::extractRawVal(buf[valIdx], buf[valIdx+1]);
      valIdx += 2;
      mValues.push_back(val);
      noOfParams--;
    }
    rc = true;
  }
  return rc;
}

void VirtualMultiParam::setValue(const ByteArray& cmd)
{
  if(cmd.size() >= 13)
  {
    ParamId id = cmd[9];
    int valIdx = id - mFirst;
    if(mValues.size() > valIdx)
    {
      mValues[valIdx] = Utils::extractRawVal(cmd[10], cmd[11]);
    }
  }
}

ByteArray VirtualMultiParam::createResponse(bool includeLen)
{
  ByteArray response;
  if(mModule != nullptr)
  {
    ByteArray ap(1, mModule->getAddressPage());
    ByteArray param(1, (unsigned char) mId);
    response = createMultiParamSetCmd(ap, param, mValues, includeLen);
  }
  return response;
}

ByteArray VirtualMultiParam::createResponse(const ByteArray& request, bool includeLen)
{
  if(request.size() >= 11 && request[6] == 0x41)
  {
    ByteArray response;
    if(mModule != nullptr)
    {
      ParamId id = request[9];
      int valIdx = id - mFirst;
      if(mValues.size() > valIdx)
      {
        unsigned short value = 0;
        value = mValues[valIdx];
        ByteArray ap(1, mModule->getAddressPage());
        ByteArray param(1, (unsigned char) id);
        response = createSingleParamSetCmd(ap, param, value, includeLen);
      }
    }
    return response;
  }
  return createResponse(includeLen);
}
