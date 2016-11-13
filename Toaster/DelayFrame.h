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
#ifndef DELAYFRAME_H
#define DELAYFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Delay.h"

namespace Ui {
class DelayFrame;
}

class Delay;

class DelayFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit DelayFrame(QWidget *parent = 0);
  ~DelayFrame();

  // IStompEditorPage
  virtual void activate(QObject& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpDelay != nullptr; }
  virtual QObject* getStomp()  { return mpDelay; }
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
  void on_bandwidthDial_valueChanged(double value);
  void on_centerFrequencyDial_valueChanged(double value);
  void on_modulationDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_timeDial_valueChanged(double value);
  void on_ratioDial_valueChanged(int valueIndex);
  void on_volumeDial_valueChanged(double value);
  // kpa => ui
  void onBandwidth(double value);
  void onCenterFrequency(double value);
  void onModulation(double value);
  void onDucking(double value);
  void onTime(double value);
  void onRatio(::DelayRatio ratio);
  void onVolume(double value);

private:
  Ui::DelayFrame *ui;

  Delay* mpDelay;

  QToasterLCD::Page mCurrentPage = QToasterLCD::Page1;
};

#endif // DELAYFRAME_H
