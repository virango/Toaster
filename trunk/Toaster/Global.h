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
  void applyWahPedalToPitchReceived(bool onOff);
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
  virtual void midiWahPedalToPitchReceived(unsigned short rawVal);
  virtual void midiOperationModeReceived(unsigned short rawVal);

  void launchBeacon();

protected slots:
  void sendBeacon();

private:
  QTimer* mBeaconTimer;
};

#endif // GLOBAL_H
