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
#include <QPainter>
#include "qmulticolorled.h"

QList<QPixmap> QMultiColorLed::sSkinPixmaps;

QMultiColorLed::QMultiColorLed(QWidget *parent)
  : QWidget(parent)
  , mColor(Off)
{
  createSkin();
  resize(sSkinPixmaps[Off].width(), sSkinPixmaps[Off].height());
}

void QMultiColorLed::createSkin()
{
  if(sSkinPixmaps.isEmpty())
  {
    QString skin = ":/resources/KPA_Stomp_Led.png";

    QPixmap masterPixmap(skin);

    int width = masterPixmap.width();
    int height = masterPixmap.height() / (NoOfColors);

    if(!masterPixmap.isNull())
    {
      int x = 0;
      int y = 0;
      for(int i = 0; i < NoOfColors; i++)
      {
        y = i * height;
        sSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
      }
    }
  }
}

void QMultiColorLed::paintEvent(QPaintEvent* /*pe*/)
{
  QPainter painter(this);
  if(mColor < NoOfColors)
  {
    QPixmap pm = sSkinPixmaps[mColor];
    painter.setWindow(0, 0, pm.width(), pm.height());
    painter.drawPixmap(0, 0, pm);
  }
}
