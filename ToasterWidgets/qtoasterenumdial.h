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
#ifndef QTOASTERENUMDIAL_H
#define QTOASTERENUMDIAL_H
#include <QWidget>
#include <QPixmap>
#include <QMap>
#include "ToasterWidgetsLib.h"

#define MAP_INSERT(x, y, z) x[y] = z

class TOASTERWIDGETS_EXPORT QToasterEnumDial : public QWidget
{
  Q_OBJECT
  Q_ENUMS(KnobSize)
  Q_ENUMS(LEDRingType)
  Q_PROPERTY(KnobSize knobSize READ knobSize WRITE setKnobSize)
  Q_PROPERTY(LEDRingType ledRingType READ ledRingType WRITE setLEDRingType)
  Q_PROPERTY(QStringList values READ values WRITE setValues)
  Q_PROPERTY(bool isActive READ isActive WRITE setIsActive)
public:
  QToasterEnumDial(QWidget *parent = 0);

  enum KnobSize
  {
    Big, Small
  };

  enum LEDRingType
  {
    None, Uni, Bi
  };

  KnobSize knobSize() const { return mKnobSize; }
  LEDRingType ledRingType() const { return mLEDRingType; }
  QStringList values() const { return mValues; }
  bool isActive() const { return mIsActive; }

  const QString& valueText() const { return mCurrValueText; }

  unsigned int valueIndex() const { return mCurrValueIndex; }

signals:
  void valueChanged(int valueIndex);
  void valueChanged(const QString&);

public slots:
  void setKnobSize(KnobSize knobSize);
  void setLEDRingType(LEDRingType ledType);
  void setValues(QStringList values);
  void setIsActive(bool enabled) { mIsActive = enabled; }
  //void setValue(const QString& value);
  void setValue(int value);

protected:
  void createKnobSkin();
  void createLEDRingSkin();
  void paintEvent(QPaintEvent* pe);
  void wheelEvent(QWheelEvent* we);
  void mousePressEvent(QMouseEvent* me);
  void mouseMoveEvent(QMouseEvent* me);

  void enterEvent(QEvent* event);
  void leaveEvent(QEvent* event);

  void update(int deltaSteps);
  void updateValueText();
  void showValueTooltip();

  void updateLEDRing();

private:
  QList<QPixmap>* mKnobSkinPixmaps;
  QList<QPixmap>* mLEDRingSkinPixmaps;
  int             mCurrKnobFrameNo;
  int             mCurrLEDRingFrameNo;
  KnobSize        mKnobSize;
  LEDRingType     mLEDRingType;
  int             mMouseY;
  int             mCurrValueIndex;
  QString         mCurrValueText;

  bool            mIsActive;

  QStringList     mValues;

  static QList<QPixmap> sSmallKnobSkinPixmaps;
  static QList<QPixmap> sBigKnobSkinPixmaps;
  static QList<QPixmap> sUniLEDRingSkinPixmaps;
  static QList<QPixmap> sBiLEDRingSkinPixmaps;
  static const int sKnobSkinNoOfFrames = 40;
  static const int sLEDRingSkinNoOfFrames = 15;
};

#endif
