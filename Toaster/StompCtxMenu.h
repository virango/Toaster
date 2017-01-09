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
#ifndef STOMPCTXMENU_H
#define STOMPCTXMENU_H
#include <QObject>
#include <QMenu>
#include "CtxMenuProvider.h"

class QAction;
class Stomp;

class StompCtxMenu : public QObject, public ICtxMenuProvider
{
  Q_OBJECT
public:
  StompCtxMenu(Stomp& stomp);

  void createMenu(QMenu& menu);

public slots:
  void setType(QAction* action);

private:
  Stomp& mStomp;

  void createNoneMenu();
  void createWahMenu();
  void createDistortionMenu();
  void createEQMenu();
  void createCompGateMenu();
  void createChorusMenu();
  void createPhaserFlangerMenu();
  void createPitchShifterMenu();
  void createEffectLoopMenu();
  void createDelayReverbMenu();

  QMenu mWahMenu;
  QMenu mDistortionMenu;
  QMenu mEQMenu;
  QMenu mCompGateMenu;
  QMenu mChorusMenu;
  QMenu mPhaserFlangerMenu;
  QMenu mPitchShifterMenu;
  QMenu mEffectLoopMenu;
  QMenu mDelayReverbMenu;
};

#endif // STOMPCTXMENU_H
