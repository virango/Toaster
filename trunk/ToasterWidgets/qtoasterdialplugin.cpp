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
#include "qtoasterdial.h"
#include "qtoasterdialplugin.h"

#include <QtPlugin>

QToasterDialPlugin::QToasterDialPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QToasterDialPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterDialPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterDialPlugin::createWidget(QWidget *parent)
{
  return new QToasterDial(parent);
}

QString QToasterDialPlugin::name() const
{
  return QLatin1String("QToasterDial");
}

QString QToasterDialPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterDialPlugin::icon() const
{
  return QIcon(":/resources/DialIcon.png");
}

QString QToasterDialPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterDialPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterDialPlugin::isContainer() const
{
  return false;
}

QString QToasterDialPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterDial\" name=\"qToasterDial\">\n</widget>\n");
}

QString QToasterDialPlugin::includeFile() const
{
  return QLatin1String("qtoasterdial.h");
}

