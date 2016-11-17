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
#ifndef REVERBFRAME_H
#define REVERBFRAME_H
#include <QWidget>
#include "ui_ReverbFrame.h"
#include "StompEditorPage.h"
#include "Reverb.h"

class ReverbFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit ReverbFrame(QWidget *parent = 0);
  virtual ~ReverbFrame();

  // IStompEditorPage
  virtual void activate(QObject& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpReverb != nullptr; }
  virtual QObject* getStomp()  { return mpReverb; }
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
  void on_predelayDial_valueChanged(double value);
  void on_bandwidthDial_valueChanged(double value);
  void on_frequencyDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_delRevBalanceDial_valueChanged(double value);
  void on_dampingDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  // kpa => ui
  void onPredaly(double value);
  void onBandwidth(double value);
  void onFrequency(double value);
  void onDucking(double value);
  void onDelRevBalance(double value);
  void onDamping(double value);
  void onVolume(double value);
private:
  Ui::ReverbFrame ui;
  Reverb* mpReverb = nullptr;
};

#endif // REVERBFRAME_H
