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
#include "qmulticolorled.h"
#include "qmulticolorledplugin.h"

#include <QtPlugin>

QMultiColorLedPlugin::QMultiColorLedPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QMultiColorLedPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QMultiColorLedPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QMultiColorLedPlugin::createWidget(QWidget *parent)
{
  return new QMultiColorLed(parent);
}

QString QMultiColorLedPlugin::name() const
{
  return QLatin1String("QMultiColorLed");
}

QString QMultiColorLedPlugin::group() const
{
  return QLatin1String("");
}

QIcon QMultiColorLedPlugin::icon() const
{
  return QIcon();
}

QString QMultiColorLedPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QMultiColorLedPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QMultiColorLedPlugin::isContainer() const
{
  return false;
}

QString QMultiColorLedPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QMultiColorLed\" name=\"qMultiColorLed\">\n</widget>\n");
}

QString QMultiColorLedPlugin::includeFile() const
{
  return QLatin1String("qmulticolorled.h");
}

