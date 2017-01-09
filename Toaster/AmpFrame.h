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
#ifndef AMPFRAME_H
#define AMPFRAME_H
#include <QWidget>
#include "ui_AmpFrame.h"
#include "StompEditorPage.h"
#include "Amp.h"

class AmpFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit AmpFrame(QWidget *parent = 0);
  ~AmpFrame();

  // IStompEditorPage
  virtual void activate(QObject& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpAmp != nullptr; }
  virtual QObject* getStomp()  { return mpAmp; }
  virtual QToasterLCD::Page getMaxDisplayPage();
  virtual QToasterLCD::Page getCurrentDisplayPage();
  virtual void setCurrentDisplayPage(QToasterLCD::Page page);

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString&  ampName);

private slots:
  void on_definitionDial_valueChanged(double value);
  void on_powerSaggingDial_valueChanged(double value);
  void on_pickDial_valueChanged(double value);
  void on_compressorDial_valueChanged(double value);
  void on_clarityDial_valueChanged(double value);
  void on_tubeShapeDial_valueChanged(double value);
  void on_tubeBiasDial_valueChanged(double value);
  void on_directMixDial_valueChanged(double value);

  void onDefinition(double value);
  void onPowerSagging(double value);
  void onPick(double value);
  void onCompressor(double value);
  void onClarity(double value);
  void onTubeShape(double value);
  void onTubeBias(double value);
  void onDirectMix(double value);

private:
  Ui::AmpFrame ui;
  Amp* mpAmp = nullptr;
};

#endif // AMPFRAME_H
