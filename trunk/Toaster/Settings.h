#ifndef SETTINGS_H
#define SETTINGS_H
#include "QSettings"

#define SETTINGS Settings::get()

class Settings : public QSettings
{
  Settings();
public:
  static Settings& get();

  QString getMidiInPort();
  void setMidiInPort(const QString& inPort);

  QString getMidiOutPort();
  void setMidiOutPort(const QString& outPort);

};

#endif // SETTINGS_H
