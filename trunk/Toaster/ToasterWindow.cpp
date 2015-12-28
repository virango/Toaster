#include "ToasterWindow.h"
#include "ui_ToasterWindow.h"
#include "Midi.h"
#include "qtoasterdial.h"
#include "SettingsDialog.h"
#include "Settings.h"
#include "DebugMidi.h"
#include "DebugCreateStringValuesDialog.h"

ToasterWindow::ToasterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToasterWindow)
{
    ui->setupUi(this);

    if(!Settings::get().getDebuggerActive())
      ui->menuDebug->menuAction()->setVisible(false);

    QString inPort(Settings::get().getMidiInPort());
    QString outPort(Settings::get().getMidiOutPort());

    if(inPort.isEmpty() || outPort.isEmpty())
    {
      showSettingsDialog();
      inPort = Settings::get().getMidiInPort();
      outPort = Settings::get().getMidiOutPort();
    }

    Midi::get().openPorts(inPort, outPort);

    QTimer* timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_actionRequestValues_triggered()));
    timer->start(20);

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


void ToasterWindow::on_actionRequestValues_triggered()
{
#if 0
  static int val = 0;
  DebugMidi::get().debugRequestStringParam((unsigned short)val, 0x32, 0x2F);
  val++;
  if(val == 0x4000)
    timer->stop();
#else
  QString connectName("Toaster ");
  ui->mainFrame->connect2KPA(connectName);
  ui->mainFrame->requestValues();
#endif
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

}

void ToasterWindow::on_actionOpenMIDIPorts_triggered()
{

}

void ToasterWindow::on_actionClose_MIDI_Ports_triggered()
{

}

void ToasterWindow::on_actionConnectToKPA_triggered()
{
  QString connectName("Toaster ");
  ui->mainFrame->connect2KPA(connectName);
}

void ToasterWindow::on_actionDisconnectFromKPA_triggered()
{
  ui->mainFrame->disconnectFromKPA();
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
