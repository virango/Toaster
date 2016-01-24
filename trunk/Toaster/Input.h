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
#ifndef INPUT_H
#define INPUT_H

#include <QObject>
#include "InputMidi.h"

class Input : public QObject, public InputMidi
{
  Q_OBJECT
public:
  Input();
  ~Input();


  void requestAllValues();

signals:
  void noiseGateReceived(double noiseGate);
  void cleanSenseReceived(double cleanSense);
  void distortionSenseReceived(double distortionSense);

public slots:
  void applyNoiseGate(double noiseGate);
  void applyCleanSense(double cleanSense);
  void applyDistortionSense(double cleanSense);

protected:
  // InputMidi
  virtual void midiNoiseGateReceived(unsigned short rawVal);
  virtual void midiCleanSenseReceived(unsigned short rawVal);
  virtual void midiDistortionSenseReceived(unsigned short rawVal);
};

#endif // INPUT_H
