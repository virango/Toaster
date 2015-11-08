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

  QString getDebugWriteStringValuesFileName();
  void setDebugWriteStringValuesFileName(const QString& fileName);

  bool getDebugPrintValues();
  void setDebugPrintValues(bool printValues);

  bool getDebugWriteStringValues();
  void setDebugWriteStringValues(bool writeStringValues);

};

#endif // SETTINGS_H
