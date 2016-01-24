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
#ifndef FLANGERFRAME_H
#define FLANGERFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class FlangerFrame;
}

class FlangerFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit FlangerFrame(QWidget *parent = 0);
  ~FlangerFrame();
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
  // ui => kpa
  void on_rateDial_valueChanged(int value);
  void on_depthDial_valueChanged(double value);
  void on_manualDial_valueChanged(double value);
  void on_feedbackDial_valueChanged(double value);
  void on_mixDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  // kpa => ui
  void onRate(int value);
  void onDepth(double value);
  void onManual(double value);
  void onFeedback(double value);
  void onMix(double value);
  void onDucking(double value);
  void onVolume(double value);
private:
  Ui::FlangerFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // FLANGERFRAME_H
