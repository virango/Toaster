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
#include "qbigdial.h"
#include "qbigdialplugin.h"

#include <QtPlugin>

QBigDialPlugin::QBigDialPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QBigDialPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QBigDialPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QBigDialPlugin::createWidget(QWidget *parent)
{
  return new QBigDial(parent);
}

QString QBigDialPlugin::name() const
{
  return QLatin1String("QBigDial");
}

QString QBigDialPlugin::group() const
{
  return QLatin1String("");
}

QIcon QBigDialPlugin::icon() const
{
  return QIcon();
}

QString QBigDialPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QBigDialPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QBigDialPlugin::isContainer() const
{
  return false;
}

QString QBigDialPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QBigDial\" name=\"qBigDial\">\n</widget>\n");
}

QString QBigDialPlugin::includeFile() const
{
  return QLatin1String("qbigdial.h");
}

