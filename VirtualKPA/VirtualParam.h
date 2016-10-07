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
#ifndef VIRTUALPARAM_H
#define VIRTUALPARAM_H
#include <QPair>
#include "SysExBase.h"
#include "Commons.h"

typedef unsigned int FunctionCode;
typedef unsigned int ParamId;
typedef QPair<ParamId, ParamId> ParamIdRange;

class VirtualModule;

class VirtualParam : public SysExBase
{
public:
  virtual ~VirtualParam() {}

  virtual FunctionCode getFunctionCode() = 0;
  virtual bool load(const ByteArray& buf) = 0;
  virtual void setValue(const ByteArray& cmd) = 0;
  virtual ByteArray createResponse(bool includeLen = true) = 0;
  virtual ByteArray createResponse(const ByteArray& request, bool includeLen = false) = 0;

  virtual bool isMultiParam() { return false; }
  virtual bool isTagParam() { return false; }
  virtual ParamIdRange getIdRange() { return ParamIdRange(mId, mId); }

protected:
  VirtualParam(ParamId id, VirtualModule* module);

protected:
  ParamId mId;
  VirtualModule* mModule;
};

#endif // VIRTUALPARAM_H
