#include "CompressorFrame.h"
#include "ui_CompressorFrame.h"
#include "Stomp.h"

CompressorFrame::CompressorFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::CompressorFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

CompressorFrame::~CompressorFrame()
{
  delete ui;
}
void CompressorFrame::activate(Stomp& stomp)
{
  mpStomp = &stomp;

  connect(mpStomp, SIGNAL(compressorGateIntensityReceived(double)), this, SLOT(onIntensity(double)));
  connect(mpStomp, SIGNAL(compressorAttackReceived(double)), this, SLOT(onAttack(double)));
  connect(mpStomp, SIGNAL(compressorSquashReceived(double)), this, SLOT(onSquash(double)));
  connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));

  mpStomp->requestCompressorGateIntensity();
  mpStomp->requestCompressorAttack();
  mpStomp->requestCompressorSquash();
  mpStomp->requestVolume();
  mpStomp->requestMix();

  ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(stomp.getInstance()));
}

void CompressorFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(compressorGateIntensityReceived(double)), this, SLOT(onIntensity(double)));
    disconnect(mpStomp, SIGNAL(compressorAttackReceived(double)), this, SLOT(onAttack(double)));
    disconnect(mpStomp, SIGNAL(compressorSquashReceived(double)), this, SLOT(onSquash(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
  }

  mpStomp = nullptr;
}

void CompressorFrame::setFXType(FXType fxType)
{
  mFXType = fxType;
  ui->lcdDisplay->setStompName(LookUpTables::stompFXName(fxType));
}
void CompressorFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void CompressorFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void CompressorFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void CompressorFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void CompressorFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void CompressorFrame::on_intensityDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyCompressorGateIntensity(value);
}

void CompressorFrame::on_attackDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyCompressorAttack(value);
}

void CompressorFrame::on_squashDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyCompressorSquash(value);
}

void CompressorFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void CompressorFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void CompressorFrame::onIntensity(double value)
{
  ui->intensityDial->setValue(value);
  update();
}
void CompressorFrame::onAttack(double value)
{
  ui->attackDial->setValue(value);
  update();
}

void CompressorFrame::onSquash(double value)
{
  ui->squashDial->setValue(value);
  update();
}

void CompressorFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void CompressorFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}
