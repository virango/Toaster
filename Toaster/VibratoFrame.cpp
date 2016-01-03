#include "VibratoFrame.h"
#include "ui_VibratoFrame.h"
#include "Stomp.h"

VibratoFrame::VibratoFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::VibratoFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  ui->crossoverDial->setLookUpTable(LookUpTables::getFrequencyValues());
}

VibratoFrame::~VibratoFrame()
{
  delete ui;
}

void VibratoFrame::activate(QObject& stomp)
{
  mpStomp = dynamic_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(modulationRateReceived(double)), this, SLOT(onRate(double)));
    connect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDepth(double)));
    connect(mpStomp, SIGNAL(modulationCrossoverReceived(int)), this, SLOT(onCrossover(int)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));

    mpStomp->requestModulationRate();
    mpStomp->requestModulationDepth();
    mpStomp->requestModulationCrossover();
    mpStomp->requestVolume();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void VibratoFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(modulationRateReceived(double)), this, SLOT(onRate(double)));
    disconnect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDepth(double)));
    disconnect(mpStomp, SIGNAL(modulationCrossoverReceived(int)), this, SLOT(onCrossover(int)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  }
  mpStomp = nullptr;
}

void VibratoFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void VibratoFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void VibratoFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void VibratoFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void VibratoFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void VibratoFrame::on_rateDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationRate(value);
}

void VibratoFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void VibratoFrame::on_crossoverDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationCrossover(value);
}

void VibratoFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void VibratoFrame::onRate(double value)
{
  ui->rateDial->setValue(value);
  update();
}

void VibratoFrame::onDepth(double value)
{
  ui->depthDial->setValue(value);
  update();
}

void VibratoFrame::onCrossover(int value)
{
  ui->crossoverDial->setValue(value);
  update();
}

void VibratoFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

