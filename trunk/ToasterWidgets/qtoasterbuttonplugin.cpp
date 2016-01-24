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
#include "qtoasterbutton.h"
#include "qtoasterbuttonplugin.h"

#include <QtPlugin>

QToasterButtonPlugin::QToasterButtonPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QToasterButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterButtonPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterButtonPlugin::createWidget(QWidget *parent)
{
  return new QToasterButton(parent);
}

QString QToasterButtonPlugin::name() const
{
  return QLatin1String("QToasterButton");
}

QString QToasterButtonPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterButtonPlugin::icon() const
{
  return QIcon(":/resources/ButtonIcon.png");
}

QString QToasterButtonPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterButtonPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterButtonPlugin::isContainer() const
{
  return false;
}

QString QToasterButtonPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterButton\" name=\"qToasterButton\">\n</widget>\n");
}

QString QToasterButtonPlugin::includeFile() const
{
  return QLatin1String("qtoasterbutton.h");
}

