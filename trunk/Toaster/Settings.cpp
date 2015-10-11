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

