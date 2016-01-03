#include "TremoloFrame.h"
#include "ui_TremoloFrame.h"
#include "Stomp.h"

TremoloFrame::TremoloFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::TremoloFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  ui->crossoverDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui->rateDial->setLookUpTable(LookUpTables::getTremoloRateValues());
}

TremoloFrame::~TremoloFrame()
{
  delete ui;
}

void TremoloFrame::activate(QObject& stomp)
{
  mpStomp = dynamic_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(modulationRateReceived(int)), this, SLOT(onRate(int)));
    connect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDepth(double)));
    connect(mpStomp, SIGNAL(modulationCrossoverReceived(int)), this, SLOT(onCrossover(int)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));

    mpStomp->requestModulationRate();
    mpStomp->requestModulationDepth();
    mpStomp->requestModulationCrossover();
    mpStomp->requestVolume();
    mpStomp->requestDucking();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void TremoloFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(modulationRateReceived(int)), this, SLOT(onRate(int)));
    disconnect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDepth(double)));
    disconnect(mpStomp, SIGNAL(modulationCrossoverReceived(int)), this, SLOT(onCrossover(int)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
  }
  mpStomp = nullptr;
}

void TremoloFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void TremoloFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void TremoloFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void TremoloFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void TremoloFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void TremoloFrame::on_rateDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationRate((int)value);
}

void TremoloFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void TremoloFrame::on_crossoverDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationCrossover(value);
}

void TremoloFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void TremoloFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void TremoloFrame::onRate(int value)
{
  ui->rateDial->setValue(value*128);
  update();
}

void TremoloFrame::onDepth(double value)
{
  ui->depthDial->setValue(value);
  update();
}

void TremoloFrame::onCrossover(int value)
{
  ui->crossoverDial->setValue(value);
  update();
}

void TremoloFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void TremoloFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}
