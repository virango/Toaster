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
#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include "ProfileMidi.h"

#define profileObj Profile::get()

class Profile : public QObject, public ProfileMidi
{
  Q_OBJECT
public:
  static Profile& get();

  void requestAllValues();
  void requestRigName() { midiRequestRigName(); }
  void requestRigAuthor() { midiRequestRigAuthor(); }
  void requestRigDateTime() { midiRequestRigDateTime(); }
  void requestRigComment() { midiRequestRigComment(); }
  void requestAmpName() { midiRequestAmpName(); }
  void requestAmpAuthor() { midiRequestAmpAuthor(); }
  void requestAmpDate() { midiRequestAmpDate(); }
  void requestAmpTime() { midiRequestAmpTime(); }
  void requestCabName() { midiRequestCabName(); }

signals:
  void rigNameReceived(const QString& rigName);
  void rigAuthorReceived(const QString& rigAuthor);
  void rigDateTimeReceived(const QString& rigDateTime);
  void rigCommentReceived(const QString& rigComment);
  void ampNameReceived(const QString& ampName);
  void ampAuthorReceived(const QString& ampAuthor);
  void ampDateReceived(const QString& ampDate);
  void ampTimeReceived(const QString& ampTime);
  void cabNameReceived(const QString& cabName);

public slots:
  void applyRigName(const QString& rigName);
  void applyRigAuthor(const QString& rigAuthor);
  void applyRigDateTime(const QString& rigDateTime);
  void applyRigComment(const QString& rigComment);
  void applyAmpName(const QString& ampName);
  void applyAmpAuthor(const QString& ampAuthor);
  void applyAmpDate(const QString& ampDate);
  void applyAmpTime(const QString& ampTime);
  void applyCabName(const QString& cabName);
  void applyRigPrev();
  void applyRigNext();

protected:
  virtual void midiRigNameReceived(const QString& rigName);
  virtual void midiRigAuthorReceived(const QString& rigAuthor);
  virtual void midiRigDateTimeReceived(const QString& rigDateTime);
  virtual void midiRigCommentReceived(const QString& rigComment);
  virtual void midiAmpNameReceived(const QString& ampName);
  virtual void midiAmpAuthorReceived(const QString& ampAuthor);
  virtual void midiAmpDateReceived(const QString& ampDate);
  virtual void midiAmpTimeReceived(const QString& ampTime);
  virtual void midiCabNameReceived(const QString& cabName);

private:
  Profile();
  ~Profile();
};

#endif // PROFILE_H
