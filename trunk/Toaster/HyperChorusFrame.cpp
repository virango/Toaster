#include "HyperChorusFrame.h"
#include "ui_HyperChorusFrame.h"
#include "Stomp.h"

HyperChorusFrame::HyperChorusFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::HyperChorusFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

HyperChorusFrame::~HyperChorusFrame()
{
  delete ui;
}

void HyperChorusFrame::activate(Stomp& stomp)
{
  mpStomp = &stomp;

  connect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDepth(double)));
  connect(mpStomp, SIGNAL(modulationHyperChorusAmountReceived(double)), this, SLOT(onAmount(double)));
  connect(mpStomp, SIGNAL(modulationCrossoverReceived(double)), this, SLOT(onCrossover(double)));
  connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
  connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));

  mpStomp->requestModulationDepth();
  mpStomp->requestModulationHyperChorusAmount();
  mpStomp->requestModulationCrossover();
  mpStomp->requestMix();
  mpStomp->requestVolume();
  mpStomp->requestDucking();

  ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(stomp.getInstance()));
}

void HyperChorusFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(modulationDepthReceived(double)), this, SLOT(onDepth(double)));
    disconnect(mpStomp, SIGNAL(modulationHyperChorusAmountReceived(double)), this, SLOT(onAmount(double)));
    disconnect(mpStomp, SIGNAL(modulationCrossoverReceived(double)), this, SLOT(onCrossover(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
  }
  mpStomp = nullptr;
}

void HyperChorusFrame::setFXType(FXType fxType)
{
  mFXType = fxType;
  ui->lcdDisplay->setStompName(LookUpTables::stompFXName(fxType));
}

void HyperChorusFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void HyperChorusFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void HyperChorusFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void HyperChorusFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void HyperChorusFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void HyperChorusFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void HyperChorusFrame::on_amountDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationHyperChorusAmount(value);
}

void HyperChorusFrame::on_crossoverDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationCrossover(value);
}

void HyperChorusFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void HyperChorusFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void HyperChorusFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void HyperChorusFrame::onDepth(double value)
{
  ui->depthDial->setValue(value);
  update();
}

void HyperChorusFrame::onAmount(double value)
{
  ui->amountDial->setValue(value);
  update();
}

void HyperChorusFrame::onCrossover(double value)
{
  ui->crossoverDial->setValue(value);
  update();
}

void HyperChorusFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void HyperChorusFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void HyperChorusFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}
