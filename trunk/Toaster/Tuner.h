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
#ifndef TUNER_H
#define TUNER_H
#include "TunerMidi.h"

class Tuner : public QObject, public TunerMidi
{
  Q_OBJECT
public:
  explicit Tuner(QObject *parent = 0);

  void requestMuteSignal() { midiRequestMuteSignal(); }


signals:
  void noteReceived(QString note, QString octave);
  void muteSignalReceived(bool muteSignal);

public slots:
  void applyMuteSignal(bool muteSignal) { midiApplyMuteSignal(muteSignal ? 1 : 0); }

protected:
  virtual void midiNoteReceived(unsigned short rawVal);
  virtual void midiMuteSignalReceived(unsigned short rawVal);
};

#endif // TUNER_H
