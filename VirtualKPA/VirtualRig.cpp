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
#include <string.h>
#include <QDataStream>
#include "VirtualRig.h"

VirtualRig::VirtualRig(const QString& path, const ByteArray& magic)
  : mFilePath(path)
  , mMagic(magic)
  , mHeader(14, 0x00)
{
}

bool VirtualRig::load(QDataStream& stream, qint64 fileSize)
{
  bool rc = false;
  stream.readRawData((char*)mHeader.data(), mHeader.size());
  unsigned int bytesInFile;
  stream.setByteOrder(QDataStream::BigEndian);
  stream >> bytesInFile;
  bytesInFile += 22;   // 4 byte magic + 14 byte header + 4 byte length

  if(bytesInFile == fileSize)
  {
    while(!stream.atEnd())
    {
      unsigned char c;
      stream.readRawData((char*)&c, 1);
      if(c == 0xF0)
      {
        unsigned short  len = 0;
        stream.readRawData((char*)&c, 1);
        if((c & 0x80) != 0)
        {
          len = (((unsigned short)c & 0x7F) << 7);
          stream.readRawData((char*)&c, 1);
          len = len | ((unsigned short)c & 0x7F);
        }
        else
        {
          len = c;
        }

        ByteArray buf(len, 0);
        stream.readRawData((char*)buf.data(), len);
        AddressPage moduleId = VirtualModule::extractAddressPage(buf);
        ModuleMap::iterator it = mModules.find(moduleId);
        VirtualModule* module = nullptr;
        if(it != mModules.end())
        {
          module = it->second.get();
        }
        else
        {
          module = new VirtualModule(moduleId);
          mModules[moduleId].reset(module);
        }

        VirtualParam* param = module->load(buf);

        if(param == nullptr)
        {
          break;
        }
        else
        {
          mParams.append(param);
        }

      }
    }

    if(stream.atEnd())
      rc = true;
  }

  return rc;
}

unsigned short VirtualRig::createKIPR(ByteArray& outBlob) const
{
  outBlob.clear();
  outBlob.append(mMagic);
  outBlob.append(mHeader);
  ByteArray sysexData;
  for(VirtualParam* param : mParams)
  {
    sysexData.append(0x00);
    sysexData.append(param->createResponse(true));
  }

  unsigned int len = sysexData.size();
  outBlob.append((len>>24) & 0xFF);
  outBlob.append((len>>16) & 0xFF);
  outBlob.append((len>>8)  & 0xFF);
  outBlob.append(len & 0xFF);
  outBlob.append(sysexData);

  return Utils::crc14(outBlob);
}

ByteArray VirtualRig::midiIn(const ByteArray& msg)
{
  if(msg.size() >= 11)
  {
    AddressPage ap = VirtualModule::extractAddressPage(msg.mid(1));
    auto it = mModules.find(ap);
    if(it != mModules.end())
    {
      VirtualModule* module = it->second.get();
      return module->midiIn(msg);
    }
  }

  return ByteArray();
}

const QString& VirtualRig::getRigName()
{

}

