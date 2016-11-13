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
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include "CtxMenuProvider.h"
#include "qtoasterbutton.h"

QList<QPixmap> QToasterButton::sBigButtonSkinPixmaps;
QList<QPixmap> QToasterButton::sSmallButtonSkinPixmaps;
QMovie* QToasterButton::sSmallButtonMovie = nullptr;
QMovie* QToasterButton::sBigButtonMovie = nullptr;

QToasterButton::QToasterButton(QWidget *parent)
  : QWidget(parent)
  , mSkinPixmaps(&sSmallButtonSkinPixmaps)
  , mType(Small)
  , mGlobalState(Off)
  , mOnOffState(Off)
  , mClickEmited(false)
  , mAnimLabel(this)
  , mpCtxMenuProvider(NULL)
{


  createSkin();

  mAnimLabel.setMovie(sSmallButtonMovie);
  mAnimLabel.hide();
  mLongClickTimer.setSingleShot(true);
  connect(&mLongClickTimer, SIGNAL(timeout()), this, SLOT(longClick()));
}

void QToasterButton::createSkin()
{
  if(sSmallButtonMovie == nullptr)
    sSmallButtonMovie = new QMovie(":/resources/SmallButtonAnim.gif");

  if(sBigButtonMovie == nullptr)
    sBigButtonMovie = new QMovie(":/resources/BigButtonAnim.gif");

  if(sSmallButtonSkinPixmaps.isEmpty())
  {
    QPixmap masterPixmap(":/resources/SmallButton.png");

    int width = masterPixmap.height();
    int height = masterPixmap.height();

    if(sSkinNoOfFrames)
      width = masterPixmap.width() / sSkinNoOfFrames;

    if(!masterPixmap.isNull())
    {
      int x = 0;
      int y = 0;
      for(int i = 0; i < sSkinNoOfFrames; i++)
      {
        x = i * width;
        sSmallButtonSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
      }
    }
  }

  if(sBigButtonSkinPixmaps.isEmpty())
  {
    QPixmap masterPixmap(":/resources/BigButton.png");

    int width = masterPixmap.height();
    int height = masterPixmap.height();

    if(sSkinNoOfFrames)
      width = masterPixmap.width() / sSkinNoOfFrames;

    if(!masterPixmap.isNull())
    {
      int x = 0;
      int y = 0;
      for(int i = 0; i < sSkinNoOfFrames; i++)
      {
        x = i * width;
        sBigButtonSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
      }
    }


  }
}

void QToasterButton::setType(Type type)
{
  mType = type;
  if(mType == Small)
  {
    mSkinPixmaps = &sSmallButtonSkinPixmaps;
    mAnimLabel.setMovie(sSmallButtonMovie);
  }
  else if(mType == Big)
  {
    mSkinPixmaps = &sBigButtonSkinPixmaps;
    mAnimLabel.setMovie(sBigButtonMovie);
  }
}

void QToasterButton::setState(State state)
{
  mGlobalState = state;
  if(state != Blinking)
    mOnOffState = state;
  update();
}

void QToasterButton::longClick()
{
  emit clicked(*this, true);
  mClickEmited = true;
}

void QToasterButton::paintEvent(QPaintEvent* /* pe */)
{
  QPainter painter(this);
  if(mGlobalState < Blinking)
  {
    mAnimLabel.hide();
    QPixmap pm = mSkinPixmaps->at(mGlobalState);
    painter.setWindow(0, 0, pm.width(), pm.height());
    painter.drawPixmap(0, 0, pm);
  }
  else
  {
    mAnimLabel.show();
    mAnimLabel.adjustSize();
    if(mAnimLabel.movie() != nullptr)
      mAnimLabel.movie()->start();
  }
}

void QToasterButton::mousePressEvent(QMouseEvent* me)
{
  if(me->button() == Qt::LeftButton)
  {
    mLongClickTimer.start(500);
    me->accept();
  }
  else
    me->ignore();
}

void QToasterButton::mouseReleaseEvent(QMouseEvent* me)
{
  if(me->button() == Qt::LeftButton)
  {
    me->accept();
    mLongClickTimer.stop();
    if(mClickEmited)
      mClickEmited = false;
    else
      emit clicked(*this, false);
  }
  else
    me->ignore();
}


void QToasterButton::contextMenuEvent(QContextMenuEvent * cme)
{
  if(mpCtxMenuProvider)
  {
    QMenu ctxMenu;
    QPoint globalPos = mapToGlobal(cme->pos());
    mpCtxMenuProvider->createMenu(ctxMenu);
    if(!ctxMenu.isEmpty())
      ctxMenu.exec(globalPos);
  }
}

void QToasterButton::resetToOnOffState()
{
  mGlobalState = mOnOffState;
}

bool QToasterButton::toggleOnOff()
{
  if(mOnOffState == On)
    mOnOffState = Off;
  else
    mOnOffState = On;

  if(mGlobalState != Blinking)
    mGlobalState = mOnOffState;

  return mOnOffState == On;
}
