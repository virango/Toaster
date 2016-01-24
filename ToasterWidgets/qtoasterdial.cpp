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
#include <QPaintEvent>
#include <QWheelEvent>
#include <QToolTip>
#include <math.h>
#include "qtoasterdial.h"

QList<QPixmap> QToasterDial::sSmallKnobSkinPixmaps;
QList<QPixmap> QToasterDial::sBigKnobSkinPixmaps;
QList<QPixmap> QToasterDial::sUniLEDRingSkinPixmaps;
QList<QPixmap> QToasterDial::sBiLEDRingSkinPixmaps;

QToasterDial::QToasterDial(QWidget *parent)
  : QWidget(parent)
  , mCurrKnobFrameNo()
  , mCurrLEDRingFrameNo()
  , mKnobSize(Big)
  , mLEDRingType(Uni)
  , mMouseY(0)
  , mMinValue(0)
  , mMaxValue(16383)
  , mStepWidth(1)
  , mPrecision(0)
  , mCurrValue(0)
  , mCurrValueText("<0.0>")
  , mUnit("")
  , mIsActive(true)
  , mKnobSkinPixmaps(&sBigKnobSkinPixmaps)
  , mLEDRingSkinPixmaps(&sUniLEDRingSkinPixmaps)
{
  createKnobSkin();
  createLEDRingSkin();
}

void QToasterDial::createKnobSkin()
{
  if(sSmallKnobSkinPixmaps.isEmpty())
  {
    QPixmap masterPixmap(":/resources/SmallDial.png");

    int width = masterPixmap.height();
    int height = masterPixmap.height();

    width = masterPixmap.width() / sKnobSkinNoOfFrames;

    if(!masterPixmap.isNull())
    {
      int x = 0;
      int y = 0;
      for(int i = 0; i < sKnobSkinNoOfFrames; i++)
      {
        x = i * width;
        sSmallKnobSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
      }
    }
  }

  if(sBigKnobSkinPixmaps.isEmpty())
  {
    QPixmap masterPixmap(":/resources/BigDial.png");

    int width = masterPixmap.height();
    int height = masterPixmap.height();

    width = masterPixmap.width() / sKnobSkinNoOfFrames;

    if(!masterPixmap.isNull())
    {
      int x = 0;
      int y = 0;
      for(int i = 0; i < sKnobSkinNoOfFrames; i++)
      {
        x = i * width;
        sBigKnobSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
      }
    }
  }
}

void QToasterDial::createLEDRingSkin()
{
  if(sUniLEDRingSkinPixmaps.isEmpty())
  {
    QPixmap masterPixmap(":/resources/LEDRingUni.png");

    int width = masterPixmap.height();
    int height = masterPixmap.height();

    width = masterPixmap.width() / sLEDRingSkinNoOfFrames;

    if(!masterPixmap.isNull())
    {
      int x = 0;
      int y = 0;
      for(int i = 0; i < sLEDRingSkinNoOfFrames; i++)
      {
        x = i * width;
        sUniLEDRingSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
      }
    }
  }

  if(sBiLEDRingSkinPixmaps.isEmpty())
  {
    QPixmap masterPixmap(":/resources/LEDRingBi.png");

    int width = masterPixmap.height();
    int height = masterPixmap.height();

    width = masterPixmap.width() / sLEDRingSkinNoOfFrames;

    if(!masterPixmap.isNull())
    {
      int x = 0;
      int y = 0;
      for(int i = 0; i < sLEDRingSkinNoOfFrames; i++)
      {
        x = i * width;
        sBiLEDRingSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
      }
    }
  }
}

void QToasterDial::update(int deltaSteps)
{
  // update value
  double newValue = mCurrValue + (deltaSteps * mStepWidth);
  double tmp = pow(10, (double)mPrecision);
  newValue = floor(newValue * tmp + 0.5) / tmp;

  if (newValue < mMinValue)
    mCurrValue = mMinValue;
  else if(newValue > mMaxValue)
    mCurrValue = mMaxValue;
  else
    mCurrValue = newValue;

  updateValueText();

  // update knob
  int newKnobFrameNo = mCurrKnobFrameNo + deltaSteps;
  if(newKnobFrameNo < 0)
    mCurrKnobFrameNo = sKnobSkinNoOfFrames + (newKnobFrameNo % sKnobSkinNoOfFrames);
  else if(newKnobFrameNo >= sKnobSkinNoOfFrames)
    mCurrKnobFrameNo = newKnobFrameNo % sKnobSkinNoOfFrames;
  else
    mCurrKnobFrameNo = newKnobFrameNo;

  // update led ring
  updateLEDRing();

  // paint
  QWidget::update();
  showValueTooltip();
  // notify value changed
  if(mIsActive)
    emit valueChanged(mCurrValue);
}

