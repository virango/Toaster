#ifndef DELAYCTXMENU_H
#define DELAYCTXMENU_H
#include <QObject>
#include <QMenu>
#include "CtxMenuProvider.h"

class QAction;
class Delay;

class DelayCtxMenu : public QObject, public ICtxMenuProvider
{
  Q_OBJECT
public:
  DelayCtxMenu(Delay& delay);

  void createMenu(QMenu& menu);

public slots:
  void setType(QAction* action);

private:
  Delay& mDelay;
};

#endif // DELAYCTXMENU_H
