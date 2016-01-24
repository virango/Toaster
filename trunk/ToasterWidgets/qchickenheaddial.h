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
#ifndef QCHICKENHEADDIAL_H
#define QCHICKENHEADDIAL_H
#include <QWidget>
#include <QPixmap>
#include "ToasterWidgetsLib.h"

class TOASTERWIDGETS_EXPORT QChickenHeadDial : public QWidget
{
  Q_OBJECT

public:
  QChickenHeadDial(QWidget *parent = 0);

  enum State
  {
    Off = 0,
    Tuner = 1,
    Browser = 2,
    Perform = 3,
    Profiler = 4
  };

signals:
  void valueChanged(QChickenHeadDial::State);

public slots:
  void setState(State state);

protected:
  void createKnobSkin();
  void paintEvent(QPaintEvent* pe);
  void wheelEvent(QWheelEvent* we);
  void mousePressEvent(QMouseEvent* me);
  //void mouseReleaseEvent(QMouseEvent* me);
  void mouseMoveEvent(QMouseEvent* me);


  void stateUp();
  void stateDown();

private:
  QList<QPixmap> mKnobSkinPixmaps;

  State mCurrState;

  int   mMouseY;

  static const int mKnobSkinNoOfFrames = 5;
};

#endif
