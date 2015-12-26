#include "FlangerFrame.h"
#include "ui_FlangerFrame.h"
#include "Stomp.h"

FlangerFrame::FlangerFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::FlangerFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

FlangerFrame::~FlangerFrame()
{
  delete ui;
}
void FlangerFrame::activate(QObject& stomp)
{
  mpStomp = dynamic_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(modulationRateReceived(double, unsigned short)), this, SLOT(onRate(double, unsigned short)));
    connect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDepth(double)));
    connect(mpStomp, SIGNAL(modulationManualReceived(double)), this, SLOT(onManual(double)));
    connect(mpStomp, SIGNAL(modulationFeedbackReceived(double)), this, SLOT(onFeedback(double)));
    connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));

    mpStomp->requestModulationRate();
    mpStomp->requestModulationDepth();
    mpStomp->requestModulationManual();
    mpStomp->requestModulationFeedback();
    mpStomp->requestMix();
    mpStomp->requestDucking();
    mpStomp->requestVolume();

    mFXType = mpStomp->getFXType();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mFXType));

    if(mFXType == FlangerOneway)
    {
      ui->rateDial->setLEDRingType(QToasterDial::Bi);
      ui->rateDial->setMinValue(-5.0);
      ui->rateDial->setMaxValue(5.0);
      ui->rateDial->setStepWidth(0.1);
      ui->rateDial->setPrecision(1);

      ui->manualDial->setLEDRingType(QToasterDial::Bi);
      ui->manualDial->setMinValue(-5.0);
      ui->manualDial->setMaxValue(5);
    }
    else
    {
      ui->rateDial->setLEDRingType(QToasterDial::Uni);
      ui->rateDial->setMinValue(0.0);
      ui->rateDial->setMaxValue(16383.0);
      ui->rateDial->setStepWidth(1.0);
      ui->rateDial->setPrecision(0);

      ui->manualDial->setLEDRingType(QToasterDial::Uni);
      ui->manualDial->setMinValue(0);
      ui->manualDial->setMaxValue(10);
    }
  }
}

void FlangerFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(modulationRateReceived(double, unsigned short)), this, SLOT(onRate(double, unsigned short)));
    disconnect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDepth(double)));
    disconnect(mpStomp, SIGNAL(modulationManualReceived(double)), this, SLOT(onManual(double)));
    disconnect(mpStomp, SIGNAL(modulationFeedbackReceived(double)), this, SLOT(onFeedback(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));

    mFXType = None;
  }

  mpStomp = nullptr;
}

void FlangerFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void FlangerFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void FlangerFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void FlangerFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void FlangerFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void FlangerFrame::on_rateDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
  {
    if(mFXType == FlangerOneway)
      mpStomp->applyModulationRate(value + 5.0);
    else
      mpStomp->applyModulationRate(value);
  }
}

void FlangerFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void FlangerFrame::on_manualDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
  {
    if(mFXType == FlangerOneway)
      mpStomp->applyModulationManual(value + 5.0);
    else
      mpStomp->applyModulationManual(value);
  }
}

void FlangerFrame::on_feedbackDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationFeedback(value);
}

void FlangerFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void FlangerFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void FlangerFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void FlangerFrame::onRate(double value, unsigned short rawVal)
{
  if(mFXType == FlangerOneway)
    ui->rateDial->setValue(value - 5.0);
  else
    ui->rateDial->setValue((double) rawVal);
}

void FlangerFrame::onDepth(double value)
{
  ui->depthDial->setValue(value);
}

void FlangerFrame::onManual(double value)
{
  if(mFXType == FlangerOneway)
    ui->manualDial->setValue(value);
  else
    ui->manualDial->setValue(value - 5.0);
}

void FlangerFrame::onFeedback(double value)
{
  ui->feedbackDial->setValue(value);
}

void FlangerFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
}

void FlangerFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
}

void FlangerFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
}

