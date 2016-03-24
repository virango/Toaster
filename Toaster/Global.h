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
#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include "GlobalMidi.h"

class QTimer;

class Global : public QObject, public GlobalMidi
{
  Q_OBJECT
public:
  Global();
  ~Global();

  enum OperationMode
  {
    Off = 0,
    Tuner = 1,
    Browser = 2,
    Perform = 3,
    Profiler = 4
  };

  void requestAllValues();
  void requestWahPedalToPitch() { midiRequestWahPedalToPitch(); }
  void requestMasterTune() { midiRequestMasterTune(); }

  void requestMainOutputSource() { midiRequestMainOutputSource(); }
  void requestMonitorOutputSource() { midiRequestMonitorOutputSource(); }
  void requestDirectOutputSource() { midiRequestDirectOutputSource(); }
  void requestSPDIFOutputSource() { midiRequestSPDIFOutputSource(); }

signals:
  void mainOutputVolumeReceived(int volume);
  void headphoneOutputVolumeReceived(int volume);
  void monitorOutputVolumeReceived(int volume);
  void directOutputVolumeReceived(int volume);
  void masterTuneReceived(double masterTune);
  void spdifInputEnableReceived(bool enabled);
  void mainOutputEQBassReceived(double bass);
  void mainOutputEQMiddleReceived(double middle);
  void mainOutputEQTrebleReceived(double treble);
  void mainOutputEQPresenceReceived(double presence);
  void monitorOutputEQBassReceived(double bass);
  void monitorOutputEQMiddleReceived(double middle);
  void monitorOutputEQTrebleReceived(double treble);
  void monitorOutputEQPresenceReceived(double presence);
  void mainOutputSourceReceived(int source);
  void spdifOutputSourceReceived(int source);
  void monitorOutputSourceReceived(int source);
  void directOutputSourceReceived(int source);
  void wahPedalToPitchReceived(bool onOff);
  void operationModeReceived(unsigned short);

public slots:
  void applyMainOutputVolume(int volume);
  void applyHeadphoneOutputVolume(int volume);
  void applyMonitorOutputVolume(int volume);
  void applyDirectOutputVolume(int volume);
  void applyMasterTune(double masterTune);
  void applySpdifInputEnable(bool enabled);
  void applyMainOutputEQBass(double bass);
  void applyMainOutputEQMiddle(double middle);
  void applyMainOutputEQTreble(double treble);
  void applyMainOutputEQPresence(double presence);
  void applyMonitorOutputEQBass(double bass);
  void applyMonitorOutputEQMiddle(double middle);
  void applyMonitorOutputEQTreble(double treble);
  void applyMonitorOutputEQPresence(double presence);
  void applyMainOutputSource(int source);
  void applySpdifOutputSource(int source);
  void applyMonitorOutputSource(int source);
  void applyDirectOutputSource(int source);
  void applyWahPedalToPitch(bool onOff);
  void applyOperationMode(Global::OperationMode opMode);

  void connect2KPA(const QString& connectName);
  void disconnectFromKPA();

protected:
  // GlobalMidi
  virtual void midiMainOutputVolumeReceived(unsigned short rawVal);
  virtual void midiHeadphoneOutputVolumeReceived(unsigned short rawVal);
  virtual void midiMonitorOutputVolumeReceived(unsigned short rawVal);
  virtual void midiDirectOutputVolumeReceived(unsigned short rawVal);
  virtual void midiMasterTuneReceived(unsigned short rawVal);
  virtual void midiSPDIFInputEnableReceived(unsigned short rawVal);
  virtual void midiMainOutputEQBassReceived(unsigned short rawVal);
  virtual void midiMainOutputEQMiddleReceived(unsigned short rawVal);
  virtual void midiMainOutputEQTrebleReceived(unsigned short rawVal);
  virtual void midiMainOutputEQPresenceReceived(unsigned short rawVal);
  virtual void midiMonitorOutputEQBassReceived(unsigned short rawVal);
  virtual void midiMonitorOutputEQMiddleReceived(unsigned short rawVal);
  virtual void midiMonitorOutputEQTrebleReceived(unsigned short rawVal);
  virtual void midiMonitorOutputEQPresenceReceived(unsigned short rawVal);
  virtual void midiMainOutputSourceReceived(unsigned short rawVal);
  virtual void midiSPDIFOutputSourceReceived(unsigned short rawVal);
  virtual void midiMonitorOutputSourceReceived(unsigned short rawVal);
  virtual void midiDirectOutputSourceReceived(unsigned short rawVal);
  virtual void midiWahPedalToPitchReceived(unsigned short rawVal);
  virtual void midiOperationModeReceived(unsigned short rawVal);

  void launchBeacon();

protected slots:
  void sendBeacon();

private:
  QTimer* mBeaconTimer;
};

#endif // GLOBAL_H
