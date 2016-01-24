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

QToasterButton::QToasterButton(QWidget *parent)
  : QWidget(parent)
  , mType(Small)
  , mGlobalState(Off)
  , mOnOffState(Off)
  , mClickEmited(false)
  , mAnimLabel(this)
  , mMovie()
  , mpCtxMenuProvider(NULL)
{
  mAnimLabel.setMovie(&mMovie);
  mAnimLabel.hide();
  MAP_INSERT(mSkins, Big,      ":/resources/BigButton.png");
  MAP_INSERT(mSkins, Small,    ":/resources/SmallButton.png");

  MAP_INSERT(mAnims, Big,      ":/resources/BigButtonAnim.gif");
  MAP_INSERT(mAnims, Small,    ":/resources/SmallButtonAnim.gif");
  createSkin();

  mLongClickTimer.setSingleShot(true);
  connect(&mLongClickTimer, SIGNAL(timeout()), this, SLOT(longClick()));
}

void QToasterButton::createSkin()
{
  if(!mSkinPixmaps.isEmpty())
    mSkinPixmaps.clear();

  QString skin = mSkins[mType];

  QPixmap masterPixmap(skin);

  int width = masterPixmap.height();
  int height = masterPixmap.height();

  if(mSkinNoOfFrames)
    width = masterPixmap.width() / mSkinNoOfFrames;

  if(!masterPixmap.isNull())
  {
    int x = 0;
    int y = 0;
    for(int i = 0; i < mSkinNoOfFrames; i++)
    {
      x = i * width;
      mSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
    }
  }

  QString anim = mAnims[mType];
  mMovie.setFileName(anim);
}

void QToasterButton::setType(Type type)
{
  mType = type;
  createSkin();
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
    QPixmap pm = mSkinPixmaps[mGlobalState];
    painter.setWindow(0, 0, pm.width(), pm.height());
    painter.drawPixmap(0, 0, pm);
  }
  else
  {
    mAnimLabel.show();
    mAnimLabel.adjustSize();
    mMovie.start();
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
