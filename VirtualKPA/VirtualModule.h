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
#ifndef VIRTUALMODULE_H
#define VIRTUALMODULE_H
#include <QMap>
#include "VirtualParam.h"

typedef unsigned int AddressPage;

class VirtualModule
{
public:
  VirtualModule(AddressPage ap);

  VirtualParam* load(const ByteArray& buf);

  AddressPage getAddressPage() { return mAP; }

  ByteArray midiIn(const ByteArray& msg);

  static AddressPage extractAddressPage(const ByteArray& buf)
  {
    AddressPage ap = -1;

    if(buf.size() >=12 && buf[5] == 6)
      ap = Utils::extractRawVal(buf.mid(7, 5));
    else if(buf.size() >= 8)
      ap = (AddressPage)buf[7];

    return ap;
  }

private:
  VirtualParam* createParam(const ByteArray& buf);

  AddressPage mAP;

  typedef QMap<ParamId, VirtualParam*> Params;

  Params mParams;
};

#endif // VIRTUALMODULE_H
