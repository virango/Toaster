#include "MicroPitchFrame.h"
#include "ui_MicroPitchFrame.h"
#include "Stomp.h"

MicroPitchFrame::MicroPitchFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::MicroPitchFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  ui->crossoverDial->setLookUpTable(LookUpTables::getFrequencyValues());
}

MicroPitchFrame::~MicroPitchFrame()
{
  delete ui;
}

void MicroPitchFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDetune(double)));
    connect(mpStomp, SIGNAL(modulationCrossoverReceived(int)), this, SLOT(onCrossover(int)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));

    mpStomp->requestModulationDepth();
    mpStomp->requestModulationCrossover();
    mpStomp->requestVolume();
    mpStomp->requestMix();
    mpStomp->requestDucking();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void MicroPitchFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDetune(double)));
    disconnect(mpStomp, SIGNAL(modulationCrossoverReceived(double)), this, SLOT(onCrossover(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
  }
  mpStomp = nullptr;
}

void MicroPitchFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void MicroPitchFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void MicroPitchFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void MicroPitchFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void MicroPitchFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void MicroPitchFrame::on_detuneDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void MicroPitchFrame::on_crossoverDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationCrossover(value);
}

void MicroPitchFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void MicroPitchFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void MicroPitchFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void MicroPitchFrame::onDetune(double value)
{
  ui->detuneDial->setValue(value);
  update();
}

void MicroPitchFrame::onCrossover(int value)
{
  ui->crossoverDial->setValue(value);
  update();
}

void MicroPitchFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void MicroPitchFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void MicroPitchFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}
