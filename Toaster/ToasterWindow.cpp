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
#include <QFileDialog>
#include "ToasterWindow.h"
#include "ui_ToasterWindow.h"
#include "Midi.h"
#include "qtoasterdial.h"
#include "SettingsDialog.h"
#include "Settings.h"
#include "DebugMidi.h"
#include "DebugCreateStringValuesDialog.h"
#include "AboutDialog.h"
#include "VirtualKPA.h"

ToasterWindow::ToasterWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::ToasterWindow)
  , mIsConnected2Midi(false)
  , mIsConnected2KPA(false)
{
  ui->setupUi(this);
  ui->statusBar->addPermanentWidget(&mConnectionStatus);

  QString title = "Toaster " + QString(APP_VERSION) + QString(" ") + QString(APP_STAGE);
  setWindowTitle(title);

  connect(this, &ToasterWindow::connectionStatusChanged,
          [=](bool midiConnected, bool) { ui->actionUploadKIPRFile->setEnabled(midiConnected); });
  connect(this, &ToasterWindow::connectionStatusChanged,
          [=](bool midiConnected, bool) { ui->actionClose_MIDI_Ports->setEnabled(midiConnected); });
  connect(this, &ToasterWindow::connectionStatusChanged,
          [=](bool midiConnected, bool) { ui->actionRequestValues->setEnabled(midiConnected); });
  connect(this, &ToasterWindow::connectionStatusChanged,
          [=](bool midiConnected, bool) { ui->actionOpenMIDIPorts->setDisabled(midiConnected); });
  connect(this, &ToasterWindow::connectionStatusChanged,
          [=](bool midiConnected, bool kpaConnected) { ui->actionDisconnectFromKPA->setEnabled(midiConnected && kpaConnected); });
  connect(this, &ToasterWindow::connectionStatusChanged,
          [=](bool midiConnected, bool kpaConnected) { ui->actionConnectToKPA->setEnabled(midiConnected && !kpaConnected);});
  connect(this, &ToasterWindow::connectionStatusChanged,
          [=](bool midiConnected, bool) { mConnectionStatus.setMidiStatus(midiConnected); });
  connect(this, &ToasterWindow::connectionStatusChanged,
          [=](bool midiConnected, bool kpaConnected) { mConnectionStatus.setKPAStatus(midiConnected && kpaConnected); });

  if(!Settings::get().getDebuggerActive())
    ui->menuDebug->menuAction()->setVisible(false);

  openMidiPorts();

  if(mIsConnected2Midi)
  {
    QTimer* timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &ToasterWindow::onStartup);
    timer->start(20);
  }

  qRegisterMetaType<::FXType>("::FXType");
  qRegisterMetaType<::WahPedalMode>("::WahPedalMode");
  qRegisterMetaType<::RotarySpeed>("::RotarySpeed");
  qRegisterMetaType<::DelayType>("::DelayType");
  qRegisterMetaType<::ReverbType>("::ReverbType");
  qRegisterMetaType<::DelayRatio>("::DelayRatio");
  qRegisterMetaType<::DelayClock>("::DelayClock");
}

ToasterWindow::~ToasterWindow()
{
  ui->mainFrame->disconnectFromKPA();
  Midi::get().closePorts();
  if(ui != nullptr)
    delete ui;
}

void ToasterWindow::onStartup()
{
  QString connectName("Toaster ");
  ui->mainFrame->connect2KPA(connectName);
  ui->mainFrame->requestValues();
  mIsConnected2KPA = true;
  emit connectionStatusChanged(mIsConnected2Midi, mIsConnected2KPA);
}

void ToasterWindow::on_actionRequestValues_triggered()
{
  ui->mainFrame->requestValues();
}

void ToasterWindow::on_actionConfigure_triggered()
{
  showSettingsDialog();
}

void ToasterWindow::showSettingsDialog()
{
  SettingsDialog settingsDialog(this);
  settingsDialog.exec();
}

