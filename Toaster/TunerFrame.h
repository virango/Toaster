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
#ifndef TUNERFRAME_H
#define TUNERFRAME_H

#include <QWidget>
#include "TunerIndex.h"

namespace Ui {
  class TunerFrame;
}

class TunerFrame : public QWidget
{
  Q_OBJECT

public:
  explicit TunerFrame(QWidget *parent = 0);
  ~TunerFrame();

private slots:
  void on_masterTuneDial_valueChanged(double value);
  void on_muteDial_valueChanged(int valueIndex);

  void onTunerNote(QString note, QString octave);
  void onTunerIndex(int index);
  void onMasterTune(double value);
  void onMute(bool muted);

  void on_toasterTunerLCD_signalMuted(bool muted);

private:
  Ui::TunerFrame *ui;
  TunerIndex mTunerIndex;
};

#endif // TUNERFRAME_H
