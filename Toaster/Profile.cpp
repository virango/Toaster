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
#include "Profile.h"

Profile::Profile(QObject *parent) : QObject(parent)
{

}

Profile::~Profile()
{

}

void Profile::requestAllValues()
{
  midiRequestRigName();
  midiRequestRigAuthor();
  midiRequestRigDateTime();
  midiRequestRigComment();
  midiRequestAmpName();
  midiRequestAmpAuthor();
  midiRequestAmpDate();
  midiRequestAmpTime();
  midiRequestCabName();
}

void Profile::applyRigName(const QString& rigName)
{
  midiApplyRigName(rigName);
}

void Profile::applyRigAuthor(const QString& rigAuthor)
{
  midiApplyRigAuthor(rigAuthor);
}

void Profile::applyRigDateTime(const QString& rigDateTime)
{
  midiApplyRigDateTime(rigDateTime);
}

void Profile::applyRigComment(const QString& rigComment)
{
  midiApplyRigComment(rigComment);
}

void Profile::applyAmpName(const QString& ampName)
{
  midiApplyAmpName(ampName);
}

void Profile::applyAmpAuthor(const QString& ampAuthor)
{
  midiApplyAmpAuthor(ampAuthor);
}

void Profile::applyAmpDate(const QString& ampDate)
{
  midiApplyAmpDate(ampDate);
}

void Profile::applyAmpTime(const QString& ampTime)
{
  midiApplyAmpTime(ampTime);
}

void Profile::applyCabName(const QString& cabName)
{
  midiApplyCabName(cabName);
}

void Profile::applyRigPrev()
{
  midiApplyRigPrev();
}

void Profile::applyRigNext()
{
  midiApplyRigNext();
}

void Profile::midiRigNameReceived(const QString& rigName)
{
  emit rigNameReceived(rigName);
}

void Profile::midiRigAuthorReceived(const QString& rigAuthor)
{
  emit rigAuthorReceived(rigAuthor);
}

void Profile::midiRigDateTimeReceived(const QString& rigDateTime)
{
  emit rigDateTimeReceived(rigDateTime);
}

void Profile::midiRigCommentReceived(const QString& rigComment)
{
  emit rigCommentReceived(rigComment);
}

void Profile::midiAmpNameReceived(const QString& ampName)
{
  emit ampNameReceived(ampName);
}

void Profile::midiAmpAuthorReceived(const QString& ampAuthor)
{
  emit ampAuthorReceived(ampAuthor);
}

void Profile::midiAmpDateReceived(const QString& ampDate)
{
  emit ampDateReceived(ampDate);
}

void Profile::midiAmpTimeReceived(const QString& ampTime)
{
  emit ampTimeReceived(ampTime);
}

void Profile::midiCabNameReceived(const QString& cabName)
{
  emit cabNameReceived(cabName);
}
