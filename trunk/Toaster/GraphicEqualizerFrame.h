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
#ifndef GRAPHICEQUALIZERFRAME_H
#define GRAPHICEQUALIZERFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class GraphicEqualizerFrame;
}

class GraphicEqualizerFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit GraphicEqualizerFrame(QWidget *parent = 0);
  ~GraphicEqualizerFrame();

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
  void on_band1Dial_valueChanged(double value);
  void on_band2Dial_valueChanged(double value);
  void on_band3Dial_valueChanged(double value);
  void on_band4Dial_valueChanged(double value);
  void on_band5Dial_valueChanged(double value);
  void on_band6Dial_valueChanged(double value);
  void on_band7Dial_valueChanged(double value);
  void on_band8Dial_valueChanged(double value);
  void on_lowCutDial_valueChanged(int value);
  void on_highCutDial_valueChanged(int value);
  // kpa => ui
  void onMix(double value);
  void onDucking(double value);
  void onVolume(double value);
  void onBand1(double value);
  void onBand2(double value);
  void onBand3(double value);
  void onBand4(double value);
  void onBand5(double value);
  void onBand6(double value);
  void onBand7(double value);
  void onBand8(double value);
  void onLowCut(int value);
  void onHighCut(int value);

private:
  Ui::GraphicEqualizerFrame *ui;
  Stomp* mpStomp;
  FXType mFXType;
};

#endif // GRAPHICEQUALIZERFRAME_H
