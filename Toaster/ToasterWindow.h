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
#ifndef TOASTERWINDOW_H
#define TOASTERWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "ConnectionStatusFrame.h"
#include "MidiConsumer.h"

namespace Ui {
class ToasterWindow;
}

class ToasterWindow : public QMainWindow, public IMidiConsumer
{
    Q_OBJECT

public:
    explicit ToasterWindow(QWidget *parent = 0);
    ~ToasterWindow();

signals:
  void connectionStatusChanged(bool midiConnected, bool kpaConnected, bool kpaDataReceived);

private slots:
  void onStartup();
  void on_actionRequestValues_triggered();
  void on_actionCmd_triggered();
  void on_actionConfigure_triggered();
  void on_actionOpenMIDIPorts_triggered();
  void on_actionConnectToKPA_triggered();
  void on_actionDisconnectFromKPA_triggered();
  void on_actionUploadKIPRFile_triggered();
  void on_actionExit_triggered();
  void on_actionClose_MIDI_Ports_triggered();
  void on_actionCreateStringValuesTable_triggered();
  void on_actionSendSySex_triggered();
  void on_actionDebugSettings_triggered();

  void on_actionAbout_triggered();

  void on_actionEditKIPRFile_triggered();

private:
  unsigned char getStatusByte() override { return 0xF0; }
  void consume(const ByteArray&) override {
      mDataReceivedfromKPA = true;
      emit connectionStatusChanged(mIsConnected2Midi, mIsConnected2KPA, mDataReceivedfromKPA);
  }

  //QTimer* timer;
  void showSettingsDialog();
  void openMidiPorts();

  Ui::ToasterWindow *ui;

  bool mIsConnected2Midi;
  bool mIsConnected2KPA;
  bool mDataReceivedfromKPA;

  ConnectionStatusFrame mConnectionStatus;
};

#endif // TOASTERWINDOW_H