void ToasterWindow::openMidiPorts()
{
  if(!Midi::get().arePortsOpen())
  {
    QString inPort(Settings::get().getMidiInPort());
    QString outPort(Settings::get().getMidiOutPort());

    if(inPort.isEmpty() || outPort.isEmpty())
    {
      showSettingsDialog();
      inPort = Settings::get().getMidiInPort();
      outPort = Settings::get().getMidiOutPort();
    }

    mIsConnected2Midi = Midi::get().openPorts(inPort, outPort);
  }
  else
  {
    mIsConnected2Midi = true;
  }

  if(mIsConnected2Midi)
    ui->statusBar->showMessage("Midi connected");  

  emit connectionStatusChanged(mIsConnected2Midi, mIsConnected2KPA);
}

void ToasterWindow::on_actionCmd_triggered()
{
  QByteArray ap;
  QByteArray param;
  QByteArray value;
/* Jumping to rig number 1
  ap.push_back(0x0);
  ap.push_back(0x0);
  ap.push_back(0x6);
  ap.push_back(0xd);
  ap.push_back(0x21);
  param.push_back(0x0);
  param.push_back(0x0);
  param.push_back(0x0);
  param.push_back(0x0);
  param.push_back(0x01);
  DebugMidi::get().debugSendExtParam(0x186a1, 1);*/

  //ap.push_back(0x7d);
  //param.push_back(0x0);
  //value.push_back(0x00);
  //value.push_back(0x00);
  //DebugMidi::get().debugSendSingleParam(ap, param, value);


  //DebugMidi::get().debugRequestExtParam(0x186a1);
/*
  ap.clear();
  param.clear();

  ap.push_back(0x0);
  ap.push_back(0x0);
  ap.push_back(0x1);
  ap.push_back(0x2);
  ap.push_back(0x0);
  param.push_back(0x0);
  param.push_back(0x0);
  param.push_back(0x0);
  param.push_back(0x0);
  param.push_back(0x0);
  DebugMidi::get().debugSendExtParam(ap, param, value);
*/


  DebugMidi::get().debugRequestExtStringParam(0x4101);
  DebugMidi::get().debugRequestExtParam(0x4101);

  DebugMidi::get().debugRequestExtStringParam(0x4000);
  DebugMidi::get().debugRequestExtParam(0x4000);

}

void ToasterWindow::on_actionUploadKIPRFile_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  QStandardPaths::locate(QStandardPaths::HomeLocation, ""),
                                                  tr("KPA-Profiles (*.kipr)"));

  if(fileName.isEmpty())
    return;
#if 0
  VirtualKPA& vk = VirtualKPA::get();
  VirtualRig* vr = vk.loadRig(fileName);
  QString newFileName = fileName + "_save";
  vk.saveRig(*vr, newFileName);
#else
  QFile kiprFile(fileName);
  QFileInfo kiprFileInfo(fileName);
  QString rigName = kiprFileInfo.fileName();
  kiprFile.open(QIODevice::ReadOnly);
  QDataStream stream(&kiprFile);
  //unsigned int magic;
  //stream.readRawData((char*)&magic, 4);
  // if(magic == 0x6468544d || magic == 0x6468544b)
  {
    //stream.skipRawData(16);
    //unsigned char tmp[2];
    //stream.readRawData((char*)tmp, 2);
    //unsigned short dataBytesInFile = (tmp[0] << 8) | tmp[1];
    //if(dataBytesInFile == kiprFile.bytesAvailable())
    {
      ui->mainFrame->disconnectFromKPA();

      qint64 fileSize = kiprFile.bytesAvailable();
      ByteArray buf(fileSize);
      stream.readRawData((char*)buf.data(), fileSize);
      QByteArray qba((char*)buf.data(), fileSize);
      QByteArray base64(qba.toBase64());

      unsigned short crc = Utils::crc14(buf);

      ByteArray c1 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x01,0x00,0x7f,0x7c,0x00,0x00,0xf7};
      ByteArray c2 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x03,0x00,0x7f,0x7d};
      QString appName("Toaster");
      for(int i = 0; i < appName.length(); ++i)
        c2.push_back(appName.at(i).toLatin1());
      c2.push_back(0x00);
      c2.push_back(0xf7);
      ByteArray c3 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x03,0x00,0x7f,0x7c,0x52,0x65,0x63,0x65,0x69,0x76,0x69,0x6e,0x67,0x20,0x52,0x69,0x67,0x73,0x2e,0x2e,0x2e,0x00,0xf7};
      ByteArray c4 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x03,0x00,0x7f,0x7c,0x52,0x65,0x63,0x65,0x69,0x76,0x69,0x6e,0x67,0x20,0x69,0x74,0x65,0x6d,0x20,0x31,0x20,0x6f,0x66,0x20,0x31,0x00,0xf7};
      ByteArray c5 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x03,0x00,0x7f,0x7b,0x00,0xf7};

      Midi::get().sendCmd(c1);
      Midi::get().sendCmd(c2);
      Midi::get().sendCmd(c3);
      Midi::get().sendCmd(c4);
      Midi::get().sendCmd(c5);

      // todo: find out the meaning of the last value 0x4e
      ByteArray r1 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x7e,0x00,0x03,0x01,0x00,0x00,0x4e,0xf7};
      {
        Midi::get().sendCmd(r1);QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                                                QStandardPaths::locate(QStandardPaths::HomeLocation, ""),
                                                                                tr("KPA-Profiles (*.kipr)"));
      }

      ByteArray s2 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x7e,0x00,0x06,0x01};

      char crcMsb = (crc >> 7) & 0x7F;
      char crcLsb = crc & 0x7F;

      s2.push_back(crcMsb);
      s2.push_back(crcLsb);
      s2.push_back(0xf7);

      int index = 0;
      bool loop = true;
      while(loop)
      {
        int len;
        if(base64.size() > (index + 1024))
        {
          len = 1024;
        }
        else
        {
          len = base64.size() - index;
          loop = false;
        }
        QByteArray chunk = base64.mid(index, len);
        ByteArray r2 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x7e,0x00,0x04,0x01};
        for(int i= 0; i < chunk.size(); i++)
        {
          r2.push_back(chunk[i]);
        }
        r2.push_back(0xf7);
        Midi::get().sendCmd(r2);
        index += len;
      }

