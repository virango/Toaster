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

  bool getDebuggerActive();

  QString getDebugWriteStringValuesFileName();
  void setDebugWriteStringValuesFileName(const QString& fileName);

  bool getDebugPrintValues();
  void setDebugPrintValues(bool printValues);

  bool getDebugWriteStringValues();
  void setDebugWriteStringValues(bool writeStringValues);

};

#endif // SETTINGS_H
