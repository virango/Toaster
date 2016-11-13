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
#include "HarmonicPitchFrame.h"
#include "ui_HarmonicPitchFrame.h"
#include "Settings.h"
#include "LookUpTables.h"

HarmonicPitchFrame::HarmonicPitchFrame(QWidget *parent)
  : QWidget(parent)
  , ui(nullptr)
  , mpStomp(nullptr)
{
}

HarmonicPitchFrame::~HarmonicPitchFrame()
{
  if(ui != nullptr)
    delete ui;
}


void HarmonicPitchFrame::activate(QObject& stomp)
{
  ui = new Ui::HarmonicPitchFrame();
  ui->setupUi(this);
  ui->voice1IntervalDial->setLookUpTable(LookUpTables::getVoiceIntervalValues());
  ui->voice2IntervalDial->setLookUpTable(LookUpTables::getVoiceIntervalValues());
  setCurrentDisplayPage(mCurrentPage);

  if(Settings::get().getKPAOSVersion() >= 0x04000000)
  {
    ui->lcdDisplay->setValue9Title("Voice Balance");
  }

  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::voice1IntervalReceived, this, &HarmonicPitchFrame::onVoice1Interval);
    connect(mpStomp, &Stomp::voice2IntervalReceived, this, &HarmonicPitchFrame::onVoice2Interval);
    connect(mpStomp, &Stomp::formantShiftReceived, this, &HarmonicPitchFrame::onFormantShift);
    connect(mpStomp, &Stomp::keyReceived, this, &HarmonicPitchFrame::onKey);
    connect(mpStomp, &Stomp::voiceMixReceived, this, &HarmonicPitchFrame::onVoiceMix);
    connect(mpStomp, &Stomp::intensityReceived, this, &HarmonicPitchFrame::onMix);
    connect(mpStomp, &Stomp::duckingReceived, this, &HarmonicPitchFrame::onDucking);
    connect(mpStomp, &Stomp::volumeReceived, this, &HarmonicPitchFrame::onVolume);
    connect(mpStomp, &Stomp::pureTuningReceived, this, &HarmonicPitchFrame::onPureTuning);
    connect(mpStomp, &Stomp::formantShiftOnOffReceived, this, &HarmonicPitchFrame::onFormantShiftOnOff);
    connect(mpStomp, &Stomp::stereoReceived, this, &HarmonicPitchFrame::onStereo);

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));

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

void HarmonicPitchFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::voice1IntervalReceived, this, &HarmonicPitchFrame::onVoice1Interval);
    disconnect(mpStomp, &Stomp::voice2IntervalReceived, this, &HarmonicPitchFrame::onVoice2Interval);
    disconnect(mpStomp, &Stomp::formantShiftReceived, this, &HarmonicPitchFrame::onFormantShift);
    disconnect(mpStomp, &Stomp::keyReceived, this, &HarmonicPitchFrame::onKey);
    disconnect(mpStomp, &Stomp::voiceMixReceived, this, &HarmonicPitchFrame::onVoiceMix);
    disconnect(mpStomp, &Stomp::intensityReceived, this, &HarmonicPitchFrame::onMix);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &HarmonicPitchFrame::onDucking);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &HarmonicPitchFrame::onVolume);
    disconnect(mpStomp, &Stomp::pureTuningReceived, this, &HarmonicPitchFrame::onPureTuning);
    disconnect(mpStomp, &Stomp::formantShiftOnOffReceived, this, &HarmonicPitchFrame::onFormantShiftOnOff);
    disconnect(mpStomp, &Stomp::stereoReceived, this, &HarmonicPitchFrame::onStereo);
  }

  mpStomp = nullptr;

  if(ui != nullptr)
  {
    mCurrentPage = ui->lcdDisplay->currentPage();
    delete ui;
    ui = nullptr;
  }
}

QToasterLCD::Page HarmonicPitchFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page HarmonicPitchFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void HarmonicPitchFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
    ui->bigDials->setCurrentIndex((int) page);
    ui->smallDials->setCurrentIndex((int) page);
  }
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

void HarmonicPitchFrame::on_stereoDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyStereo(value);
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

void HarmonicPitchFrame::onStereo(double value)
{
  ui->stereoDial->setValue(value);
  update();
}