#if 0
      while(!stream.atEnd())
      {
        unsigned char c;
        stream.readRawData((char*)&c, 1);
        if(c == 0xF0)
        {
          QByteArray midiCmd;
          midiCmd.push_back(c);
          unsigned short  len = 0;
          stream.readRawData((char*)&c, 1);
          if((c & 0x80) != 0)
          {
            unsigned char d;
            stream.readRawData((char*)&d, 1);
            len = (((unsigned short)c & 0x7F) << 7) | ((unsigned short)d & 0x7F);
          }
          else
          {
            len = c;
          }
          //midiCmd.push_back(len);
          unsigned char buf[0x4000];
          stream.readRawData((char*)buf, len);
          for(unsigned short i = 0; i < len; ++i)
            midiCmd.push_back(buf[i]);
          Midi::get().sendCmd(midiCmd);
        }
      }
#endif



      Midi::get().sendCmd(s2);

      ByteArray cmd1 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x7e,0x00,0x02,0x01,0x01,0x00};
      ByteArray cmd2 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x7e,0x00,0x08,0x01};
      for(int i = 0; i < rigName.length(); ++i)
      {
        cmd1.push_back(rigName.at(i).toLatin1());
        cmd2.push_back(rigName.at(i).toLatin1());
      }
      cmd1.push_back(0xf7);
      cmd2.push_back(0);
      cmd2.push_back(0xf7);
      Midi::get().sendCmd(cmd1);
      Midi::get().sendCmd(cmd2);

      ByteArray e1(c1);
      ByteArray e2(c2);
      ByteArray e3 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x03,0x00,0x7f,0x7c,0x52,0x65,0x63,0x65,0x69,0x76,0x69,0x6e,0x67,0x20,0x69,0x74,0x65,0x6d,0x20,0x31,0x20,0x6f,0x66,0x20,0x31,0x00,0xf7};
      ByteArray e4 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x03,0x00,0x7f,0x7b,0x00,0xf7};
      ByteArray e5 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x01,0x00,0x7f,0x7c,0x00,0x64,0xf7};
      ByteArray e6 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x01,0x00,0x7f,0x7c,0x00,0x00,0xf7};
      ByteArray e7 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x03,0x00,0x7f,0x7d,0x00,0xf7};
      ByteArray e8 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x03,0x00,0x7f,0x7c,0x00,0xf7};
      ByteArray e9 = {0xf0,0x00,0x20,0x33,0x02,0x7f,0x03,0x00,0x7f,0x7b,0x00,0xf7};

      Midi::get().sendCmd(e1);
      Midi::get().sendCmd(e2);
      Midi::get().sendCmd(e3);
      Midi::get().sendCmd(e4);
      Midi::get().sendCmd(e5);
      Midi::get().sendCmd(e6);
      Midi::get().sendCmd(e7);
      Midi::get().sendCmd(e8);
      Midi::get().sendCmd(e9);

      ui->mainFrame->connect2KPA("Toaster ");
    }
  }
