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
#include "QToasterLookUpTableDial.h"
#include "QToasterLookUpTableDialPlugin.h"

#include <QtPlugin>

QToasterLookUpTableDialPlugin::QToasterLookUpTableDialPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QToasterLookUpTableDialPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterLookUpTableDialPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterLookUpTableDialPlugin::createWidget(QWidget *parent)
{
  return new QToasterLookUpTableDial(parent);
}

QString QToasterLookUpTableDialPlugin::name() const
{
  return QLatin1String("QToasterLookUpTableDial");
}

QString QToasterLookUpTableDialPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterLookUpTableDialPlugin::icon() const
{
  return QIcon(":/resources/DialIcon.png");
}

QString QToasterLookUpTableDialPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterLookUpTableDialPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterLookUpTableDialPlugin::isContainer() const
{
  return false;
}

QString QToasterLookUpTableDialPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterLookUpTableDial\" name=\"qToasterLookUpTableDial\">\n</widget>\n");
}

QString QToasterLookUpTableDialPlugin::includeFile() const
{
  return QLatin1String("QToasterLookUpTableDial.h");
}