void QToasterDial::updateValueText()
{
  mCurrValueText = "";
  mCurrValueText += QString::number(mCurrValue, 'f', mPrecision) + " " + mUnit;
  if(mCurrValueText.startsWith("0.0") && mMinValue < 0)
    mCurrValueText = "<" + mCurrValueText + ">";

  if(mIsActive)
    emit valueChanged(mCurrValueText);
}

void QToasterDial::setKnobSize(KnobSize knobSize)
{
  mKnobSize = knobSize;
  if(mKnobSize == Small)
    mKnobSkinPixmaps = &sSmallKnobSkinPixmaps;
  else
    mKnobSkinPixmaps = &sBigKnobSkinPixmaps;
}

void QToasterDial::setLEDRingType(LEDRingType ledRingType)
{
  mLEDRingType = ledRingType;
  if(mLEDRingType == None || mLEDRingType == Uni)
    mLEDRingSkinPixmaps = &sUniLEDRingSkinPixmaps;
  else
    mLEDRingSkinPixmaps = &sBiLEDRingSkinPixmaps;
}

void QToasterDial::setMinValue(double minValue)
{
  if(minValue < mMaxValue)
  {
    mMinValue = minValue;
  }
  QWidget::update();
}

void QToasterDial::setMaxValue(double maxValue)
{
  if(maxValue > mMinValue)
  {
    mMaxValue = maxValue;
  }
  QWidget::update();
}

void QToasterDial::setStepWidth(double stepWidth)
{
  if(stepWidth < (mMaxValue - mMinValue))
  {
    mStepWidth = stepWidth;
    if(mStepWidth < 1.0 && mPrecision == 0)
      mPrecision = 1;
  }
}

void QToasterDial::setValue(double value)
{
  if(value >= mMinValue && value <= mMaxValue && mIsActive)
  {
    double tmp = pow(10, (double)mPrecision);
    mCurrValue = floor(value * tmp + 0.5) / tmp;
    updateValueText();
    updateLEDRing();
  }
}

void QToasterDial::setUnit(QString unit)
{
  mUnit = unit;
}

void QToasterDial::paintEvent(QPaintEvent* /* pe */)
{
  if(mKnobSkinPixmaps != nullptr)
  {
    QPainter painter(this);
    const QPixmap& pmKnob = mKnobSkinPixmaps->at(mCurrKnobFrameNo);
    painter.setWindow(0, 0, pmKnob.width(), pmKnob.height());
    if(mLEDRingType != None && mLEDRingSkinPixmaps != nullptr)
      painter.drawPixmap(0,0, mLEDRingSkinPixmaps->at(mCurrLEDRingFrameNo));
    painter.drawPixmap(0, 0, pmKnob);
  }
}

void QToasterDial::wheelEvent(QWheelEvent* we)
{
  we->accept();
  int delta = we->delta()/120;
  update(delta);
}

void QToasterDial::mousePressEvent(QMouseEvent* me)
{
  if(me->button() == Qt::LeftButton)
  {
    me->accept();
    mMouseY = me->y();
  }
  else
    me->ignore();
}

void QToasterDial::mouseMoveEvent(QMouseEvent* me)
{
  if(me->buttons() == Qt::LeftButton)
  {
    me->accept();
    int delta = mMouseY - me->y();
    mMouseY = me->y();
    update(delta);
  }
  else
    me->ignore();
}

void QToasterDial::enterEvent(QEvent* event)
{
  event->accept();
  showValueTooltip();
}

void QToasterDial::leaveEvent(QEvent* event)
{
  event->accept();
  QToolTip::hideText();
}

void QToasterDial::showValueTooltip()
{
  if(mIsActive)
  {
    QPoint pos = mapToGlobal(QPoint(this->width()/2, this->height()/2));
    QToolTip::showText(pos, mCurrValueText, this);
  }
}

void QToasterDial::updateLEDRing()
{
  if(mLEDRingType != None && mIsActive)
  {
    double step = (mMaxValue - mMinValue) / (sLEDRingSkinNoOfFrames - 1);
    double offset = mMinValue * (-1);
    double value =  (mCurrValue + offset) / step;
    mCurrLEDRingFrameNo = (int) floor(value + 0.5);
  }
}
