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
#include "qtoasterenumdial.h"
#include "qtoasterenumdialplugin.h"

#include <QtPlugin>

QToasterEnumDialPlugin::QToasterEnumDialPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QToasterEnumDialPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterEnumDialPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterEnumDialPlugin::createWidget(QWidget *parent)
{
  return new QToasterEnumDial(parent);
}

QString QToasterEnumDialPlugin::name() const
{
  return QLatin1String("QToasterEnumDial");
}

QString QToasterEnumDialPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterEnumDialPlugin::icon() const
{
  return QIcon(":/resources/DialIcon.png");
}

QString QToasterEnumDialPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterEnumDialPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterEnumDialPlugin::isContainer() const
{
  return false;
}

QString QToasterEnumDialPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterEnumDial\" name=\"qToasterEnumDial\">\n</widget>\n");
}

QString QToasterEnumDialPlugin::includeFile() const
{
  return QLatin1String("qtoasterenumdial.h");
}
