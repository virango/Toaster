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
#include "ui_StompEditorFrame.h"
#include "Commons.h"

struct IStompEditorPage;

class StompEditorFrame : public QWidget
{
  Q_OBJECT

public:
  explicit StompEditorFrame(QWidget *parent = 0);
  ~StompEditorFrame();

  void init();

  void activate(QObject& stomp);
  void deactivate();

signals:
  void editorPageChanged(IStompEditorPage* editorPage);

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
  void onStompDelayType(::FXType type);
  // delay
  // kpa => ui
  void onDelayOnOff(bool onOff);
  // reverb
  // kpa => ui
  void onReverbOnOff(bool onOff);
  // profile
  // kpa => ui
  void onAmpName(const QString& ampName);

public slots:
  void nextDisplayPage();
  void prevDisplayPage();

private:
  void requestValues();
  void activatePage(IStompEditorPage* page);

private:
  Ui::StompEditorFrame ui;

  QObject*          mpActiveStomp;
  int               mActiveStompType;
  IStompEditorPage* mpActivePage;
};

#endif // STOMPEDITORFRAME_H
