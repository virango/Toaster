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
#ifndef LEGACYDELAYFRAME_H
#define LEGACYDELAYFRAME_H

#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class LegacyDelayFrame;
}

class LegacyDelayFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit LegacyDelayFrame(QWidget *parent = 0);
  ~LegacyDelayFrame();
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
  void on_mixDial_valueChanged(int value);
  void on_delay1TimeDial_valueChanged(double value);
  void on_delay2RatioDial_valueChanged(double value);
  void on_feedbackDial_valueChanged(double value);
  void on_noteValue1Dial_valueChanged(int valueIndex);
  void on_noteValue2Dial_valueChanged(int valueIndex);
  void on_toTempoDial_valueChanged(int valueIndex);
  void on_bandwidthDial_valueChanged(double value);
  void on_frequencyDial_valueChanged(double value);
  void on_modulationDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  // kpa => ui
  void OnMix(int value);
  void OnDelay1Time(double value);
  void OnDelay2Ratio(double value);
  void OnFeedback(double value);
  void OnNoteValue1(int valueIndex);
  void OnNoteValue2(int valueIndex);
  void OnToTempo(int valueIndex);
  void OnBandwidth(double value);
  void OnFrequency(double value);
  void OnModulation(double value);
  void OnDucking(double value);

private:
  void UpdateLCD();
  Ui::LegacyDelayFrame *ui;
  Stomp* mpStomp;
  bool mToTempo;
  QToasterLCD::Page mCurrentPage = QToasterLCD::Page1;
};

#endif // LEGACYDELAYFRAME_H
