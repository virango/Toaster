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
#include "ToasterWindow.h"
#include <QApplication>
#include "KPAOS4Checker.h"

/*
void TryToGetKPAOSVersion()
{
  QString inPort(Settings::get().getMidiInPort());
  QString outPort(Settings::get().getMidiOutPort());

  if(inPort.isEmpty() || outPort.isEmpty())
  {
    SettingsDialog settingsDialog(nullptr);
    settingsDialog.exec();
    inPort = Settings::get().getMidiInPort();
    outPort = Settings::get().getMidiOutPort();
  }

  if(Midi::get().openPorts(inPort, outPort))
  {
    connect
    stompDelayObj.requestOnOff();
  }
}
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    KPAOS4Checker osChecker;
    osChecker.check();

    ToasterWindow w;
    w.show();

    return a.exec();
}
