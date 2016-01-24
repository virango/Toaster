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
#include "Settings.h"

Settings::Settings()
  : QSettings(IniFormat, UserScope, "Toaster", "Toaster")
{
}

Settings& Settings::get()
{
  static Settings singleton;
  return singleton;
}

QString Settings::getMidiInPort()
{
  return value("MIDI/InPort", QVariant("")).toString();
}

void Settings::setMidiInPort(const QString& inPort)
{
  setValue("MIDI/InPort", QVariant(inPort));
}

QString Settings::getMidiOutPort()
{
  return value("MIDI/OutPort", QVariant("")).toString();
}

void Settings::setMidiOutPort(const QString& outPort)
{
  setValue("MIDI/OutPort", QVariant(outPort));
}

bool Settings::getDebuggerActive()
{
  return value("Debug/Active", QVariant(false)).toBool();
}

QString Settings::getDebugWriteStringValuesFileName()
{
  return value("Debug/WriteStringValuesFileName", QVariant("")).toString();
}

void Settings::setDebugWriteStringValuesFileName(const QString& fileName)
{
  setValue("Debug/WriteStringValuesFileName", QVariant(fileName));
}

bool Settings::getDebugPrintValues()
{
  return value("Debug/PrintValues", QVariant(true)).toBool();
}

void Settings::setDebugPrintValues(bool printValues)
{
  setValue("Debug/PrintValues", QVariant(printValues));
}

bool Settings::getDebugWriteStringValues()
{
  return value("Debug/WriteStringValues", QVariant(true)).toBool();
}

void Settings::setDebugWriteStringValues(bool writeStringValues)
{
  setValue("Debug/WriteStringValues", QVariant(writeStringValues));
}
