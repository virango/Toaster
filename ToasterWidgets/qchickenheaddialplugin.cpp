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
#include "qchickenheaddial.h"
#include "qchickenheaddialplugin.h"

#include <QtPlugin>

QChickenHeadDialPlugin::QChickenHeadDialPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QChickenHeadDialPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QChickenHeadDialPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QChickenHeadDialPlugin::createWidget(QWidget *parent)
{
  return new QChickenHeadDial(parent);
}

QString QChickenHeadDialPlugin::name() const
{
  return QLatin1String("QChickenHeadDial");
}

QString QChickenHeadDialPlugin::group() const
{
  return QLatin1String("");
}

QIcon QChickenHeadDialPlugin::icon() const
{
  return QIcon(":/resources/ChickeHeadDialIcon.png");
}

QString QChickenHeadDialPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QChickenHeadDialPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QChickenHeadDialPlugin::isContainer() const
{
  return false;
}

QString QChickenHeadDialPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QChickenHeadDial\" name=\"qChickenHeadDial\">\n</widget>\n");
}

QString QChickenHeadDialPlugin::includeFile() const
{
  return QLatin1String("qchickenheaddial.h");
}

