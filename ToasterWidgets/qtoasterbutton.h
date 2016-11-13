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
#ifndef QTOASTERBUTTON_H
#define QTOASTERBUTTON_H

#include <QWidget>
#include <QMap>
#include <QLabel>
#include <QMovie>
#include <QTimer>

#include "ToasterWidgetsLib.h"

#define MAP_INSERT(x, y, z) x[y] = z

struct ICtxMenuProvider;

class TOASTERWIDGETS_EXPORT QToasterButton : public QWidget
{
  Q_OBJECT
  Q_ENUMS(Type)
  Q_ENUMS(State)
  Q_PROPERTY(Type type READ type WRITE setType)
  Q_PROPERTY(State state READ state WRITE setState)

public:
  QToasterButton(QWidget *parent = 0);

  enum Type
  {
    Big, Small
  };

  enum State
  {
    Off = 0,
    On = 1,
    Blinking = 2
  };

  Type type() const { return mType; }
  State state() const { return mGlobalState; }
  void setCtxMenuProvider(ICtxMenuProvider* ctxMenuProvider) { mpCtxMenuProvider = ctxMenuProvider; }

signals:
  void clicked(QToasterButton& bt, bool longClick);

public slots:
  void setType(Type type);
  void setState(State state);
  void resetToOnOffState();
  bool toggleOnOff();

private slots:
  void longClick();

protected:
  void createSkin();
  void paintEvent(QPaintEvent* pe);
  void mousePressEvent(QMouseEvent* me);
  void mouseReleaseEvent(QMouseEvent* me);
  void contextMenuEvent(QContextMenuEvent * cme);

private:
  QList<QPixmap>* mSkinPixmaps;

  Type    mType;
  State   mGlobalState;
  State   mOnOffState;

  bool    mClickEmited;
  QTimer  mLongClickTimer;
  QLabel  mAnimLabel;

  ICtxMenuProvider* mpCtxMenuProvider;

  static QList<QPixmap> sBigButtonSkinPixmaps;
  static QList<QPixmap> sSmallButtonSkinPixmaps;
  static QMovie* sSmallButtonMovie;
  static QMovie* sBigButtonMovie;
  static const int sSkinNoOfFrames = 2;
};

#endif
