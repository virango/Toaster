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
#include "Settings.h"
#include "LookUpTables.h"

ChromaticPitchFrame::ChromaticPitchFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::ChromaticPitchFrame)
  , mpStomp(nullptr)
{
  ui->setupUi(this);
  setCurrentDisplayPage(QToasterLCD::Page1);

  if(Settings::get().getKPAOSVersion() >= 0x04000000)
  {
    ui->lcdDisplay->setValue9Title("Voice Balance");
  }
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
    connect(mpStomp, &Stomp::voice1PitchReceived, this, &ChromaticPitchFrame::onVoice1Pitch);
    connect(mpStomp, &Stomp::voice2PitchReceived, this, &ChromaticPitchFrame::onVoice2Pitch);
    connect(mpStomp, &Stomp::formantShiftReceived, this, &ChromaticPitchFrame::onFormantShift);
    connect(mpStomp, &Stomp::detuneReceived, this, &ChromaticPitchFrame::onDetune);
    connect(mpStomp, &Stomp::voiceMixReceived, this, &ChromaticPitchFrame::onVoiceMix);
    connect(mpStomp, &Stomp::intensityReceived, this, &ChromaticPitchFrame::onMix);
    connect(mpStomp, &Stomp::duckingReceived, this, &ChromaticPitchFrame::onDucking);
    connect(mpStomp, &Stomp::volumeReceived, this, &ChromaticPitchFrame::onVolume);
    connect(mpStomp, &Stomp::smoothChordsReceived, this, &ChromaticPitchFrame::onSmoothChords);
    connect(mpStomp, &Stomp::pureTuningReceived, this, &ChromaticPitchFrame::onPureTuning);
    connect(mpStomp, &Stomp::formantShiftOnOffReceived, this, &ChromaticPitchFrame::onFormantShiftOnOff);
    connect(mpStomp, &Stomp::stereoReceived, this, &ChromaticPitchFrame::onStereo);

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));

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

    StompInstance si = mpStomp->getInstance();
    if(si != StompX && si != StompMod && si != StompDelay)
    {
      ui->lcdDisplay->setValue16("");
      ui->lcdDisplay->setValue16Title("");
      ui->stereoDial->setIsActive(false);
    }
    else
    {
      ui->lcdDisplay->setValue16Title("Stereo");
      ui->stereoDial->setIsActive(true);
      mpStomp->requestStereo();
    }
  }
}

void ChromaticPitchFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::voice1PitchReceived, this, &ChromaticPitchFrame::onVoice1Pitch);
    disconnect(mpStomp, &Stomp::voice2PitchReceived, this, &ChromaticPitchFrame::onVoice2Pitch);
    disconnect(mpStomp, &Stomp::formantShiftReceived, this, &ChromaticPitchFrame::onFormantShift);
    disconnect(mpStomp, &Stomp::detuneReceived, this, &ChromaticPitchFrame::onDetune);
    disconnect(mpStomp, &Stomp::voiceMixReceived, this, &ChromaticPitchFrame::onVoiceMix);
    disconnect(mpStomp, &Stomp::intensityReceived, this, &ChromaticPitchFrame::onMix);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &ChromaticPitchFrame::onDucking);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &ChromaticPitchFrame::onVolume);
    disconnect(mpStomp, &Stomp::smoothChordsReceived, this, &ChromaticPitchFrame::onSmoothChords);
    disconnect(mpStomp, &Stomp::pureTuningReceived, this, &ChromaticPitchFrame::onPureTuning);
    disconnect(mpStomp, &Stomp::formantShiftOnOffReceived, this, &ChromaticPitchFrame::onFormantShiftOnOff);
    disconnect(mpStomp, &Stomp::stereoReceived, this, &ChromaticPitchFrame::onStereo);

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

void ChromaticPitchFrame::on_stereoDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyStereo(value);
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

void ChromaticPitchFrame::onStereo(double value)
{
  ui->stereoDial->setValue(value);
  update();
}
