#ifndef STOMPCTXMENU_H
#define STOMPCTXMENU_H
#include <QObject>
#include <QMenu>
#include "CtxMenuProvider.h"

class Stomp;
class QAction;

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
