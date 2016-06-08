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
#ifndef REVERB_H
#define REVERB_H

#include <QObject>
#include "ReverbMidi.h"

#define reverbObj Reverb::get()

class Reverb : public QObject, public ReverbMidi
{
  Q_OBJECT
public:
  static Reverb& get();

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

  ::ReverbType getReverbType() const { return mReverbType; }

signals:
  void typeReceived(::ReverbType type);
  void onOffCutsTailReceived(bool onOff);
  void mixReceived(int mix);
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
  void applyMix(int mix);
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

  ReverbType mReverbType;

private:
  Reverb();
  ~Reverb();
};

#endif // REVERB_H