#endif
}

void ToasterWindow::on_actionOpenMIDIPorts_triggered()
{
  openMidiPorts();
}

void ToasterWindow::on_actionClose_MIDI_Ports_triggered()
{
  on_actionDisconnectFromKPA_triggered();
  Midi::get().closePorts();
  mIsConnected2KPA = false;
  mIsConnected2Midi = false;
  emit connectionStatusChanged(mIsConnected2Midi, mIsConnected2KPA);
}

void ToasterWindow::on_actionConnectToKPA_triggered()
{
  QString connectName("Toaster ");
  ui->mainFrame->connect2KPA(connectName);
  mIsConnected2KPA = true;
  emit connectionStatusChanged(mIsConnected2Midi, mIsConnected2KPA);
}

void ToasterWindow::on_actionDisconnectFromKPA_triggered()
{
  ui->mainFrame->disconnectFromKPA();
  mIsConnected2KPA = false;
  emit connectionStatusChanged(mIsConnected2Midi, mIsConnected2KPA);
}

void ToasterWindow::on_actionExit_triggered()
{
  QApplication::quit();
}

void ToasterWindow::on_actionCreateStringValuesTable_triggered()
{
  on_actionDisconnectFromKPA_triggered();
  DebugCreateStringValuesDialog d;
  d.exec();
  on_actionConnectToKPA_triggered();
}

void ToasterWindow::on_actionSendSySex_triggered()
{

  // request all rig name infos NOTE: crashes the KPA
  ByteArray ap;
  ByteArray param;
  ByteArray value;

  ap.push_back(0x07);
  //param.push_back(0x03);
  param.push_back(0x00);
  value.push_back(0x01);

  DebugMidi::get().debugSendReserveFct7E(ap, param, value);

  ap.clear();
  value.clear();


  ap.push_back(0x05);

  //DebugMidi::get().debugSendReserveFct7E(ap, param, value);


  /*
  // request a rig
  ByteArray ap;
  ByteArray param;
  // parameter is here the rig file name <name>-<date> <time>.kipr
  QByteArray value = {0x01,0x4F,0x41,0x2D,0x47,0x69,0x6C,0x6D,0x6F,0x75,0x72,0x20,0x2D,0x20,0x32,0x30,0x31,0x36,0x2D,0x30,0x39,0x2D,0x30,0x36,0x20,0x31,0x38,0x2D,0x32,0x31,0x2D,0x31,0x39,0x2E,0x6B,0x69,0x70,0x72,0x00};

  ap.push_back(0x01);
  param.push_back(0x00);

  DebugMidi::get().debugSendReserveFct7E(ap, param, value);

  ap.clear();
  param.clear();
  value.clear();

  ap.push_back(0x05);
  param.push_back(0x00);

  DebugMidi::get().debugSendReserveFct7E(ap, param, value);
  */

/*
  DebugMidi::get().debugRequestExtStringParam(0x1863c);
  DebugMidi::get().debugRequestExtParam(0x1863c);

  DebugMidi::get().debugRequestExtStringParam(0x4000);  // works
  DebugMidi::get().debugRequestExtParam(0x4000);        // works not
*/
}

void ToasterWindow::on_actionDebugSettings_triggered()
{

}

void ToasterWindow::on_actionAbout_triggered()
{
  AboutDialog d;
  d.setVersionString(QString(APP_VERSION) + QString(" ") + QString(APP_STAGE));
  d.exec();
}

void ToasterWindow::on_actionEditKIPRFile_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  QStandardPaths::locate(QStandardPaths::HomeLocation, ""),
                                                  tr("KPA-Profiles (*.kipr)"));

  VirtualKPA& vk = VirtualKPA::get();
  VirtualRig* vr = vk.loadRig(fileName);
  ui->mainFrame->requestValues();
}
