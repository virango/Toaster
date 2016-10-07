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
#ifndef VIRTUALKPA_H
#define VIRTUALKPA_H
#include "virtualkpa_global.h"
#include "VirtualRig.h"
#include "MidiConsumer.h"


class VIRTUALKPASHARED_EXPORT VirtualKPA
{
public:
  static VirtualKPA& get();

  VirtualRig* loadRig(const QString& rigFilePath);
  VirtualRig* getCurrentRig() { return mCurrentRig; }

  unsigned short loadRig(const QString& rigFileName, ByteArray& blob);

  void saveRig(const VirtualRig& rig);
  void saveRig(const VirtualRig& rig, const QString& rigName);
  void closeRig(const QString& rigName);

  void midiIn(const ByteArray& msg);

  void addMidiConsumer(IMidiConsumer* consumer);
  void removeMidiConsumer(IMidiConsumer* consumer);

private:
  VirtualKPA();

  void midiOut(const ByteArray& msg);

  typedef QMap<QString, VirtualRig*> RigMap;

  RigMap mRigMap;

  VirtualRig* mCurrentRig = nullptr;

  QList<IMidiConsumer*> mMidiConsumer;

  static const ByteArray sKiprMagic1;
  static const ByteArray sKiprMagic2;
};

#endif // VIRTUALKPA_H
