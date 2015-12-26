#ifndef REVERBCTXMENU_H
#define REVERBCTXMENU_H
#include <QObject>
#include <QMenu>
#include "CtxMenuProvider.h"

class QAction;
class Reverb;

class ReverbCtxMenu : public QObject, public ICtxMenuProvider
{
  Q_OBJECT
public:
  explicit ReverbCtxMenu(Reverb& reverb);

  void createMenu(QMenu& menu);

public slots:
  void setType(QAction* action);

private:
  Reverb& mReverb;
};

#endif // REVERBCTXMENU_H
