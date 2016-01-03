#include "HarmonicPitchFrame.h"
#include "ui_HarmonicPitchFrame.h"

HarmonicPitchFrame::HarmonicPitchFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::HarmonicPitchFrame)
  , mpStomp(nullptr)
{
  ui->setupUi(this);
  ui->pageDial->setValue(0);
  ui->voice1IntervalDial->setLookUpTable(LookUpTables::getVoiceIntervalValues());
  ui->voice2IntervalDial->setLookUpTable(LookUpTables::getVoiceIntervalValues());
}

HarmonicPitchFrame::~HarmonicPitchFrame()
{
  delete ui;
}


void HarmonicPitchFrame::activate(QObject& stomp)
{
  mpStomp = dynamic_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(voice1IntervalReceived(int)), this, SLOT(onVoice1Interval(int)));
    connect(mpStomp, SIGNAL(voice2IntervalReceived(int)), this, SLOT(onVoice2Interval(int)));
    connect(mpStomp, SIGNAL(formantShiftReceived(double)), this, SLOT(onFormantShift(double)));
    connect(mpStomp, SIGNAL(keyReceived(int)), this, SLOT(onKey(int)));
    connect(mpStomp, SIGNAL(voiceMixReceived(double)), this, SLOT(onVoiceMix(double)));
    connect(mpStomp, SIGNAL(intensityReceived(double)), this, SLOT(onMix(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(pureTuningReceived(bool)), this, SLOT(onPureTuning(bool)));
    connect(mpStomp, SIGNAL(formantShiftOnOffReceived(bool)), this, SLOT(onFormantShiftOnOff(bool)));

    mpStomp->requestVoice1Interval();
    mpStomp->requestVoice2Interval();
    mpStomp->requestFormantShift();
    mpStomp->requestKey();
    mpStomp->requestVoiceMix();
    mpStomp->requestIntensity();
    mpStomp->requestDucking();
    mpStomp->requestVolume();
    mpStomp->requestPureTuning();
    mpStomp->requestFormantShiftOnOff();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void HarmonicPitchFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(voice1IntervalReceived(int)), this, SLOT(onVoice1Interval(int)));
    disconnect(mpStomp, SIGNAL(voice2IntervalReceived(int)), this, SLOT(onVoice1Interval(int)));
    disconnect(mpStomp, SIGNAL(formantShiftReceived(double)), this, SLOT(onFormantShift(double)));
    disconnect(mpStomp, SIGNAL(keyReceived(int)), this, SLOT(onKey(int)));
    disconnect(mpStomp, SIGNAL(voiceMixReceived(double)), this, SLOT(onVoiceMix(double)));
    disconnect(mpStomp, SIGNAL(intensityReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(pureTuningReceived(bool)), this, SLOT(onPureTuning(bool)));
    disconnect(mpStomp, SIGNAL(formantShiftOnOffReceived(bool)), this, SLOT(onFormantShiftOnOff(bool)));
  }

  mpStomp = nullptr;
}

void HarmonicPitchFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void HarmonicPitchFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void HarmonicPitchFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void HarmonicPitchFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void HarmonicPitchFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void HarmonicPitchFrame::on_pageDial_valueChanged(int valueIndex)
{
  ui->lcdDisplay->setCurrentPage((QToasterStompEditLCD::Page)valueIndex);
}

void HarmonicPitchFrame::on_voice1IntervalDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVoice1Interval(value);
}

void HarmonicPitchFrame::on_voice2IntervalDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVoice2Interval(value);
}

void HarmonicPitchFrame::on_formantShiftDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyFormantShift(value);
}

void HarmonicPitchFrame::on_keyDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applyKey(valueIndex);
}

void HarmonicPitchFrame::on_voiceMixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVoiceMix(value);
}

void HarmonicPitchFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyIntensity(value);
}

void HarmonicPitchFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void HarmonicPitchFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void HarmonicPitchFrame::on_pureTuningDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applyPureTuning(valueIndex != 0);
}

void HarmonicPitchFrame::on_formantShiftOnOffDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applyFormantShiftOnOff(valueIndex != 0);
}

void HarmonicPitchFrame::onVoice1Interval(int value)
{
  ui->voice1IntervalDial->setValue(value);
  update();
}

void HarmonicPitchFrame::onVoice2Interval(int value)
{
  ui->voice2IntervalDial->setValue(value);
  update();
}

void HarmonicPitchFrame::onFormantShift(double value)
{
  ui->formantShiftDial->setValue(value);
  update();
}

void HarmonicPitchFrame::onKey(int value)
{
  ui->keyDial->setValue(value);
  update();
}

void HarmonicPitchFrame::onVoiceMix(double value)
{
  ui->voiceMixDial->setValue(value);
  update();
}

void HarmonicPitchFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void HarmonicPitchFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void HarmonicPitchFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void HarmonicPitchFrame::onPureTuning(bool onOff)
{
  ui->pureTuningDial->setValue(onOff ? 1 : 0);
  update();
}

void HarmonicPitchFrame::onFormantShiftOnOff(bool onOff)
{
  ui->formantShiftOnOffDial->setValue(onOff ? 1 : 0);
  update();
}
