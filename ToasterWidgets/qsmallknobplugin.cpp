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
#include "qsmallknob.h"
#include "qsmallknobplugin.h"

#include <QtPlugin>

QSmallKnobPlugin::QSmallKnobPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QSmallKnobPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QSmallKnobPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QSmallKnobPlugin::createWidget(QWidget *parent)
{
  return new QSmallKnob(parent);
}

QString QSmallKnobPlugin::name() const
{
  return QLatin1String("QSmallKnob");
}

QString QSmallKnobPlugin::group() const
{
  return QLatin1String("");
}

QIcon QSmallKnobPlugin::icon() const
{
  return QIcon();
}

QString QSmallKnobPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QSmallKnobPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QSmallKnobPlugin::isContainer() const
{
  return false;
}

QString QSmallKnobPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QSmallKnob\" name=\"qSmallKnob\">\n</widget>\n");
}

QString QSmallKnobPlugin::includeFile() const
{
  return QLatin1String("qsmallknob.h");
}

