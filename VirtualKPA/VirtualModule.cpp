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
#include "VirtualModule.h"
#include "VirtualSingleParam.h"
#include "VirtualMultiParam.h"
#include "VirtualStringParam.h"
#include "VirtualBlobParam.h"
#include "VirtualExtendedParam.h"
#include "VirtualUnknownParam.h"
#include "Utils.h"

VirtualModule::VirtualModule(AddressPage ap)
  :mAP(ap)
{
}

VirtualParam* VirtualModule::load(const ByteArray& buf)
{
  VirtualParam* newParam = createParam(buf);

  if(newParam != nullptr)
  {
    if(newParam->load(buf))
    {
      ParamIdRange idRange = newParam->getIdRange();
      for(ParamId it = idRange.first; it <= idRange.second; ++it)
      {
        mParams[it] = newParam;
      }
    }
    else
    {
      delete newParam;
      newParam = nullptr;
    }
  }

  return newParam;
}

VirtualParam* VirtualModule::createParam(const ByteArray& buf)
{
  VirtualParam* newParam = nullptr;

  if(buf.size() >= 10)
  {
    switch(buf[5])
    {
      case 1:
        newParam = new VirtualSingleParam(buf[8], this);
        break;
      case 2:
        newParam = new VirtualMultiParam(buf[8], this);
        break;
      case 3:
        newParam = new VirtualStringParam(buf[8], this);
        break;
      case 4:
        newParam = new VirtualBlobParam(buf[8], this);
        break;
      case 6:
        newParam = new VirtualExtendedParam(Utils::extractRawVal(buf.mid(7, 5)), this);
        break;
      default:
        newParam = new VirtualUnknownParam(buf[5], buf[8], this);
        break;
    }
  }

  return newParam;
}

ByteArray VirtualModule::midiIn(const ByteArray& msg)
{
  if(msg.size() >= 10)
  {
    ParamId paramId = 0xFFFFFFFF;
    unsigned char paramType = msg[6];
    if(paramType == 0x06 || paramType == 0x46)
      paramId = Utils::extractRawVal(msg.mid(8, 5));
    else
      paramId = msg[9];

    Params::iterator it = mParams.find(paramId);
    if(it != mParams.end())
    {
      VirtualParam* param = (*it);
      if(paramType < 40)
      {
        param->setValue(msg);
      }
      else
      {
        return param->createResponse(msg, false);
      }
    }
  }
  return ByteArray();
}
