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
#ifndef DELAY_H
#define DELAY_H
#include <QObject>
#include "DelayMidi.h"

class Delay : public QObject, public DelayMidi
{
  Q_OBJECT
public:
  Delay();
  ~Delay();

  void requestAllValues();
  void requestType() { midiRequestType(); }
  void requestOnOffCutsTail() { midiRequestOnOffCutsTail(); }
  void requestMix() { midiRequestMix(); }
  void requestVolume() { midiRequestVolume(); }
  void requestTime() { midiRequestTime(); }
  void requestRatio() { midiRequestRatio(); }
  void requestClockLeft() { midiRequestClockLeft(); }
  void requestClockRight() { midiRequestClockRight(); }
  void requestFeedback() { midiRequestFeedback(); }
  void requestBandwidth() { midiRequestBandwidth(); }
  void requestCenterFrequency() { midiRequestCenterFrequency(); }
  void requestModulation() { midiRequestModulation(); }
  void requestOnOffKeepsTail() { midiRequestOnOffKeepsTail(); }
  void requestDucking() { midiRequestDucking(); }

  ::DelayType getDelayType() const { return mDelayType; }
  
signals:
  void typeReceived(::DelayType type);
  void onOffCutsTailReceived(bool onOffCutsTail);
  void mixReceived(int mix);
  void volumeReceived(double volume);
  void timeReceived(double time);
  void ratioReceived(::DelayRatio ratio);
  void clockLeftReceived(::DelayClock clockLeft);
  void clockRightReceived(::DelayClock clockRight);
  void feedbackReceived(double feedback);
  void bandwidthReceived(double bandwidth);
  void centerFrequencyReceived(double centerFrequency);
  void modulationReceived(double modulation);
  void onOffKeepsTailReceived(bool onOffKeepsTail);
  void duckingReceived(double ducking);

public slots:
  void applyType(::DelayType type);
  void applyOnOffCutsTail(bool onOffCutsTail);
  void applyMix(int mix);
  void applyVolume(double volume);
  void applyTime(double time);
  void applyRatio(::DelayRatio ratio);
  void applyClockLeft(::DelayClock clockLeft);
  void applyClockRight(::DelayClock clockRight);
  void applyFeedback(double feedback);
  void applyBandwidth(double bandwidth);
  void applyCenterFrequency(double centerFrequency);
  void applyModulation(double modulation);
  void applyOnOffKeepsTail(bool onOffKeepsTail);
  void applyDucking(double ducking);

protected:
  // DelayMidi
  virtual void midiTypeReceived(unsigned short rawVal);
  virtual void midiOnOffCutsTailReceived(unsigned short rawVal);
  virtual void midiMixReceived(unsigned short rawVal);
  virtual void midiVolumeReceived(unsigned short rawVal);
  virtual void midiTimeReceived(unsigned short rawVal);
  virtual void midiRatioReceived(unsigned short rawVal);
  virtual void midiClockLeftReceived(unsigned short rawVal);
  virtual void midiClockRightReceived(unsigned short rawVal);
  virtual void midiFeedbackReceived(unsigned short rawVal);
  virtual void midiBandwidthReceived(unsigned short rawVal);
  virtual void midiCenterFrequencyReceived(unsigned short rawVal);
  virtual void midiModulationReceived(unsigned short rawVal);
  virtual void midiOnOffKeepsTailReceived(unsigned short rawVal);
  virtual void midiDuckingReceived(unsigned short rawVal);

  ::DelayType mDelayType;
};

#endif // DELAY_H
