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
#ifndef CAB_H
#define CAB_H
#include <QObject>
#include "CabMidi.h"

#define cabObj Cab::get()

class Cab : public QObject, public CabMidi
{
  Q_OBJECT
public:
  static Cab& get();

  void requestAllValues();
  void requestOnOff() { midiRequestOnOff(); }
  void requestVolume() { midiRequestVolume(); }
  void requestHighShift() { midiRequestHighShift(); }
  void requestLowShift() { midiRequestLowShift(); }
  void requestCharacter() { midiRequestCharacter(); }
  
signals:
  void onOffReceived(bool onOff);
  void volumeReceived(double volume);
  void highShiftReceived(double highShift);
  void lowShiftReceived(double lowShift);
  void characterReceived(double character);

public slots:
  void applyOnOff(bool onOff);
  void applyVolume(double volume);
  void applyHighShift(double highShift);
  void applyLowShift(double lowShift);
  void applyCharacter(double character);

protected:
  // CabMidi
  void midiOnOffReceived(unsigned short rawVal);
  void midiVolumeReceived(unsigned short rawVal);
  void midiHighShiftReceived(unsigned short rawVal);
  void midiLowShiftReceived(unsigned short rawVal);
  void midiCharacterReceived(unsigned short rawVal);

private:
  Cab();
  ~Cab();
};

#endif // CAB_H
