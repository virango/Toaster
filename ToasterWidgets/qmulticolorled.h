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
#ifndef QMULTICOLORLED_H
#define QMULTICOLORLED_H
#include <QWidget>
#include "ToasterWidgetsLib.h"
#include "Commons.h"

class TOASTERWIDGETS_EXPORT QMultiColorLed : public QWidget
{
  Q_OBJECT
  Q_ENUMS(Color)
  Q_PROPERTY(Color color READ color WRITE setColor)

public:
  enum Color
  {
    Off    = 0,
    Orange      = 1,
    Red         = 2,
    Yellow      = 3,
    Cyan        = 4,
    Blue        = 5,
    Purple      = 6,
    White       = 7,
    Green       = 8,
    NoOfColors  = 9      // must be always last
  };

  QMultiColorLed(QWidget *parent = 0);
  ~QMultiColorLed() {}

  Color color() const { return mColor; }

public slots:
  void setColor(Color color) { mColor = color; }

protected:
  void paintEvent(QPaintEvent*);
  void createSkin();

  Color mColor;

  static QList<QPixmap> sSkinPixmaps;
};

#endif
