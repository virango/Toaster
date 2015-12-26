#ifndef REVERB_H
#define REVERB_H

#include <QObject>
#include "ReverbMidi.h"

class Reverb : public QObject, public ReverbMidi
{
  Q_OBJECT
public:
  Reverb();
  ~Reverb();

  void requestAllValues();
  void requestType() { midiRequestType(); }
  void requestOnOffCutsTail() { midiRequestOnOffCutsTail(); }
  void requestMix() { midiRequestMix(); }
  void requestVolume() {midiRequestVolume(); }
  void requestDelRevBalance() { midiRequestDelRevBalance(); }
  void requestTime() { midiRequestTime(); }
  void requestDamping() { midiRequestDamping(); }
  void requestBandwidth() { midiRequestBandwidth(); }
  void requestCenterFrequency() { midiRequestCenterFrequency(); }
  void requestPreDelay() { midiRequestPreDelay(); }
  void requestOnOffKeepsTail() { midiRequestOnOffKeepsTail(); }
  void requestDucking() { midiRequestDucking(); }

signals:
  void typeReceived(::ReverbType type);
  void onOffCutsTailReceived(bool onOff);
  void mixReceived(double mix);
  void volumeReceived(double volume);
  void delRevBalanceReceived(double balance);
  void timeReceived(double time);
  void dampingReceived(double damping);
  void bandwidthReceived(double bandwidth);
  void centerFrequencyReceived(double frequency);
  void preDelayReceived(double preDelay);
  void onOffKeepsTailReceived(bool onOff);
  void duckingReceived(double ducking);

public slots:
  void applyType(::ReverbType type);
  void applyOnOffCutsTail(bool onOff);
  void applyMix(double mix);
  void applyVolume(double volume);
  void applyDelRevBalance(double balance);
  void applyTime(double time);
  void applyDamping(double damping);
  void applyBandwidth(double bandwidth);
  void applyCenterFrequency(double frequency);
  void applyPreDelay(double preDelay);
  void applyOnOffKeepsTail(bool onOff);
  void applyDucking(double ducking);

protected:
  // ReverbMidi
  virtual void midiTypeReceived(unsigned short rawVal);
  virtual void midiOnOffCutsTailReceived(unsigned short rawVal);
  virtual void midiMixReceived(unsigned short rawVal);
  virtual void midiVolumeReceived(unsigned short rawVal);
  virtual void midiDelRevBalanceReceived(unsigned short rawVal);
  virtual void midiTimeReceived(unsigned short rawVal);
  virtual void midiDampingReceived(unsigned short rawVal);
  virtual void midiBandwidthReceived(unsigned short rawVal);
  virtual void midiCenterFrequencyReceived(unsigned short rawVal);
  virtual void midiPreDelayReceived(unsigned short rawVal);
  virtual void midiOnOffKeepsTailReceived(unsigned short rawVal);
  virtual void midiDuckingReceived(unsigned short rawVal);
};

#endif // REVERB_H
