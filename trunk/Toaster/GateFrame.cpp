#include "GateFrame.h"
#include "ui_GateFrame.h"
#include "Stomp.h"

GateFrame::GateFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::GateFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

GateFrame::~GateFrame()
{
  delete ui;
}

void GateFrame::activate(Stomp& stomp)
{
  mpStomp = &stomp;

  connect(mpStomp, SIGNAL(compressorGateIntensityReceived(double)), this, SLOT(onThreshold(double)));

  mpStomp->requestCompressorGateIntensity();

  ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(stomp.getInstance()));
}

void GateFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(compressorGateIntensityReceived(double)), this, SLOT(onThreshold(double)));
  }
  mpStomp = nullptr;
}

void GateFrame::setFXType(FXType fxType)
{
  mFXType = fxType;
  ui->lcdDisplay->setStompName(LookUpTables::stompFXName(fxType));
}

void GateFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void GateFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void GateFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void GateFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void GateFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}
void GateFrame::on_thresholdDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyCompressorGateIntensity(value);
}

void GateFrame::onThreshold(double value)
{
  ui->thresholdDial->setValue(value);
  update();
}

