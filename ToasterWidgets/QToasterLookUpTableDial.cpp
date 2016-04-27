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
{
  MAP_INSERT(mKnobSkins, Big,   ":/resources/BigDial.png");
  MAP_INSERT(mKnobSkins, Small, ":/resources/SmallDial.png");

  MAP_INSERT(mLEDRingSkins, Uni, ":/resources/LEDRingUni.png");
  MAP_INSERT(mLEDRingSkins, Bi,  ":/resources/LEDRingBi.png");
  createKnobSkin();
  createLEDRingSkin();

  connect(&mAccelerationTimer, &QTimer::timeout,
          [=](){ mAcceleration = 1; });
}

void QToasterLookUpTableDial::createKnobSkin()
{
  if(!mKnobSkinPixmaps.isEmpty())
    mKnobSkinPixmaps.clear();

  QString skin = mKnobSkins[mKnobSize];

  QPixmap masterPixmap(skin);

  int width = masterPixmap.height();
  int height = masterPixmap.height();

  width = masterPixmap.width() / mKnobSkinNoOfFrames;

  if(!masterPixmap.isNull())
  {
    int x = 0;
    int y = 0;
    for(int i = 0; i < mKnobSkinNoOfFrames; i++)
    {
      x = i * width;
      mKnobSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
    }
  }
}

void QToasterLookUpTableDial::createLEDRingSkin()
{
  if(!mLEDRingSkinPixmaps.isEmpty())
    mLEDRingSkinPixmaps.clear();

  if(mLEDRingType != None)
  {
    QString skin = mLEDRingSkins[mLEDRingType];

    QPixmap masterPixmap(skin);

    int width = masterPixmap.height();
    int height = masterPixmap.height();

    width = masterPixmap.width() / mLEDRingSkinNoOfFrames;

    if(!masterPixmap.isNull())
    {
      int x = 0;
      int y = 0;
      for(int i = 0; i < mLEDRingSkinNoOfFrames; i++)
      {
        x = i * width;
        mLEDRingSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
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
      mCurrKnobFrameNo = mKnobSkinNoOfFrames + (newKnobFrameNo % mKnobSkinNoOfFrames);
    else if(newKnobFrameNo >= mKnobSkinNoOfFrames)
      mCurrKnobFrameNo = newKnobFrameNo % mKnobSkinNoOfFrames;
    else
      mCurrKnobFrameNo = newKnobFrameNo;

    mCurrKnobFrameNo %= mKnobSkinNoOfFrames;

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
  createKnobSkin();
}

void QToasterLookUpTableDial::setLEDRingType(LEDRingType ledRingType)
{
  mLEDRingType = ledRingType;
  createLEDRingSkin();
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
  QPainter painter(this);
  QPixmap& pmKnob = mKnobSkinPixmaps[mCurrKnobFrameNo];
  painter.setWindow(0, 0, pmKnob.width(), pmKnob.height());
  if(!mLEDRingSkinPixmaps.isEmpty())
    painter.drawPixmap(0,0, mLEDRingSkinPixmaps[mCurrLEDRingFrameNo]);
  painter.drawPixmap(0, 0, pmKnob);
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
    double step = (mMaxValue - mMinValue) / (mLEDRingSkinNoOfFrames - 1);
    double offset = mMinValue * (-1);
    double value =  (mLookUpTable->at(mCurrValue).first + offset) / step;
    mCurrLEDRingFrameNo = (int) floor(value + 0.5);
    if(mCurrLEDRingFrameNo >= mLEDRingSkinNoOfFrames)
      mCurrLEDRingFrameNo = mLEDRingSkinNoOfFrames - 1;
  }
}
