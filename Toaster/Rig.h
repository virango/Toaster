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
#ifndef RIG_H
#define RIG_H
#include <QObject>
#include "RigMidi.h"

#define rigObj Rig::get()

class Rig : public QObject, public RigMidi
{
  Q_OBJECT
public:
  static Rig& get();

  void requestAllValues();

signals:
  void tempoReceived(double tempo);
  void volumeReceived(int volume);
  void tempoEnableReceived(bool tempoEnable);
  void stompsEnableReceived(bool stompsEnable);
  void stackEnableReceived(bool stackEnable);
  void effectsEnableReceived(bool effectsEnable);

public slots:
  void applyTempo(double tempo);
  void applyVolume(int volume);
  void applyTempoEnable(bool tempoEnable);
  void applyStompsEnable(bool stompsEnable);
  void applyStackEnable(bool stackEnable);
  void applyEffectsEnable(bool effectsEnable);

protected:
  // RigMidi
  virtual void midiTempoReceived(unsigned short rawVal);
  virtual void midiVolumeReceived(unsigned short rawVal);
  virtual void midiTempoEnableReceived(unsigned short rawVal);
  virtual void midiStompsEnableReceived(unsigned short rawVal);
  virtual void midiStackEnableReceived(unsigned short rawVal);
  virtual void midiEffectsEnableReceived(unsigned short rawVal);

private:
  Rig();
  ~Rig();
};

#endif // RIG_H
