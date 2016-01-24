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
#ifndef STOMPEDITORFRAME_H
#define STOMPEDITORFRAME_H

#include <QStackedWidget>
#include "Commons.h"
#include "Stomp.h"
#include "Delay.h"
#include "Reverb.h"
#include "Profile.h"

namespace Ui {
  class StompEditorFrame;
}

struct IStompEditorPage;

class StompEditorFrame : public QStackedWidget
{
  Q_OBJECT

public:
  explicit StompEditorFrame(QWidget *parent = 0);
  ~StompEditorFrame();

  void init(Stomp& stompA,
            Stomp& stompB,
            Stomp& stompC,
            Stomp& stompD,
            Stomp& stompX,
            Stomp& stompMod,
            Delay& delay,
            Reverb& reverb,
            Profile& profile);

  void activate(QObject& stomp);
  void deactivate();

private slots:
  void onActiveStompType(::FXType fxType);
  void onDelayType(::DelayType delayType);
  void onReverbType(::ReverbType reverbType);

  // stomps
  // kpa => ui
  void onStompAOnOff(bool onOff);
  void onStompBOnOff(bool onOff);
  void onStompCOnOff(bool onOff);
  void onStompDOnOff(bool onOff);
  void onStompXOnOff(bool onOff);
  void onStompModOnOff(bool onOff);
  void onStompAType(::FXType type);
  void onStompBType(::FXType type);
  void onStompCType(::FXType type);
  void onStompDType(::FXType type);
  void onStompXType(::FXType type);
  void onStompModType(::FXType type);
  // delay
  // kpa => ui
  void onDelayOnOff(bool onOff);
  // reverb
  // kpa => ui
  void onReverbOnOff(bool onOff);
  // profile
  // kpa => ui
  void onAmpName(const QString& ampName);

private:
  void requestValues();
  void activatePage(IStompEditorPage* page, int index);

private:
  Ui::StompEditorFrame *ui;

  Stomp*            mpStompA;
  Stomp*            mpStompB;
  Stomp*            mpStompC;
  Stomp*            mpStompD;
  Stomp*            mpStompX;
  Stomp*            mpStompMod;
  Delay*            mpDelay;
  Reverb*           mpReverb;
  Profile*          mpProfile;

  QObject*          mpActiveStomp;
  int               mActiveStompType;
  IStompEditorPage* mpActivePage;
};

#endif // STOMPEDITORFRAME_H
