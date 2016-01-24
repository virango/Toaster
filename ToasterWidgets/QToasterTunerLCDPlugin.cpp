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
#include "QToasterTunerLCDPlugin.h"
#include "QToasterTunerLCD.h"

QToasterTunerLCDPlugin::QToasterTunerLCDPlugin(QObject *parent) :
  QObject(parent)
{
    m_initialized = false;
}

void QToasterTunerLCDPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterTunerLCDPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterTunerLCDPlugin::createWidget(QWidget *parent)
{
  return new QToasterTunerLCD(parent);
}

QString QToasterTunerLCDPlugin::name() const
{
  return QLatin1String("QToasterTunerLCD");
}

QString QToasterTunerLCDPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterTunerLCDPlugin::icon() const
{
  return QIcon();
}

QString QToasterTunerLCDPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterTunerLCDPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterTunerLCDPlugin::isContainer() const
{
  return false;
}

QString QToasterTunerLCDPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterTunerLCD\" name=\"toasterTunerLCD\">\n</widget>\n");
}

QString QToasterTunerLCDPlugin::includeFile() const
{
  return QLatin1String("QToasterTunerLCD.h");
}


