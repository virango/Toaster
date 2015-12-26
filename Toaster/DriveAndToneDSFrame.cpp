#include "DriveAndToneDSFrame.h"
#include "ui_DriveAndToneDSFrame.h"
#include "Stomp.h"

DriveAndToneDSFrame::DriveAndToneDSFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::DriveAndToneDSFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

DriveAndToneDSFrame::~DriveAndToneDSFrame()
{
  delete ui;
}

void DriveAndToneDSFrame::activate(QObject& stomp)
{
  mpStomp = dynamic_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(distortionShaperDriveReceived(double)), this, SLOT(onDrive(double)));
    connect(mpStomp, SIGNAL(distortionBoosterToneReceived(double)), this, SLOT(onTone(double)));

    mpStomp->requestVolume();
    mpStomp->requestDistortionShaperDrive();
    mpStomp->requestDistortionBoosterTone();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void DriveAndToneDSFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(distortionShaperDriveReceived(double)), this, SLOT(onDrive(double)));
    disconnect(mpStomp, SIGNAL(distortionBoosterToneReceived(double)), this, SLOT(onTone(double)));
  }
  mpStomp = nullptr;
}

void DriveAndToneDSFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void DriveAndToneDSFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void DriveAndToneDSFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void DriveAndToneDSFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void DriveAndToneDSFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void DriveAndToneDSFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void DriveAndToneDSFrame::on_driveDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionShaperDrive(value);
}

void DriveAndToneDSFrame::on_toneDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionBoosterTone(value);
}

void DriveAndToneDSFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void DriveAndToneDSFrame::onDrive(double value)
{
  ui->driveDial->setValue(value);
  update();
}

void DriveAndToneDSFrame::onTone(double value)
{
  ui->toneDial->setValue(value);
  update();
}
