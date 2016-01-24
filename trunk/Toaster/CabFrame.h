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
#ifndef CABFRAME_H
#define CABFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Cab.h"

namespace Ui {
class CabFrame;
}

class CabFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit CabFrame(QWidget *parent = 0);
  ~CabFrame();

  // IStompEditorPage
  virtual void activate(QObject& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpCab != nullptr; }
  virtual QObject* getStomp()  { return mpCab; }

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString&  ampName);

private slots:
  void on_highShiftDial_valueChanged(double value);
  void on_lowShiftDial_valueChanged(double value);
  void on_characterDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  void onHighShift(double value);
  void onLowShift(double value);
  void onCharacter(double value);
  void onVolume(double value);

private:
  Ui::CabFrame *ui;

  Cab* mpCab;
};

#endif // CABFRAME_H
