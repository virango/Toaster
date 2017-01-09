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
#include <QFile>
#include <QDataStream>
#include "VirtualKPA.h"
#include "Utils.h"

const ByteArray VirtualKPA::sKiprMagic1 = {0x49,0x54,0x68,0x64};
const ByteArray VirtualKPA::sKiprMagic2 = {0x4b,0x54,0x68,0x64};

VirtualKPA::VirtualKPA()
{
}

VirtualKPA& VirtualKPA::get()
{
  static VirtualKPA vk;
  return vk;
}

VirtualRig* VirtualKPA::loadRig(const QString& rigFilePath)
{
  QFile kiprFile(rigFilePath);

  VirtualRig* newRig = nullptr;

  kiprFile.open(QIODevice::ReadOnly);
  QDataStream stream(&kiprFile);
  qint64 fileSize = kiprFile.bytesAvailable();
  ByteArray magic(4,0x00);
  stream.readRawData((char*)magic.data(), 4);
  if(magic == sKiprMagic1 || magic == sKiprMagic2)
  {
    newRig = new VirtualRig(rigFilePath, magic);
    if(!newRig->load(stream, fileSize))
    {
      delete newRig;
      newRig = nullptr;
    }
  }

  mCurrentRig.reset(newRig);

  return newRig;
}

unsigned short VirtualKPA::loadRig(const QString& rigFileName, ByteArray& blob)
{
  QFile kiprFile(rigFileName);

  kiprFile.open(QIODevice::ReadOnly);
  QDataStream stream(&kiprFile);
  int magicSize = sizeof(sKiprMagic1);
  ByteArray magic(magicSize, 0);
  stream.readRawData((char*)magic.data(), magicSize);

  if(magic == sKiprMagic1 || magic == sKiprMagic2)
  {
    qint64 fileSize = kiprFile.bytesAvailable();
    blob.reserve(fileSize + magicSize);
    blob.append(magic);
    stream.readRawData((char*) blob.data()+magicSize, fileSize);
  }

  return Utils::crc14(blob);
}

void VirtualKPA::saveRig(const VirtualRig& rig, const QString& rigName)
{
  ByteArray kiprBlob;
  rig.createKIPR(kiprBlob);
  QFile kiprFile(rigName);
  kiprFile.open(QIODevice::WriteOnly);
  QDataStream stream(&kiprFile);
  stream.writeRawData((char*)kiprBlob.data(), kiprBlob.size());
}

void VirtualKPA::midiIn(const ByteArray& msg)
{
  if(mCurrentRig)
  {
    midiOut(mCurrentRig->midiIn(msg));
  }
}

void VirtualKPA::midiOut(const ByteArray& msg)
{
  if(msg.size() > 0)
  {
    for(IMidiConsumer* consumer : mMidiConsumer)
    {
      if(msg[0] == consumer->getStatusByte())
        consumer->consume(msg);
    }
  }
}

void VirtualKPA::addMidiConsumer(IMidiConsumer* consumer)
{
  if(consumer)
    mMidiConsumer.push_back(consumer);
}

void VirtualKPA::removeMidiConsumer(IMidiConsumer* consumer)
{
  mMidiConsumer.removeOne(consumer);
}
