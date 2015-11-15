#include "StereoWeidenerFrame.h"
#include "ui_StereoWeidenerFrame.h"
#include "Stomp.h"

StereoWeidenerFrame::StereoWeidenerFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::StereoWeidenerFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

StereoWeidenerFrame::~StereoWeidenerFrame()
{
  delete ui;
}

void StereoWeidenerFrame::activate(Stomp& stomp)
{
  mpStomp = &stomp;

  connect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onIntensity(double)));
  connect(mpStomp, SIGNAL(modulationRateReceived(double)), this, SLOT(onTune(double)));
  connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));

  mpStomp->requestModulationDepth();
  mpStomp->requestModulationRate();
  mpStomp->requestDucking();

  ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(stomp.getInstance()));
}

void StereoWeidenerFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onIntensity(double)));
    disconnect(mpStomp, SIGNAL(modulationRateReceived(double)), this, SLOT(onTune(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
  }
  mpStomp = nullptr;
}

void StereoWeidenerFrame::setFXType(FXType fxType)
{
  mFXType = fxType;
  ui->lcdDisplay->setStompName(LookUpTables::stompFXName(fxType));
}

void StereoWeidenerFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void StereoWeidenerFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void StereoWeidenerFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void StereoWeidenerFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void StereoWeidenerFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void StereoWeidenerFrame::on_intensityDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void StereoWeidenerFrame::on_tuneDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationRate(value);
}

void StereoWeidenerFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void StereoWeidenerFrame::onIntensity(double value)
{
  ui->intensityDial->setValue(value);
  update();
}

void StereoWeidenerFrame::onTune(double value)
{
  ui->tuneDial->setValue(value);
  update();
}

void StereoWeidenerFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}
