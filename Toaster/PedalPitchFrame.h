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
#ifndef PEDALPITCHFRAME_H
#define PEDALPITCHFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"
#include "Global.h"

namespace Ui {
class PedalPitchFrame;
}


class PedalPitchFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit PedalPitchFrame(QWidget *parent = 0);
  ~PedalPitchFrame();
  // IStompEditorPage
  virtual void activate(QObject& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpStomp != nullptr; }
  virtual QObject* getStomp()  { return mpStomp; }
  virtual QToasterLCD::Page getMaxDisplayPage();
  virtual QToasterLCD::Page getCurrentDisplayPage();
  virtual void setCurrentDisplayPage(QToasterLCD::Page page);

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString&  ampName);
private slots:
  void on_pageDial_valueChanged(int valueIndex);

  // ui => kpa
  void on_heelPitchDial_valueChanged(double value);
  void on_toePitchDial_valueChanged(double value);
  void on_formantShiftDial_valueChanged(double value);
  void on_mixDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_wahPedalToPitchDial_valueChanged(int valueIndex);
  void on_smoothChordsDial_valueChanged(int valueIndex);
  void on_pureTuningDial_valueChanged(int valueIndex);
  void on_formantShiftOnOffDial_valueChanged(int valueIndex);
  // kpa => ui
  void onHeelPitch(double value);
  void onToePitch(double value);
  void onFormantShift(double value);
  void onMix(double value);
  void onVolume(double value);
  void onDucking(double value);
  void onWahPedalToPitch(bool onOff);
  void onSmoothChords(bool onOff);
  void onPureTuning(bool onOff);
  void onFormantShiftOnOff(bool onOff);



private:
  Ui::PedalPitchFrame *ui;

  Stomp* mpStomp;
  Global mGlobal;

  FXType mFXType;
};

#endif // PEDALPITCHFRAME_H
