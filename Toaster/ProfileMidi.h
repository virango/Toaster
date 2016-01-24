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
#ifndef PROFILEMIDI_H
#define PROFILEMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class ProfileMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(RigName)
  BYTEARRAYDECL(RigAuthor)
  BYTEARRAYDECL(RigDateTime)
  BYTEARRAYDECL(RigComment)
  BYTEARRAYDECL(AmpName)
  BYTEARRAYDECL(AmpAuthor)
  BYTEARRAYDECL(AmpDate)
  BYTEARRAYDECL(AmpTime)
  BYTEARRAYDECL(CabName)
  // commands
  BYTEARRAYDECL(RigPrev)
  BYTEARRAYDECL(RigNext)

  ProfileMidi();
  ~ProfileMidi();

  // ISysExConsumer
  void consumeSysExMsg(ByteArray* msg);
  unsigned char getId();

  // parameter
  // RigName
  void midiRequestRigName();
  void midiApplyRigName(const QString& rigName);
  // RigAuthor
  void midiRequestRigAuthor();
  void midiApplyRigAuthor(const QString& rigAuthor);
  // RigDateTime
  void midiRequestRigDateTime();
  void midiApplyRigDateTime(const QString& rigDateTime);
  // RigComment
  void midiRequestRigComment();
  void midiApplyRigComment(const QString& rigComment);
  // AmpName
  void midiRequestAmpName();
  void midiApplyAmpName(const QString& ampName);
  // AmpAuthor
  void midiRequestAmpAuthor();
  void midiApplyAmpAuthor(const QString& ampAuthor);
  // AmpDate
  void midiRequestAmpDate();
  void midiApplyAmpDate(const QString& ampDate);
  // AmpTime
  void midiRequestAmpTime();
  void midiApplyAmpTime(const QString& ampTime);
  // CabName
  void midiRequestCabName();
  void midiApplyCabName(const QString& cabName);

  // commands
  // RigPrev
  void midiApplyRigPrev();
  // RigNext
  void midiApplyRigNext();


  virtual void midiRigNameReceived(const QString& rigName) = 0;
  virtual void midiRigAuthorReceived(const QString& rigAuthor) = 0;
  virtual void midiRigDateTimeReceived(const QString& rigDateTime) = 0;
  virtual void midiRigCommentReceived(const QString& rigComment) = 0;
  virtual void midiAmpNameReceived(const QString& ampName) = 0;
  virtual void midiAmpAuthorReceived(const QString& ampAuthor) = 0;
  virtual void midiAmpDateReceived(const QString& ampDate) = 0;
  virtual void midiAmpTimeReceived(const QString& ampTime) = 0;
  virtual void midiCabNameReceived(const QString& cabName) = 0;

  // utility methods
  ByteArray getAddressPage();
};

#endif // PROFILEMIDI_H
