/*  This file is part of Toaster, the editor and remote control for Kemper profiling amplifier.
*
*   Copyright (C) 2016  Thomas Langer
*
*   Toaster is free software: you can redistribute it and/or modify it under the terms of the
*   GNU General Public License as published by the Free Software Foundation, either version 3
*   of the License, or (at your option) any later version.
*
*   Toaster is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
*   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*   See the GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along with Toaster.
*   If not, see <http://www.gnu.org/licenses/>.
*/
#include "ChromaticPitchFrame.h"
#include "ui_ChromaticPitchFrame.h"
#include "Stomp.h"

ChromaticPitchFrame::ChromaticPitchFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::ChromaticPitchFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  setCurrentDisplayPage(QToasterLCD::Page1);
}

ChromaticPitchFrame::~ChromaticPitchFrame()
{
  delete ui;
}

void ChromaticPitchFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(voice1PitchReceived(double)), this, SLOT(onVoice1Pitch(double)));
    connect(mpStomp, SIGNAL(voice2PitchReceived(double)), this, SLOT(onVoice2Pitch(double)));
    connect(mpStomp, SIGNAL(formantShiftReceived(double)), this, SLOT(onFormantShift(double)));
    connect(mpStomp, SIGNAL(detuneReceived(double)), this, SLOT(onDetune(double)));
    connect(mpStomp, SIGNAL(voiceMixReceived(double)), this, SLOT(onVoiceMix(double)));
    connect(mpStomp, SIGNAL(intensityReceived(double)), this, SLOT(onMix(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(smoothChordsReceived(bool)), this, SLOT(onSmoothChords(bool)));
    connect(mpStomp, SIGNAL(pureTuningReceived(bool)), this, SLOT(onPureTuning(bool)));
    connect(mpStomp, SIGNAL(formantShiftOnOffReceived(bool)), this, SLOT(onFormantShiftOnOff(bool)));

    mpStomp->requestVoice1Pitch();
    mpStomp->requestVoice2Pitch();
    mpStomp->requestFormantShift();
    mpStomp->requestDetune();
    mpStomp->requestVoiceMix();
    mpStomp->requestIntensity();
    mpStomp->requestDucking();
    mpStomp->requestVolume();
    mpStomp->requestSmoothChords();
    mpStomp->requestPureTuning();
    mpStomp->requestFormantShiftOnOff();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void ChromaticPitchFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(voice1PitchReceived(double)), this, SLOT(onVoice1Pitch(double)));
    disconnect(mpStomp, SIGNAL(voice2PitchReceived(double)), this, SLOT(onVoice2Pitch(double)));
    disconnect(mpStomp, SIGNAL(formantShiftReceived(double)), this, SLOT(onFormantShift(double)));
    disconnect(mpStomp, SIGNAL(detuneReceived(double)), this, SLOT(onDetune(double)));
    disconnect(mpStomp, SIGNAL(voiceMixReceived(double)), this, SLOT(onVoiceMix(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(smoothChordsReceived(bool)), this, SLOT(onSmoothChords(bool)));
    disconnect(mpStomp, SIGNAL(pureTuningReceived(bool)), this, SLOT(onPureTuning(bool)));
    disconnect(mpStomp, SIGNAL(formantShiftOnOffReceived(bool)), this, SLOT(onFormantShiftOnOff(bool)));
  }


  mpStomp = nullptr;
}

QToasterLCD::Page ChromaticPitchFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page ChromaticPitchFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void ChromaticPitchFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
    ui->bigDials->setCurrentIndex((int) page);
    ui->smallDials->setCurrentIndex((int) page);
  }
}

void ChromaticPitchFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void ChromaticPitchFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void ChromaticPitchFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void ChromaticPitchFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void ChromaticPitchFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void ChromaticPitchFrame::on_voice1PitchDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVoice1Pitch(value);
}

void ChromaticPitchFrame::on_voice2PitchDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVoice2Pitch(value);
}

void ChromaticPitchFrame::on_formantShiftDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyFormantShift(value);
}

void ChromaticPitchFrame::on_detuneDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDetune(value);
}

void ChromaticPitchFrame::on_voiceMixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVoiceMix(value);
}

void ChromaticPitchFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyIntensity(value);
}

void ChromaticPitchFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void ChromaticPitchFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void ChromaticPitchFrame::on_smoothChordsDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applySmoothChords(valueIndex != 0);
}

void ChromaticPitchFrame::on_pureTuningDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applyPureTuning(valueIndex != 0);
}

void ChromaticPitchFrame::on_formantShiftOnOffDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applyFormantShiftOnOff(valueIndex != 0);
}

void ChromaticPitchFrame::onVoice1Pitch(double value)
{
  ui->voice1PitchDial->setValue(value);
  update();
}

void ChromaticPitchFrame::onVoice2Pitch(double value)
{
  ui->voice2PitchDial->setValue(value);
  update();
}

void ChromaticPitchFrame::onFormantShift(double value)
{
  ui->formantShiftDial->setValue(value);
  update();
}

void ChromaticPitchFrame::onDetune(double value)
{
  ui->detuneDial->setValue(value);
  update();
}

void ChromaticPitchFrame::onVoiceMix(double value)
{
  ui->voiceMixDial->setValue(value);
  update();
}

void ChromaticPitchFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void ChromaticPitchFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void ChromaticPitchFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void ChromaticPitchFrame::onSmoothChords(bool onOff)
{
  ui->smoothChordsDial->setValue(onOff ? 1 : 0);
  update();
}

void ChromaticPitchFrame::onPureTuning(bool onOff)
{
  ui->pureTuningDial->setValue(onOff ? 1 : 0);
  update();
}

void ChromaticPitchFrame::onFormantShiftOnOff(bool onOff)
{
  ui->formantShiftOnOffDial->setValue(onOff ? 1 : 0);
  update();
}
