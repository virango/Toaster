#include "ToneAndDuckingDSFrame.h"
#include "ui_ToneAndDuckingDSFrame.h"
#include "Stomp.h"

ToneAndDuckingDSFrame::ToneAndDuckingDSFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::ToneAndDuckingDSFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

ToneAndDuckingDSFrame::~ToneAndDuckingDSFrame()
{
  delete ui;
}

void ToneAndDuckingDSFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(distortionBoosterToneReceived(double)), this, SLOT(onTone(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));

    mpStomp->requestVolume();
    mpStomp->requestDistortionBoosterTone();
    mpStomp->requestDucking();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void ToneAndDuckingDSFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(distortionBoosterToneReceived(double)), this, SLOT(onTone(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
  }
  mpStomp = nullptr;
}

void ToneAndDuckingDSFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void ToneAndDuckingDSFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void ToneAndDuckingDSFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void ToneAndDuckingDSFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void ToneAndDuckingDSFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void ToneAndDuckingDSFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void ToneAndDuckingDSFrame::on_toneDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionBoosterTone(value);
}

void ToneAndDuckingDSFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void ToneAndDuckingDSFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void ToneAndDuckingDSFrame::onTone(double value)
{
  ui->toneDial->setValue(value);
  update();
}

void ToneAndDuckingDSFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

