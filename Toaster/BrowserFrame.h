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
#ifndef BROWSERFRAME_H
#define BROWSERFRAME_H
#include <QFrame>
#include "Commons.h"

namespace Ui {
  class BrowserFrame;
}

class BrowserFrame : public QFrame
{
  Q_OBJECT

public:
  explicit BrowserFrame(QWidget *parent = 0);
  ~BrowserFrame();

  void requestValues();

private slots:
  // stomps
  // kpa => ui
  void onStompAOnOff(bool onOff);
  void onStompBOnOff(bool onOff);
  void onStompCOnOff(bool onOff);
  void onStompDOnOff(bool onOff);
  void onStompXOnOff(bool onOff);
  void onStompModOnOff(bool onOff);
  void onStompAType(::FXType type);
  void onStompBType(::FXType type);
  void onStompCType(::FXType type);
  void onStompDType(::FXType type);
  void onStompXType(::FXType type);
  void onStompModType(::FXType type);

  // delay
  // kpa => ui
  void onDelayOnOff(bool onOff);

  // reverb
  // kpa => ui
  void onReverbOnOff(bool onOff);

  // eq
  // ui => kpa
  void on_eqBassDial_valueChanged(double value);
  void on_eqBassDial_valueChanged(const QString &value);
  void on_eqMiddleDial_valueChanged(double value);
  void on_eqMiddleDial_valueChanged(const QString &value);
  void on_eqTrebleDial_valueChanged(double value);
  void on_eqTrebleDial_valueChanged(const QString &value);
  void on_eqPresenceDial_valueChanged(double value);
  void on_eqPresenceDial_valueChanged(const QString &value);
  // kpa => ui
  void onEqBass(double bass);
  void onEqMiddle(double middle);
  void onEqTreble(double treble);
  void onEqPresence(double presence);

  // profile
  // ui => kpa
  // kpa => ui
  void onRigName(const QString& rigName);
  void onRigAuthor(const QString& rigAuthor);
  void onAmpName(const QString& ampName);

  // extended parameter
  // ui => kpa
  void on_browseModeDial_valueChanged(int view);
  //void on_lcdDisplay_browserModeViewChanged(int view);
  // kpa => ui
  void onBrowserView(unsigned int view);

private:
  Ui::BrowserFrame *ui;
};

#endif // BROWSERFRAME_H
