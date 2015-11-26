#include "MetalDSFrame.h"
#include "ui_MetalDSFrame.h"
#include "Stomp.h"

MetalDSFrame::MetalDSFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::MetalDSFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

MetalDSFrame::~MetalDSFrame()
{
  delete ui;
}

void MetalDSFrame::activate(Stomp& stomp)
{
  mpStomp = &stomp;

  connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  connect(mpStomp, SIGNAL(distortionShaperDriveReceived(double)), this, SLOT(onDrive(double)));
  connect(mpStomp, SIGNAL(parametricEQLowGainReceived(double)), this, SLOT(onLow(double)));
  connect(mpStomp, SIGNAL(parametricEQPeakGainReceived(double)), this, SLOT(onMiddle(double)));
  connect(mpStomp, SIGNAL(parametricEQPeakFrequencyReceived(double)), this, SLOT(onMidFreq(double)));
  connect(mpStomp, SIGNAL(parametricEQHighGainReceived(double)), this, SLOT(onHigh(double)));

  mpStomp->requestVolume();
  mpStomp->requestDistortionShaperDrive();
  mpStomp->requestParametricEQLowGain();
  mpStomp->requestParametricEQPeakGain();
  mpStomp->requestParametricEQPeakFrequency();
  mpStomp->requestParametricEQHighGain();

  ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(stomp.getInstance()));
}

void MetalDSFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(distortionShaperDriveReceived(double)), this, SLOT(onDrive(double)));
    disconnect(mpStomp, SIGNAL(parametricEQLowGainReceived(double)), this, SLOT(onLowDial(double)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakGainReceived(double)), this, SLOT(onMiddleDial(double)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakFrequencyReceived(double)), this, SLOT(onMidFreqDial(double)));
    disconnect(mpStomp, SIGNAL(parametricEQHighGainReceived(double)), this, SLOT(onHighDial(double)));
  }
  mpStomp = nullptr;
}

void MetalDSFrame::setFXType(FXType fxType)
{
  mFXType = fxType;
  ui->lcdDisplay->setStompName(LookUpTables::stompFXName(fxType));
}

void MetalDSFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void MetalDSFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void MetalDSFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void MetalDSFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void MetalDSFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void MetalDSFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void MetalDSFrame::on_driveDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionShaperDrive(value);
}

void MetalDSFrame::on_lowDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQLowGain(value);
}

void MetalDSFrame::on_middleDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakGain(value);
}

void MetalDSFrame::on_midFreqDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakFrequency(value);
}

void MetalDSFrame::on_highDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQHighGain(value);
}

void MetalDSFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void MetalDSFrame::onDrive(double value)
{
  ui->driveDial->setValue(value);
  update();
}

void MetalDSFrame::onLow(double value)
{
  ui->lowDial->setValue(value);
  update();
}

void MetalDSFrame::onMiddle(double value)
{
  ui->middleDial->setValue(value);
  update();
}

void MetalDSFrame::onMidFreq(double value)
{
  ui->midFreqDial->setValue(value);
  update();
}

void MetalDSFrame::onHigh(double value)
{
  ui->highDial->setValue(value);
  update();
}
