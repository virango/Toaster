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
#include <QString>
#include "VirtualStringParam.h"
#include "VirtualModule.h"

VirtualStringParam::VirtualStringParam(ParamId id, VirtualModule* module)
  : VirtualParam(id, module)
  , mValue("")
  , mIsTagParam(false)
{

}


bool VirtualStringParam::load(const ByteArray& buf)
{
  bool rc = false;
  if(buf.size() >= 9)
  {
    mValue = QString::fromLatin1((const char*)buf.mid(9).data());
    rc = true;
  }

  return rc;
}

void VirtualStringParam::setValue(const ByteArray& cmd)
{

}

ByteArray VirtualStringParam::createResponse(bool includeLen)
{
  ByteArray response;
  if(mModule != nullptr)
  {
    ByteArray ap(1, mModule->getAddressPage());
    ByteArray param(1, (unsigned char) mId);
    response = createStringParamSetCmd(ap, param, mValue, includeLen);
  }
  return response;
}

ByteArray VirtualStringParam::createResponse(const ByteArray&, bool includeLen)
{
  return createResponse(includeLen);
}

