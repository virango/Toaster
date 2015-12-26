#include "RectiShaperFrame.h"
#include "ui_RectiShaperFrame.h"
#include "Stomp.h"

RectiShaperFrame::RectiShaperFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::RectiShaperFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

RectiShaperFrame::~RectiShaperFrame()
{
  delete ui;
}

void RectiShaperFrame::activate(QObject& stomp)
{
  mpStomp = dynamic_cast<Stomp*>(&stomp);

  connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  connect(mpStomp, SIGNAL(distortionShaperDriveReceived(double)), this, SLOT(onDrive(double)));
  connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));

  mpStomp->requestVolume();
  mpStomp->requestDistortionShaperDrive();
  mpStomp->requestDucking();

  ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
  ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
}

void RectiShaperFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(distortionShaperDriveReceived(double)), this, SLOT(onDrive(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
  }
  mpStomp = nullptr;
}

void RectiShaperFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void RectiShaperFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void RectiShaperFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void RectiShaperFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void RectiShaperFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void RectiShaperFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void RectiShaperFrame::on_driveDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionShaperDrive(value);
}

void RectiShaperFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void RectiShaperFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void RectiShaperFrame::onDrive(double value)
{
  ui->driveDial->setValue(value);
  update();
}

void RectiShaperFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}
