#include "DriveDSFrame.h"
#include "ui_DriveDSFrame.h"
#include "Stomp.h"

DriveDSFrame::DriveDSFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::DriveDSFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

DriveDSFrame::~DriveDSFrame()
{
  delete ui;
}

void DriveDSFrame::activate(Stomp& stomp)
{
  mpStomp = &stomp;

  connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  connect(mpStomp, SIGNAL(distortionShaperDriveReceived(double)), this, SLOT(onDrive(double)));

  mpStomp->requestVolume();
  mpStomp->requestDistortionShaperDrive();

  ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(stomp.getInstance()));
}

void DriveDSFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(driveReceived(double)), this, SLOT(onDrive(double)));
  }
  mpStomp = nullptr;
}

void DriveDSFrame::setFXType(FXType fxType)
{
  mFXType = fxType;
  ui->lcdDisplay->setStompName(LookUpTables::stompFXName(fxType));
}

void DriveDSFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void DriveDSFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void DriveDSFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void DriveDSFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void DriveDSFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void DriveDSFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void DriveDSFrame::on_driveDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionShaperDrive(value);
}

void DriveDSFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void DriveDSFrame::onDrive(double value)
{
  ui->driveDial->setValue(value);
  update();
}
