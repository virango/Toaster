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
#ifndef WahWahFrame_H
#define WahWahFrame_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
  class WahWahFrame;
}


class WahWahFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit WahWahFrame(QWidget *parent = 0);
  ~WahWahFrame();

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
  // ui => kpa
  void on_manualDial_valueChanged(double value);
  void on_peakDial_valueChanged(double value);
  void on_pedalRangeDial_valueChanged(double value);
  void on_peakRangeDial_valueChanged(double value);
  void on_pedalModeDial_valueChanged(int valueIndex);
  void on_mixDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  void on_touchAttackDial_valueChanged(double value);
  void on_touchReleaseDial_valueChanged(double value);
  void on_touchBoostDial_valueChanged(double value);
  // kpa => ui
  void onManual(double value);
  void onPeak(double value);
  void onPedalRange(double value);
  void onPeakRange(double value);
  void onPedalMode(::WahPedalMode value);
  void onMix(double value);
  void onDucking(double value);
  void onVolume(double value);
  void onTouchAttack(double value);
  void onTouchRelease(double value);
  void onTouchBoost(double value);

private:
  Ui::WahWahFrame *ui;

  Stomp* mpStomp;
  FXType mFXType;
};

#endif // WahWahFrame_H
