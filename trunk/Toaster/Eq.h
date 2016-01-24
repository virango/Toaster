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
#ifndef EQ_H
#define EQ_H
#include <QObject>
#include "EqMidi.h"

class Eq : public QObject, public EqMidi
{
  Q_OBJECT
public:
  Eq();
  ~Eq();

  void requestAllValues();

signals:
  void onOffReceived(bool onOff);
  void bassReceived(double bass);
  void middleReceived(double middle);
  void trebleReceived(double treble);
  void presenceReceived(double presence);

public slots:
  void applyOnOff(bool onOff);
  void applyBass(double bass);
  void applyMiddle(double middle);
  void applyTreble(double treble);
  void applyPresence(double presence);

protected:
  // EqMidi
  virtual void midiOnOffReceived(unsigned short rawVal);
  virtual void midiBassReceived(unsigned short rawVal);
  virtual void midiMiddleReceived(unsigned short rawVal);
  virtual void midiTrebleReceived(unsigned short rawVal);
  virtual void midiPresenceReceived(unsigned short rawVal);
};

#endif // EQ_H
