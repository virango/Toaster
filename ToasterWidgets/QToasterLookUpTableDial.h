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
#ifndef QTOASTERLOOKUPTABLEDIAL_H
#define QTOASTERLOOKUPTABLEDIAL_H
#include <QWidget>
#include <QPixmap>
#include <QMap>
#include <QTimer>
#include "ToasterWidgetsLib.h"

#define MAP_INSERT(x, y, z) x[y] = z

class TOASTERWIDGETS_EXPORT QToasterLookUpTableDial : public QWidget
{
  Q_OBJECT
  Q_ENUMS(KnobSize)
  Q_ENUMS(LEDRingType)
  Q_PROPERTY(KnobSize knobSize READ knobSize WRITE setKnobSize)
  Q_PROPERTY(LEDRingType ledRingType READ ledRingType WRITE setLEDRingType)
  Q_PROPERTY(QString unit READ unit WRITE setUnit)
  Q_PROPERTY(bool isActive READ isActive WRITE setIsActive)

public:
  QToasterLookUpTableDial(QWidget *parent = 0);

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
  QString unit() const { return mUnit; }
  bool isActive() const { return mIsActive; }

  const QString& valueText() const { return mCurrValueText; }

  void setLookUpTable(QVector<QPair<int, QString> >* lookUpTable);

signals:
  void valueChanged(int value);
  void valueChanged(const QString&);

public slots:
  void setKnobSize(KnobSize knobSize);
  void setLEDRingType(LEDRingType ledType);
  void setValue(int value);
  void setUnit(QString unit);
  void setIsActive(bool active) { mIsActive = active; }

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
  QList<QPixmap> mKnobSkinPixmaps;
  QList<QPixmap> mLEDRingSkinPixmaps;
  int mCurrKnobFrameNo;
  int mCurrLEDRingFrameNo;

  KnobSize mKnobSize;
  LEDRingType  mLEDRingType;

  int mMouseY;

  int      mMinValueIndex;
  int      mMaxValueIndex;
  int      mMinValue;
  int      mMaxValue;
  int      mCurrValue;
  QString  mCurrValueText;
  QString  mUnit;
  bool     mIsActive;
  int      mAcceleration;
  QTimer   mAccelerationTimer;
  QVector<QPair<int,QString>>* mLookUpTable;

  QMap<KnobSize, QString> mKnobSkins;
  QMap<LEDRingType, QString> mLEDRingSkins;
  static const int mKnobSkinNoOfFrames = 40;
  static const int mLEDRingSkinNoOfFrames = 15;
};

#endif
