#include "CabFrame.h"
#include "ui_CabFrame.h"

CabFrame::CabFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::CabFrame)
  , mpCab(nullptr)
{
  ui->setupUi(this);
}

CabFrame::~CabFrame()
{
  delete ui;
}

void CabFrame::activate(QObject& amp)
{
  mpCab = qobject_cast<Cab*>(&amp);

  if(mpCab != nullptr)
  {
    connect(mpCab, &Cab::highShiftReceived, this, &CabFrame::onHighShift);
    connect(mpCab, &Cab::lowShiftReceived, this, &CabFrame::onLowShift);
    connect(mpCab, &Cab::characterReceived, this, &CabFrame::onCharacter);
    connect(mpCab, &Cab::volumeReceived, this, &CabFrame::onVolume);

    mpCab->requestHighShift();
    mpCab->requestLowShift();
    mpCab->requestCharacter();
    mpCab->requestVolume();
  }
}

void CabFrame::deactivate()
{
  if(mpCab != nullptr)
  {
    disconnect(mpCab, &Cab::highShiftReceived, this, &CabFrame::onHighShift);
    disconnect(mpCab, &Cab::lowShiftReceived, this, &CabFrame::onLowShift);
    disconnect(mpCab, &Cab::characterReceived, this, &CabFrame::onCharacter);
    disconnect(mpCab, &Cab::volumeReceived, this, &CabFrame::onVolume);
    mpCab = nullptr;
  }
}

void CabFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void CabFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void CabFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void CabFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void CabFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void CabFrame::on_highShiftDial_valueChanged(double value)
{
  if(mpCab != nullptr)
    mpCab->applyHighShift(value);
}

void CabFrame::on_lowShiftDial_valueChanged(double value)
{
  if(mpCab != nullptr)
    mpCab->applyLowShift(value);
}

void CabFrame::on_characterDial_valueChanged(double value)
{
  if(mpCab != nullptr)
    mpCab->applyCharacter(value);
}

void CabFrame::on_volumeDial_valueChanged(double value)
{
  if(mpCab != nullptr)
    mpCab->applyVolume(value);
}

void CabFrame::onHighShift(double value)
{
  ui->highShiftDial->setValue(value);
}

void CabFrame::onLowShift(double value)
{
  ui->lowShiftDial->setValue(value);
}

void CabFrame::onCharacter(double value)
{
  ui->characterDial->setValue(value);
}

void CabFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
}


