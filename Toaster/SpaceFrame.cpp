#include "SpaceFrame.h"
#include "ui_SpaceFrame.h"
#include "Stomp.h"

SpaceFrame::SpaceFrame(QWidget *parent)
  : QWidget(parent)
,   ui(new Ui::SpaceFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

SpaceFrame::~SpaceFrame()
{
  delete ui;
}

void SpaceFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(intensityReceived(double)), this, SLOT(onIntensity(double)));

    mpStomp->requestIntensity();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void SpaceFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(intensityReceived(double)), this, SLOT(onIntensity(double)));
  }
  mpStomp = nullptr;
}

void SpaceFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void SpaceFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void SpaceFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void SpaceFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void SpaceFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void SpaceFrame::on_intensityDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyIntensity(value*10.0);
}

void SpaceFrame::onIntensity(double value)
{
  ui->intensityDial->setValue(value/10.0);
  update();
}


