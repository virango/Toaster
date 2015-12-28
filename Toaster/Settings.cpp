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
