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
    connect(timer, SIGNAL(timeout()), this, SLOT(onStartup()));
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
  QString inPort(Settings::get().getMidiInPort());
  QString outPort(Settings::get().getMidiOutPort());

  if(inPort.isEmpty() || outPort.isEmpty())
  {
    showSettingsDialog();
    inPort = Settings::get().getMidiInPort();
    outPort = Settings::get().getMidiOutPort();
  }

  mIsConnected2Midi = Midi::get().openPorts(inPort, outPort);
  if(mIsConnected2Midi)
    ui->statusBar->showMessage("Midi connected");  

  emit connectionStatusChanged(mIsConnected2Midi, mIsConnected2KPA);
}

void ToasterWindow::on_actionCmd_triggered()
{
  ByteArray ap;
  ByteArray param;
  ByteArray value;
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

  ap.push_back(0x7d);
  param.push_back(0x0);
  value.push_back(0x00);
  value.push_back(0x00);
  DebugMidi::get().debugSendSingleParam(ap, param, value);


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

/*
  DebugMidi::get().debugRequestExtStringParam(0x4101);
  DebugMidi::get().debugRequestExtParam(0x4101);

  DebugMidi::get().debugRequestExtStringParam(0x4000);
  DebugMidi::get().debugRequestExtParam(0x4000);
*/
}

void ToasterWindow::on_actionUploadKIPRFile_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  QStandardPaths::locate(QStandardPaths::HomeLocation, ""),
                                                  tr("KPA-Profiles (*.kipr)"));

  if(fileName.isEmpty())
    return;

  QFile kiprFile(fileName);
  kiprFile.open(QIODevice::ReadOnly);
  QDataStream stream(&kiprFile);
  unsigned int magic;
  stream.readRawData((char*)&magic, 4);
  if(magic == 0x6468544d || magic == 0x6468544b)
  {
    stream.skipRawData(16);
    unsigned char tmp[2];
    stream.readRawData((char*)tmp, 2);
    unsigned short dataBytesInFile = (tmp[0] << 8) | tmp[1];
    if(dataBytesInFile == kiprFile.bytesAvailable())
    {
      while(!stream.atEnd())
      {
        unsigned char c;
        stream.readRawData((char*)&c, 1);
        if(c == 0xF0)
        {
          ByteArray midiCmd;
          midiCmd.push_back(c);
          unsigned char  len;
          stream.readRawData((char*)&len, 1);
          //midiCmd.push_back(len);
          unsigned char buf[255];
          stream.readRawData((char*)buf, len);
          for(unsigned char i = 0; i < len; ++i)
            midiCmd.push_back(buf[i]);
          Midi::get().sendCmd(midiCmd);
        }
      }
    }
  }
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
