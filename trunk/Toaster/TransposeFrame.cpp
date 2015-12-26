#include "TransposeFrame.h"
#include "ui_TransposeFrame.h"
#include "Stomp.h"

TransposeFrame::TransposeFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::TransposeFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

TransposeFrame::~TransposeFrame()
{
  delete ui;
}

void TransposeFrame::activate(QObject& stomp)
{
  mpStomp = dynamic_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(voice2PitchReceived(double)), this, SLOT(onPitch(double)));
    connect(mpStomp, SIGNAL(smoothChordsReceived(bool)), this, SLOT(onSmoothChords(bool)));

    mpStomp->requestVoice2Pitch();
    mpStomp->requestSmoothChords();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void TransposeFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(voice2PitchReceived(double)), this, SLOT(onPitch(double)));
    disconnect(mpStomp, SIGNAL(smoothChordsReceived(unsigned short)), this, SLOT(onSmoothChords(unsigned short)));
  }
  mpStomp = nullptr;
}

void TransposeFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void TransposeFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void TransposeFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void TransposeFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void TransposeFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void TransposeFrame::on_pitchDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVoice2Pitch(value);
}

void TransposeFrame::on_smoothChordsDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applySmoothChords(valueIndex == 1);
}

void TransposeFrame::onPitch(double value)
{
  ui->pitchDial->setValue(value);
  update();
}

void TransposeFrame::onSmoothChords(bool onOff)
{
  ui->smoothChordsDial->setValue(onOff ? 1 : 0);
  update();
}
