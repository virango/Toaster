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
#include "QToasterBrowserLCD.h"
#include "QToasterBrowserLCDPlugin.h"

#include <QtPlugin>

QToasterBrowserLCDPlugin::QToasterBrowserLCDPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QToasterBrowserLCDPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterBrowserLCDPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterBrowserLCDPlugin::createWidget(QWidget *parent)
{
  return new QToasterBrowserLCD(parent);
}

QString QToasterBrowserLCDPlugin::name() const
{
  return QLatin1String("QToasterBrowserLCD");
}

QString QToasterBrowserLCDPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterBrowserLCDPlugin::icon() const
{
  return QIcon();
}

QString QToasterBrowserLCDPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterBrowserLCDPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterBrowserLCDPlugin::isContainer() const
{
  return false;
}

QString QToasterBrowserLCDPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterBrowserLCD\" name=\"toasterBrowserLCD\">\n</widget>\n");
}

QString QToasterBrowserLCDPlugin::includeFile() const
{
  return QLatin1String("QToasterBrowserLCD.h");
}

