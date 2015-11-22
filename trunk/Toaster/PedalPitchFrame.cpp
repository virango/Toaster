#include "PedalPitchFrame.h"
#include "ui_PedalPitchFrame.h"
#include "Stomp.h"

PedalPitchFrame::PedalPitchFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::PedalPitchFrame)
  , mpStomp(nullptr)
  , mGlobal()
  , mFXType(None)
{
  ui->setupUi(this);
  ui->pageDial->setValue(0);
  ui->smoothChordsDial->setValue(0);
  ui->pureTuningDial->setValue(0);
  ui->formantShiftOnOffDial->setValue(0);
  ui->wahPedalToPitchDial->setValue(0);
}

PedalPitchFrame::~PedalPitchFrame()
{
  delete ui;
}

void PedalPitchFrame::activate(Stomp& stomp)
{
  mpStomp = &stomp;

  connect(mpStomp, SIGNAL(voice2PitchReceived(double)), this, SLOT(onHeelPitch(double)));
  connect(mpStomp, SIGNAL(voice1PitchReceived(double)), this, SLOT(onToePitch(double)));
  connect(mpStomp, SIGNAL(formantShiftReceived(double)), this, SLOT(onFormantShift(double)));
  connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
  connect(mpStomp, SIGNAL(smoothChordsReceived(bool)), this, SLOT(onSmoothChords(bool)));
  connect(mpStomp, SIGNAL(pureTuningReceived(bool)), this, SLOT(onPureTuning(bool)));
  connect(mpStomp, SIGNAL(formantShiftOnOffReceived(bool)), this, SLOT(onFormantShiftOnOff(bool)));
  connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
  connect(&mGlobal, SIGNAL(wahPedalToPitchReceived(bool)), this, SLOT(onWahPedalToPitch(bool)));

  mpStomp->requestVoice2Pitch();
  mpStomp->requestVoice1Pitch();
  mpStomp->requestFormantShift();
  mpStomp->requestMix();
  mpStomp->requestSmoothChords();
  mpStomp->requestPureTuning();
  mpStomp->requestFormantShiftOnOff();
  mpStomp->requestVolume();
  mpStomp->requestDucking();
  mGlobal.requestWahPedalToPitch();

  ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(stomp.getInstance()));
}

void PedalPitchFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(voice2PitchReceived(double)), this, SLOT(onHeelPitch(double)));
    disconnect(mpStomp, SIGNAL(voice1PitchReceived(double)), this, SLOT(onToePitch(double)));
    disconnect(mpStomp, SIGNAL(formantShiftReceived(double)), this, SLOT(onFormantShift(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(smoothChordsReceived(bool)), this, SLOT(onSmoothChords(bool)));
    disconnect(mpStomp, SIGNAL(pureTuningReceived(bool)), this, SLOT(onPureTuning(bool)));
    disconnect(mpStomp, SIGNAL(formantShiftOnOffReceived(bool)), this, SLOT(onFormantShiftOnOff(bool)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
  }

  disconnect(&mGlobal, SIGNAL(wahPedalToPitchReceived(bool)), this, SLOT(onWahPedalToPitch(bool)));

  mpStomp = nullptr;
}

void PedalPitchFrame::setFXType(FXType fxType)
{
  mFXType = fxType;
  ui->lcdDisplay->setStompName(LookUpTables::stompFXName(fxType));
}

void PedalPitchFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void PedalPitchFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void PedalPitchFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void PedalPitchFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void PedalPitchFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void PedalPitchFrame::on_pageDial_valueChanged(int valueIndex)
{
  ui->lcdDisplay->setCurrentPage((QToasterStompEditLCD::Page)valueIndex);
}

void PedalPitchFrame::on_heelPitchDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVoice2Pitch(value);
}

void PedalPitchFrame::on_toePitchDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVoice1Pitch(value);
}

void PedalPitchFrame::on_formantShiftDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyFormantShift(value);
}

void PedalPitchFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void PedalPitchFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void PedalPitchFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void PedalPitchFrame::on_wahPedalToPitchDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mGlobal.applyWahPedalToPitchReceived(valueIndex != 0);
}

void PedalPitchFrame::on_smoothChordsDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applySmoothChords(valueIndex != 0);
}

void PedalPitchFrame::on_pureTuningDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applyPureTuning(valueIndex != 0);
}

void PedalPitchFrame::on_formantShiftOnOffDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applyFormantShiftOnOff(valueIndex != 0);
}

void PedalPitchFrame::onHeelPitch(double value)
{
  ui->heelPitchDial->setValue(value);
  update();
}

void PedalPitchFrame::onToePitch(double value)
{
  ui->toePitchDial->setValue(value);
  update();
}

void PedalPitchFrame::onFormantShift(double value)
{
  ui->formantShiftDial->setValue(value);
  update();
}

void PedalPitchFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void PedalPitchFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void PedalPitchFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void PedalPitchFrame::onWahPedalToPitch(bool onOff)
{
  ui->wahPedalToPitchDial->setValue(onOff ? 1 : 0);
  update();
}

void PedalPitchFrame::onSmoothChords(bool onOff)
{
  ui->smoothChordsDial->setValue(onOff ? 1 : 0);
  update();
}

void PedalPitchFrame::onPureTuning(bool onOff)
{
  ui->pureTuningDial->setValue(onOff ? 1 : 0);
  update();
}

void PedalPitchFrame::onFormantShiftOnOff(bool onOff)
{
  ui->formantShiftOnOffDial->setValue(onOff ? 1 : 0);
  update();
}

