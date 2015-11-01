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

  void activate(StompInstance stompInstance);
  void deactivate();

private slots:
  void onActiveStompType(::FXType type);

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

  Stomp             mStompA;
  Stomp             mStompB;
  Stomp             mStompC;
  Stomp             mStompD;
  Stomp             mStompX;
  Stomp             mStompMod;
  Delay             mDelay;
  Reverb            mReverb;
  Profile           mProfile;

  Stomp*            mpActiveStomp;
  IStompEditorPage* mpActivePage;
};

#endif // STOMPEDITORFRAME_H
