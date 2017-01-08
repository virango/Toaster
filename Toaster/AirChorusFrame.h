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
#ifndef AIRCHORUSFRAME_H
#define AIRCHORUSFRAME_H
#include <QWidget>
#include "ui_AirChorusFrame.h"
#include "StompEditorPage.h"
#include "Stomp.h"

class AirChorusFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit AirChorusFrame(QWidget *parent = 0);
  ~AirChorusFrame();
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
  void on_depthDial_valueChanged(double value);
  void on_crossoverDial_valueChanged(int value);
  void on_volumeDial_valueChanged(double value);
  // kpa => ui
  void onDepth(double value);
  void onCrossover(int value);
  void onVolume(double value);
private:
  Ui::AirChorusFrame ui;
  Stomp* mpStomp = nullptr;
};

#endif // AIRCHORUSFRAME_H
