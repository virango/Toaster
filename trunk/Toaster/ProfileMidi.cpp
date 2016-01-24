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
#include "ProfileMidi.h"
#include "Midi.h"

BYTEARRAYDEF(ProfileMidi, AddressPage,        0x00)
// parameter
BYTEARRAYDEF(ProfileMidi, RigName,            0x01)
BYTEARRAYDEF(ProfileMidi, RigAuthor,          0x02)
BYTEARRAYDEF(ProfileMidi, RigDateTime,        0x03)
BYTEARRAYDEF(ProfileMidi, RigComment,         0x04)
BYTEARRAYDEF(ProfileMidi, AmpName,            0x10)
BYTEARRAYDEF(ProfileMidi, AmpAuthor,          0x11)
BYTEARRAYDEF(ProfileMidi, AmpDate,            0x12)
BYTEARRAYDEF(ProfileMidi, AmpTime,            0x13)
BYTEARRAYDEF(ProfileMidi, CabName,            0x20)
// commands
BYTEARRAYDEF(ProfileMidi, RigNext,            0x30)
BYTEARRAYDEF(ProfileMidi, RigPrev,            0x31)


ProfileMidi::ProfileMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

ProfileMidi::~ProfileMidi()
{
}

// ISysExConsumer
void ProfileMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    QString strVal = extractString(ByteArray(msg->begin() + 10, msg->end()));
    const char param = msg->at(9);
    if(param == sRigName[0])
      midiRigNameReceived(strVal);
    else if(param == sRigAuthor[0])
      midiRigAuthorReceived(strVal);
    else if(param == sRigDateTime[0])
      midiRigDateTimeReceived(strVal);
    else if(param == sRigComment[0])
      midiRigDateTimeReceived(strVal);
    else if(param == sAmpName[0])
      midiAmpNameReceived(strVal);
    else if(param == sAmpAuthor[0])
      midiAmpAuthorReceived(strVal);
    else if(param == sAmpDate[0])
      midiAmpDateReceived(strVal);
    else if(param == sAmpTime[0])
      midiAmpTimeReceived(strVal);
    else if(param == sCabName[0])
      midiCabNameReceived(strVal);
  }
}

unsigned char ProfileMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}


void ProfileMidi::midiRequestRigName()
{
  Midi::get().sendCmd(createStringParamGetCmd(getAddressPage(), sRigName));
}

void ProfileMidi::midiApplyRigName(const QString& rigName)
{
  Midi::get().sendCmd(createStringParamSetCmd(getAddressPage(), sRigName, rigName));
}

void ProfileMidi::midiRequestRigAuthor()
{
  Midi::get().sendCmd(createStringParamGetCmd(getAddressPage(), sRigAuthor));
}

void ProfileMidi::midiApplyRigAuthor(const QString& rigAuthor)
{
  Midi::get().sendCmd(createStringParamSetCmd(getAddressPage(), sRigAuthor, rigAuthor));
}

void ProfileMidi::midiRequestRigDateTime()
{
  Midi::get().sendCmd(createStringParamGetCmd(getAddressPage(), sRigDateTime));
}

void ProfileMidi::midiApplyRigDateTime(const QString& rigDateTime)
{
  Midi::get().sendCmd(createStringParamSetCmd(getAddressPage(), sRigDateTime, rigDateTime));
}

void ProfileMidi::midiRequestRigComment()
{
  Midi::get().sendCmd(createStringParamGetCmd(getAddressPage(), sRigComment));
}

void ProfileMidi::midiApplyRigComment(const QString& rigComment)
{
  Midi::get().sendCmd(createStringParamSetCmd(getAddressPage(), sRigComment, rigComment));
}

void ProfileMidi::midiRequestAmpName()
{
  Midi::get().sendCmd(createStringParamGetCmd(getAddressPage(), sAmpName));
}

void ProfileMidi::midiApplyAmpName(const QString& ampName)
{
  Midi::get().sendCmd(createStringParamSetCmd(getAddressPage(), sAmpName, ampName));
}

void ProfileMidi::midiRequestAmpAuthor()
{
  Midi::get().sendCmd(createStringParamGetCmd(getAddressPage(), sAmpAuthor));
}

void ProfileMidi::midiApplyAmpAuthor(const QString& ampAuthor)
{
  Midi::get().sendCmd(createStringParamSetCmd(getAddressPage(), sAmpAuthor, ampAuthor));
}

void ProfileMidi::midiRequestAmpDate()
{
  Midi::get().sendCmd(createStringParamGetCmd(getAddressPage(), sAmpDate));
}

void ProfileMidi::midiApplyAmpDate(const QString& ampDate)
{
  Midi::get().sendCmd(createStringParamSetCmd(getAddressPage(), sAmpDate, ampDate));
}

void ProfileMidi::midiRequestAmpTime()
{
  Midi::get().sendCmd(createStringParamGetCmd(getAddressPage(), sAmpTime));
}

void ProfileMidi::midiApplyAmpTime(const QString& ampTime)
{
  Midi::get().sendCmd(createStringParamSetCmd(getAddressPage(), sAmpTime, ampTime));
}

void ProfileMidi::midiRequestCabName()
{
  Midi::get().sendCmd(createStringParamGetCmd(getAddressPage(), sCabName));
}

void ProfileMidi::midiApplyCabName(const QString& cabName)
{
  Midi::get().sendCmd(createStringParamSetCmd(getAddressPage(), sCabName, cabName));
}

void ProfileMidi::midiApplyRigPrev()
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sRigPrev, 0));
}

void ProfileMidi::midiApplyRigNext()
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sRigNext, 0));
}


ByteArray ProfileMidi::getAddressPage()
{
  return sAddressPage;
}
