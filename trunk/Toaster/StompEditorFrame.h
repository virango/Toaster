#ifndef STOMPEDITORFRAME_H
#define STOMPEDITORFRAME_H

#include <QStackedWidget>
#include "Commons.h"
#include "Stomp.h"
#include "Delay.h"
#include "Reverb.h"
#include "Amp.h"

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
  void onStompType(::FXType type);

private:
  Ui::StompEditorFrame *ui;

  Stomp         mStompA;
  Stomp         mStompB;
  Stomp         mStompC;
  Stomp         mStompD;
  Stomp         mStompX;
  Stomp         mStompMod;
  Delay         mDelay;
  Reverb        mReverb;
  Amp           mAmp;

  Stomp*        mpActiveStomp;
  IStompEditorPage* mpActivePage;
};

#endif // STOMPEDITORFRAME_H
