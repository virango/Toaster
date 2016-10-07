#include "KPAOS4Checker.h"
#include "Settings.h"
#include "SettingsDialog.h"
#include "Midi.h"
#include "Stomp.h"

KPAOS4Checker::KPAOS4Checker(QObject *parent) : QObject(parent)
{
  mTimer = new QTimer(this);
}

KPAOS4Checker::~KPAOS4Checker()
{
  if(mTimer != nullptr)
  {
    delete mTimer;
    mTimer = nullptr;
  }
}


void KPAOS4Checker::check()
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
    QEventLoop el;
    el.connect(this, &KPAOS4Checker::stopLoop, &el, &QEventLoop::quit);
    el.connect(&stompDelayObj, &Stomp::onOffReceived, this, &KPAOS4Checker::onOfReceived);
    el.connect(mTimer, &QTimer::timeout, this, &KPAOS4Checker::timerTimeout);
    mTimer->start(500);
    stompDelayObj.requestOnOff();
    el.exec();
    el.disconnect(this, &KPAOS4Checker::stopLoop, &el, &QEventLoop::quit);
    el.disconnect(&stompDelayObj, &Stomp::onOffReceived, this, &KPAOS4Checker::onOfReceived);
    el.disconnect(mTimer, &QTimer::timeout, this, &KPAOS4Checker::timerTimeout);
  }
}

void KPAOS4Checker::onOfReceived(bool)
{
  if(mTimer != nullptr)
    mTimer->stop();

  Settings::get().setKPAOSVersion(0x04000000);

  emit stopLoop();
}

void KPAOS4Checker::timerTimeout()
{
  Settings::get().setKPAOSVersion(0x03000000);
  emit stopLoop();
}
