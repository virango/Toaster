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
#include "qlcddisplay.h"
#include "qlcddisplayplugin.h"

#include <QtPlugin>

QLCDDisplayPlugin::QLCDDisplayPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QLCDDisplayPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QLCDDisplayPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QLCDDisplayPlugin::createWidget(QWidget *parent)
{
  return new QLCDDisplay(parent);
}

QString QLCDDisplayPlugin::name() const
{
  return QLatin1String("QLCDDisplay");
}

QString QLCDDisplayPlugin::group() const
{
  return QLatin1String("");
}

QIcon QLCDDisplayPlugin::icon() const
{
  return QIcon();
}

QString QLCDDisplayPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QLCDDisplayPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QLCDDisplayPlugin::isContainer() const
{
  return false;
}

QString QLCDDisplayPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QLCDDisplay\" name=\"qLCDDisplay\">\n</widget>\n");
}

QString QLCDDisplayPlugin::includeFile() const
{
  return QLatin1String("qlcddisplay.h");
}

