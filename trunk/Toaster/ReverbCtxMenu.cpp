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


