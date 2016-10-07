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
#ifndef VIRTUALRIG_H
#define VIRTUALRIG_H
#include <qglobal.h>
#include <QMap>
#include "VirtualModule.h"

class QDataStream;

class VirtualRig
{
public:
  VirtualRig(const QString& path, const ByteArray& magic);

  bool load(QDataStream& stream, qint64 fileSize);

  unsigned short createKIPR(ByteArray& outBlob) const;

  ByteArray midiIn(const ByteArray& msg);

  const QString& getFilePath() const { return mFilePath; }

  const QString& getRigName();

private:
  typedef QMap<AddressPage, VirtualModule*> ModuleMap;
  typedef QList<VirtualParam*> ParamList;

  QString   mFilePath;

  ByteArray mMagic;
  ByteArray mHeader;

  ModuleMap mModules;
  ParamList mParams;
};

#endif // VIRTUALRIG_H
