#include "DelayCtxMenu.h"
#include "Delay.h"
#include "Commons.h"

DelayCtxMenu::DelayCtxMenu(Delay& delay)
  : mDelay(delay)
{
}

void DelayCtxMenu::createMenu(QMenu& menu)
{
  connect(&menu, SIGNAL(triggered(QAction*)), this, SLOT(setType(QAction*)));

  QAction* action = menu.addAction("Tap Delay");
  action->setData(QVariant((unsigned int)TapDelay));

  action = menu.addAction("Free Delay");
  action->setData(QVariant((unsigned int)FreeDelay));

  action = menu.addAction("Analog Delay");
  action->setData(QVariant((unsigned int)AnalogDelay));
}

void DelayCtxMenu::setType(QAction* action)
{
  DelayType delayType = (DelayType)action->data().toUInt();
  mDelay.applyType(delayType);
}

