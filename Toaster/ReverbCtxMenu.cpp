#include "ReverbCtxMenu.h"
#include "Reverb.h"
#include "Commons.h"

ReverbCtxMenu::ReverbCtxMenu(Reverb& reverb)
  : mReverb(reverb)
{
}

void ReverbCtxMenu::createMenu(QMenu& menu)
{
  connect(&menu, SIGNAL(triggered(QAction*)), this, SLOT(setType(QAction*)));

  QAction* action = menu.addAction("Hall");
  action->setData(QVariant((unsigned int)Hall));

  action = menu.addAction("Large Room");
  action->setData(QVariant((unsigned int)LargeRoom));

  action = menu.addAction("Small Room");
  action->setData(QVariant((unsigned int)SmallRoom));

  action = menu.addAction("Ambience");
  action->setData(QVariant((unsigned int)Ambience));

  action = menu.addAction("Matchbox");
  action->setData(QVariant((unsigned int)Matchbox));
}

void ReverbCtxMenu::setType(QAction* action)
{
  ReverbType reverbType = (ReverbType)action->data().toUInt();
  mReverb.applyType(reverbType);
}


