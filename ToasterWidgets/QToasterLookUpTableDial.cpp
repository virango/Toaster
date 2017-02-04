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
#include "QToasterLookUpTableDial.h"

#define DEFAULT_SKIN

QList<QPixmap> QToasterLookUpTableDial::sSmallKnobSkinPixmaps;
QList<QPixmap> QToasterLookUpTableDial::sBigKnobSkinPixmaps;
QList<QPixmap> QToasterLookUpTableDial::sUniLEDRingSkinPixmaps;
QList<QPixmap> QToasterLookUpTableDial::sBiLEDRingSkinPixmaps;

QToasterLookUpTableDial::QToasterLookUpTableDial(QWidget *parent)
  : QWidget(parent)
  , mCurrKnobFrameNo(0)
  , mCurrLEDRingFrameNo(0)
  , mKnobSize(Big)
  , mLEDRingType(Uni)
  , mMouseY(0)
  , mMinValueIndex(0)
  , mMaxValueIndex(0)
  , mMinValue(0)
  , mMaxValue(0)
  , mCurrValue(0)
  , mCurrValueText("<0.0>")
  , mUnit("")
  , mIsActive(true)
  , mAcceleration(1)
  , mLookUpTable(nullptr)
  , mKnobSkinPixmaps(&sBigKnobSkinPixmaps)
  , mLEDRingSkinPixmaps(&sUniLEDRingSkinPixmaps)
{
  createKnobSkin();
  createLEDRingSkin();

  connect(&mAccelerationTimer, &QTimer::timeout,
          [=](){ mAcceleration = 1; });
}

void QToasterLookUpTableDial::createKnobSkin()
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

void QToasterLookUpTableDial::createLEDRingSkin()
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

void QToasterLookUpTableDial::setLookUpTable(QVector<QPair<int,QString>>* lookUpTable)
{
  mLookUpTable = lookUpTable;
  if(mLookUpTable != nullptr)
  {
    mMinValue = mLookUpTable->at(0).first;
    mMaxValue = mLookUpTable->at(mLookUpTable->size() - 1).first;

    mMinValueIndex = 0;
    mMaxValueIndex = mLookUpTable->size() - 1;
  }
}

void QToasterLookUpTableDial::update(int deltaSteps)
{
  if(mLookUpTable != nullptr)
  {
    // update value
    int newValue = mCurrValue + (deltaSteps * mAcceleration);
    if (newValue < mMinValueIndex)
      mCurrValue = mMinValueIndex;
    else if(newValue > mMaxValueIndex)
      mCurrValue = mMaxValueIndex;
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

    mCurrKnobFrameNo %= sKnobSkinNoOfFrames;

    // update led ring
    updateLEDRing();

    // paint
    QWidget::update();
    showValueTooltip();
    // notify value changed
    if(mIsActive)
      emit valueChanged(mLookUpTable->at(mCurrValue).first);

    if(mAccelerationTimer.isActive())
    {
      mAccelerationTimer.stop();
      if(mAcceleration < 10)
        mAcceleration++;
    }

    mAccelerationTimer.start(200);
  }
}

void QToasterLookUpTableDial::updateValueText()
{
  if(mLookUpTable != nullptr)
  {
    mCurrValueText = mLookUpTable->at((int)mCurrValue).second + " " + mUnit;

    if(mCurrValueText.startsWith("0.0") && mMinValueIndex < 0)
      mCurrValueText = "<" + mCurrValueText + ">";

    if(mIsActive)
      emit valueChanged(mCurrValueText);
  }
}

void QToasterLookUpTableDial::setKnobSize(KnobSize knobSize)
{
  mKnobSize = knobSize;
  if(mKnobSize == Small)
    mKnobSkinPixmaps = &sSmallKnobSkinPixmaps;
  else
    mKnobSkinPixmaps = &sBigKnobSkinPixmaps;
}

void QToasterLookUpTableDial::setLEDRingType(LEDRingType ledRingType)
{
  mLEDRingType = ledRingType;
  if(mLEDRingType == None || mLEDRingType == Uni)
    mLEDRingSkinPixmaps = &sUniLEDRingSkinPixmaps;
  else
    mLEDRingSkinPixmaps = &sBiLEDRingSkinPixmaps;
}

void QToasterLookUpTableDial::setValue(int value)
{
  if(mLookUpTable != nullptr && mIsActive)
  {
    for(int i = 0; i < mLookUpTable->size(); ++i)
    {
      if(mLookUpTable->at(i).first > value)
        break;
      mCurrValue = i;
    }
    if(mCurrValue > mMaxValueIndex)
      mCurrValue = mMaxValueIndex;

    updateValueText();
    updateLEDRing();
  }
}

void QToasterLookUpTableDial::setUnit(QString unit)
{
  mUnit = unit;
}

void QToasterLookUpTableDial::paintEvent(QPaintEvent* /* pe */)
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

void QToasterLookUpTableDial::wheelEvent(QWheelEvent* we)
{
  we->accept();
  int delta = we->delta();
  if(delta > 0)
    update(1);
  else if(delta < 0)
    update(-1);
}

void QToasterLookUpTableDial::mousePressEvent(QMouseEvent* me)
{
  if(me->button() == Qt::LeftButton)
  {
    me->accept();
    mMouseY = me->y();
  }
  else
    me->ignore();
}

void QToasterLookUpTableDial::mouseMoveEvent(QMouseEvent* me)
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

void QToasterLookUpTableDial::enterEvent(QEvent* event)
{
  event->accept();
  showValueTooltip();
}

void QToasterLookUpTableDial::leaveEvent(QEvent* event)
{
  event->accept();
  QToolTip::hideText();
}

void QToasterLookUpTableDial::showValueTooltip()
{
  if(mIsActive)
  {
    QPoint pos = mapToGlobal(QPoint(this->width()/2, this->height()/2));
    QToolTip::showText(pos, mCurrValueText, this);
  }
}

void QToasterLookUpTableDial::updateLEDRing()
{
  if(mLEDRingType != None && mIsActive)
  {
    double step = (mMaxValue - mMinValue) / (sLEDRingSkinNoOfFrames - 1);
    double offset = mMinValue * (-1);
    double value =  (mLookUpTable->at(mCurrValue).first + offset) / step;
    mCurrLEDRingFrameNo = (int) floor(value + 0.5);
    if(mCurrLEDRingFrameNo >= sLEDRingSkinNoOfFrames)
      mCurrLEDRingFrameNo = sLEDRingSkinNoOfFrames - 1;
  }
}
