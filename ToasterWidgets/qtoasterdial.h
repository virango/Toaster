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
#ifndef QTOASTERDIAL_H
#define QTOASTERDIAL_H
#include <QWidget>
#include <QPixmap>
#include <QMap>
#include "ToasterWidgetsLib.h"

class TOASTERWIDGETS_EXPORT QToasterDial : public QWidget
{
  Q_OBJECT
  Q_ENUMS(KnobSize)
  Q_ENUMS(LEDRingType)
  Q_PROPERTY(KnobSize knobSize READ knobSize WRITE setKnobSize)
  Q_PROPERTY(LEDRingType ledRingType READ ledRingType WRITE setLEDRingType)
  Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
  Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
  Q_PROPERTY(double value READ value WRITE setValue)
  Q_PROPERTY(double stepWidth READ stepWidth WRITE setStepWidth)
  Q_PROPERTY(unsigned int precision READ precision WRITE setPrecision)
  Q_PROPERTY(QString unit READ unit WRITE setUnit)
  Q_PROPERTY(bool isActive READ isActive WRITE setIsActive)

public:
  QToasterDial(QWidget *parent = 0);

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
  double minValue() const { return mMinValue; }
  double maxValue() const { return mMaxValue; }
  double value() const { return mCurrValue; }
  double stepWidth() const { return mStepWidth; }
  int precision() const { return mPrecision; }
  QString unit() const { return mUnit; }
  bool isActive() const { return mIsActive; }
  const QString& valueText() const { return mCurrValueText; }

signals:
  void valueChanged(double);
  void valueChanged(const QString&);

public slots:
  void setKnobSize(KnobSize knobSize);
  void setLEDRingType(LEDRingType ledType);
  void setMinValue(double minValue);
  void setMaxValue(double maxValue);
  void setStepWidth(double stepWidth);
  void setPrecision(unsigned int precision) { mPrecision = precision; }
  void setValue(double value);
  void setUnit(QString unit);
  void setIsActive(bool active) { mIsActive = active; update(0); }

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
  int             mCurrKnobFrameNo;
  int             mCurrLEDRingFrameNo;
  KnobSize        mKnobSize;
  LEDRingType     mLEDRingType;
  int             mMouseY;
  double          mMinValue;
  double          mMaxValue;
  double          mStepWidth;
  int             mPrecision;
  double          mCurrValue;
  QString         mCurrValueText;
  QString         mUnit;
  bool            mIsActive;
  QList<QPixmap>* mKnobSkinPixmaps;
  QList<QPixmap>* mLEDRingSkinPixmaps;

  static QList<QPixmap> sSmallKnobSkinPixmaps;
  static QList<QPixmap> sBigKnobSkinPixmaps;
  static QList<QPixmap> sUniLEDRingSkinPixmaps;
  static QList<QPixmap> sBiLEDRingSkinPixmaps;
  static const int sKnobSkinNoOfFrames = 40;
  static const int sLEDRingSkinNoOfFrames = 15;
};

Q_DECLARE_METATYPE(QToasterDial::LEDRingType)

#endif
