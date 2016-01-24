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
#ifndef STUDIOEQUALIZERFRAME_H
#define STUDIOEQUALIZERFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class StudioEqualizerFrame;
}

class StudioEqualizerFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit StudioEqualizerFrame(QWidget *parent = 0);
  ~StudioEqualizerFrame();
  // IStompEditorPage
  virtual void activate(QObject& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpStomp != nullptr; }
  virtual QObject* getStomp()  { return mpStomp; }

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString&  ampName);

private slots:
  void on_pageDial_valueChanged(int valueIndex);
  // ui => kpa
  void on_mixDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  void on_lowCutDial_valueChanged(int value);
  void on_highCutDial_valueChanged(int value);
  void on_lowGainDial_valueChanged(double value);
  void on_lowFreqDial_valueChanged(int value);
  void on_highGainDial_valueChanged(double value);
  void on_highFreqDial_valueChanged(int value);
  void on_mid1GainDial_valueChanged(double value);
  void on_mid1FreqDial_valueChanged(int value);
  void on_mid1QFactorDial_valueChanged(int value);
  void on_mid2GainDial_valueChanged(double value);
  void on_mid2FreqDial_valueChanged(int value);
  void on_mid2QFactorDial_valueChanged(int value);
  // kpa => ui
  void onMix(double value);
  void onDucking(double value);
  void onVolume(double value);
  void onLowCut(int value);
  void onHighCut(int value);
  void onLowGain(double value);
  void onLowFreq(int value);
  void onHighGain(double value);
  void onHighFreq(int value);
  void onMid1Gain(double value);
  void onMid1Freq(int value);
  void onMid1QFactor(int value);
  void onMid2Gain(double value);
  void onMid2Freq(int value);
  void onMid2QFactor(int value);

private:
  Ui::StudioEqualizerFrame *ui;

  Stomp* mpStomp;
  FXType mFXType;
};

#endif // STUDIOEQUALIZERFRAME_H
