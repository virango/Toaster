#include "AirChorusFrame.h"
#include "ui_AirChorusFrame.h"
#include "Stomp.h"

AirChorusFrame::AirChorusFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::AirChorusFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  ui->crossoverDial->setLookUpTable(LookUpTables::getFrequencyValues());
}

AirChorusFrame::~AirChorusFrame()
{
  delete ui;
}

void AirChorusFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDepth(double)));
    connect(mpStomp, SIGNAL(modulationCrossoverReceived(int)), this, SLOT(onCrossover(int)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));

    mpStomp->requestModulationDepth();
    mpStomp->requestModulationCrossover();
    mpStomp->requestVolume();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }

}

void AirChorusFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDepth(double)));
    disconnect(mpStomp, SIGNAL(modulationCrossoverReceived(double)), this, SLOT(onCrossover(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  }
  mpStomp = nullptr;
}

void AirChorusFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void AirChorusFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void AirChorusFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void AirChorusFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void AirChorusFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void AirChorusFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void AirChorusFrame::on_crossoverDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationCrossover(value);
}

void AirChorusFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void AirChorusFrame::onDepth(double value)
{
  ui->depthDial->setValue(value);
  update();
}

void AirChorusFrame::onCrossover(int value)
{
  ui->crossoverDial->setValue(value);
  update();
}

void AirChorusFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}
