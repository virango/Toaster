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
#ifndef INPUTFRAME_H
#define INPUTFRAME_H
#include <QWidget>
#include "ui_InputFrame.h"
#include "StompEditorPage.h"
#include "Input.h"

class InputFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit InputFrame(QWidget *parent = 0);
  ~InputFrame();
  // IStompEditorPage
  virtual void activate(QObject& module);
  virtual void deactivate();
  virtual bool isActive() { return mpInput != nullptr; }
  virtual QObject* getStomp()  { return mpInput; }
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
  void on_cleanSensDial_valueChanged(double value);
  void on_distortionSensDial_valueChanged(double value);
  void on_inputSourceDial_valueChanged(int valueIndex);
  void on_reampSensDial_valueChanged(double value);
  // kpa => ui
  void OnCleanSens(double value);
  void OnDistortionSens(double value);
  void OnInputSource(int valueIndex);
  void OnReampSens(double value);

private:
  Ui::InputFrame ui;
  Input* mpInput = nullptr;
};

#endif // INPUTFRAME_H
