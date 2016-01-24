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

QToasterEnumDial::QToasterEnumDial(QWidget *parent)
  : QWidget(parent)
  , mCurrKnobFrameNo()
  , mKnobSize(Big)
  , mMouseY(0)
  , mCurrValueIndex(0)
  , mCurrValueText("")
  , mIsActive(true)
{
  MAP_INSERT(mKnobSkins, Big,   ":/resources/BigDial.png");
  MAP_INSERT(mKnobSkins, Small, ":/resources/SmallDial.png");

  createKnobSkin();
}

void QToasterEnumDial::createKnobSkin()
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
    mCurrKnobFrameNo = mKnobSkinNoOfFrames + (newKnobFrameNo % mKnobSkinNoOfFrames);
  else if(newKnobFrameNo >= mKnobSkinNoOfFrames)
    mCurrKnobFrameNo = newKnobFrameNo % mKnobSkinNoOfFrames;
  else
    mCurrKnobFrameNo = newKnobFrameNo;

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
  mCurrValueText += mValues[mCurrValueIndex];

  emit valueChanged(mCurrValueText);
}

void QToasterEnumDial::setKnobSize(KnobSize knobSize)
{
  mKnobSize = knobSize;
  createKnobSkin();
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
  QPainter painter(this);
  QPixmap& pmKnob = mKnobSkinPixmaps[mCurrKnobFrameNo];
  painter.setWindow(0, 0, pmKnob.width(), pmKnob.height());
  painter.drawPixmap(0, 0, pmKnob);
}

void QToasterEnumDial::wheelEvent(QWheelEvent* we)
{
  we->accept();
  int delta = we->delta()/120;
  update(delta);
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

