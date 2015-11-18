#include "RotarySpeakerFrame.h"
#include "ui_RotarySpeakerFrame.h"
#include "Stomp.h"

RotarySpeakerFrame::RotarySpeakerFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::RotarySpeakerFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

RotarySpeakerFrame::~RotarySpeakerFrame()
{
  delete ui;
}

void RotarySpeakerFrame::activate(Stomp& stomp)
{
  mpStomp = &stomp;

  connect(mpStomp, SIGNAL(rotaryDistanceReceived(double)), this, SLOT(onDistance(double)));
  connect(mpStomp, SIGNAL(rotaryBalanceReceived(double)), this, SLOT(onLowHighBalance(double)));
  connect(mpStomp, SIGNAL(rotarySpeedReceived(::RotarySpeed)), this, SLOT(onRotarySpeed(::RotarySpeed)));
  connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
  connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));

  mpStomp->requestRotaryDistance();
  mpStomp->requestRotaryBalance();
  mpStomp->requestRotarySpeed();
  mpStomp->requestVolume();
  mpStomp->requestMix();
  mpStomp->requestDucking();

  ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(stomp.getInstance()));
}

void RotarySpeakerFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(rotaryDistanceReceived(double)), this, SLOT(onDistance(double)));
    disconnect(mpStomp, SIGNAL(rotaryBalanceReceived(double)), this, SLOT(onLowHighBalance(double)));
    disconnect(mpStomp, SIGNAL(rotarySpeedReceived(::RotarySpeed)), this, SLOT(onRotarySpeed(::RotarySpeed)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
  }
  mpStomp = nullptr;
}

void RotarySpeakerFrame::setFXType(FXType fxType)
{
  mFXType = fxType;
  ui->lcdDisplay->setStompName(LookUpTables::stompFXName(fxType));
}

void RotarySpeakerFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void RotarySpeakerFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void RotarySpeakerFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void RotarySpeakerFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void RotarySpeakerFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void RotarySpeakerFrame::on_distanceDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyRotaryDistance(value);
}

void RotarySpeakerFrame::on_lowHighBalanceDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyRotaryBalance(value);
}

void RotarySpeakerFrame::on_rotarySpeedDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyRotarySpeed((::RotarySpeed)value);
}

void RotarySpeakerFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void RotarySpeakerFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void RotarySpeakerFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void RotarySpeakerFrame::onDistance(double value)
{
  ui->distanceDial->setValue(value);
  update();
}

void RotarySpeakerFrame::onLowHighBalance(double value)
{
  ui->lowHighBalanceDial->setValue(value);
  update();
}

void RotarySpeakerFrame::onRotarySpeed(::RotarySpeed value)
{
  ui->rotarySpeedDial->setValue(value);
  update();
}

void RotarySpeakerFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void RotarySpeakerFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void RotarySpeakerFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}
