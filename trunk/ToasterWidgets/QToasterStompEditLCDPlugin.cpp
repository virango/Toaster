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
#include "QToasterStompEditLCD.h"
#include "QToasterStompEditLCDPlugin.h"

#include <QtPlugin>

QToasterStompEditLCDPlugin::QToasterStompEditLCDPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QToasterStompEditLCDPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterStompEditLCDPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterStompEditLCDPlugin::createWidget(QWidget *parent)
{
  return new QToasterStompEditLCD(parent);
}

QString QToasterStompEditLCDPlugin::name() const
{
  return QLatin1String("QToasterStompEditLCD");
}

QString QToasterStompEditLCDPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterStompEditLCDPlugin::icon() const
{
  return QIcon();
}

QString QToasterStompEditLCDPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterStompEditLCDPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterStompEditLCDPlugin::isContainer() const
{
  return false;
}

QString QToasterStompEditLCDPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterStompEditLCD\" name=\"toasterStompEditLCD\">\n</widget>\n");
}

QString QToasterStompEditLCDPlugin::includeFile() const
{
  return QLatin1String("QToasterStompEditLCD.h");
}

