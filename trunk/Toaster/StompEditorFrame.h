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
