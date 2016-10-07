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
#include "VirtualBlobParam.h"
#include "VirtualModule.h"

VirtualBlobParam::VirtualBlobParam(ParamId id, VirtualModule* module)
  : VirtualParam(id, module)
{
}

bool VirtualBlobParam::load(const ByteArray& buf)
{
  bool rc = false;
  int bufSize = buf.size();

  mBlob.clear();
  if(bufSize >= 15)
  {
    mBlob.append(buf.mid(9));
    mBlob.pop_back();
    rc = true;
  }

  return rc;
}

void VirtualBlobParam::setValue(const ByteArray& cmd)
{

}

ByteArray VirtualBlobParam::createResponse(bool includeLen)
{
  ByteArray response;
  if(mModule != nullptr)
  {
    ByteArray ap(1, mModule->getAddressPage());
    ByteArray param(1, (unsigned char) mId);
    response = createBlobParamSetCmd(ap, param, mBlob, includeLen);
  }
  return response;
}

ByteArray VirtualBlobParam::createResponse(const ByteArray&, bool includeLen)
{
  return createResponse(includeLen);
}
