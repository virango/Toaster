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
#include "qsmalldial.h"
#include "qsmalldialplugin.h"

#include <QtPlugin>

QSmallDialPlugin::QSmallDialPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QSmallDialPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QSmallDialPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QSmallDialPlugin::createWidget(QWidget *parent)
{
  return new QSmallDial(parent);
}

QString QSmallDialPlugin::name() const
{
  return QLatin1String("QSmallDial");
}

QString QSmallDialPlugin::group() const
{
  return QLatin1String("");
}

QIcon QSmallDialPlugin::icon() const
{
  return QIcon();
}

QString QSmallDialPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QSmallDialPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QSmallDialPlugin::isContainer() const
{
  return false;
}

QString QSmallDialPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QSmallDial\" name=\"qSmallDial\">\n</widget>\n");
}

QString QSmallDialPlugin::includeFile() const
{
  return QLatin1String("qsmalldial.h");
}

