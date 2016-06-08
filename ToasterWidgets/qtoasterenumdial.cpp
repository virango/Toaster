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
#include "qtoasterenumdial.h"

#define DEFAULT_SKIN

QList<QPixmap> QToasterEnumDial::sSmallKnobSkinPixmaps;
QList<QPixmap> QToasterEnumDial::sBigKnobSkinPixmaps;
QList<QPixmap> QToasterEnumDial::sUniLEDRingSkinPixmaps;
QList<QPixmap> QToasterEnumDial::sBiLEDRingSkinPixmaps;

QToasterEnumDial::QToasterEnumDial(QWidget *parent)
  : QWidget(parent)
  , mKnobSkinPixmaps(&sBigKnobSkinPixmaps)
  , mLEDRingSkinPixmaps(&sUniLEDRingSkinPixmaps)
  , mCurrKnobFrameNo(0)
  , mCurrLEDRingFrameNo(0)
  , mKnobSize(Big)
  , mLEDRingType(None)
  , mMouseY(0)
  , mCurrValueIndex(0)
  , mCurrValueText("")
  , mIsActive(true)
{
  createKnobSkin();
  createLEDRingSkin();
}

void QToasterEnumDial::createKnobSkin()
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

void QToasterEnumDial::createLEDRingSkin()
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

void QToasterEnumDial::update(int deltaSteps)
{
  // update value
  int newValueIndex = mCurrValueIndex + deltaSteps;

  if (newValueIndex < 0)
    mCurrValueIndex = 0;
  else if(newValueIndex >= mValues.size())
    mCurrValueIndex = mValues.size() - 1;
  else
    mCurrValueIndex = newValueIndex;

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
    emit valueChanged(mCurrValueIndex);
}

void QToasterEnumDial::updateValueText()
{
  mCurrValueText = "";
  if(mValues.size() > 0 && mCurrValueIndex >= 0 && mCurrValueIndex < mValues.size())
    mCurrValueText += mValues[mCurrValueIndex];

  emit valueChanged(mCurrValueText);
}

void QToasterEnumDial::setKnobSize(KnobSize knobSize)
{
  mKnobSize = knobSize;
  if(mKnobSize == Small)
    mKnobSkinPixmaps = &sSmallKnobSkinPixmaps;
  else
    mKnobSkinPixmaps = &sBigKnobSkinPixmaps;
}

void QToasterEnumDial::setLEDRingType(LEDRingType ledRingType)
{
  mLEDRingType = ledRingType;
  if(mLEDRingType == None || mLEDRingType == Uni)
    mLEDRingSkinPixmaps = &sUniLEDRingSkinPixmaps;
  else
    mLEDRingSkinPixmaps = &sBiLEDRingSkinPixmaps;
}

void QToasterEnumDial::setValues(QStringList values)
{
  mValues = values;
  updateValueText();
  QWidget::update();
}

void QToasterEnumDial::setValue(int value)
{
  if(value >= 0 && value < mValues.size() && mIsActive)
  {
    mCurrValueIndex = value;
    updateValueText();
    QWidget::update();
    emit valueChanged(mCurrValueIndex);
  }
}

void QToasterEnumDial::paintEvent(QPaintEvent* /* pe */)
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

void QToasterEnumDial::wheelEvent(QWheelEvent* we)
{
  we->accept();
  int delta = we->delta();
  if(delta > 0)
    update(1);
  else if(delta < 0)
    update(-1);
}

void QToasterEnumDial::mousePressEvent(QMouseEvent* me)
{
  if(me->button() == Qt::LeftButton)
  {
    me->accept();
    mMouseY = me->y();
  }
  else
    me->ignore();
}

void QToasterEnumDial::mouseMoveEvent(QMouseEvent* me)
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

void QToasterEnumDial::enterEvent(QEvent* event)
{
  event->accept();
  showValueTooltip();
}

void QToasterEnumDial::leaveEvent(QEvent* event)
{
  event->accept();
  QToolTip::hideText();
}

void QToasterEnumDial::showValueTooltip()
{
  if(mIsActive)
  {
    QPoint pos = mapToGlobal(QPoint(this->width()/2, this->height()/2));
    QToolTip::showText(pos, mCurrValueText, this);
  }
}

void QToasterEnumDial::updateLEDRing()
{
  if(mLEDRingType != None && mIsActive)
  {
    double step = (double)mValues.size() / (double)(sLEDRingSkinNoOfFrames);
    double value =  mCurrValueIndex / step;
    mCurrLEDRingFrameNo = (int) floor(value + 0.5);
    if(mCurrLEDRingFrameNo > sLEDRingSkinNoOfFrames)
      mCurrLEDRingFrameNo = sLEDRingSkinNoOfFrames;
  }
}
