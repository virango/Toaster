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
#include "PedalPitchFrame.h"
#include "ui_PedalPitchFrame.h"
#include "Stomp.h"
#include "Global.h"
#include "LookUpTables.h"

PedalPitchFrame::PedalPitchFrame(QWidget *parent)
  : QWidget(parent)
  , ui(nullptr)
  , mpStomp(nullptr)

{
}

PedalPitchFrame::~PedalPitchFrame()
{
  if(ui != nullptr)
    delete ui;
}

void PedalPitchFrame::activate(QObject& stomp)
{
  ui = new Ui::PedalPitchFrame();
  ui->setupUi(this);
  ui->smoothChordsDial->setValue(0);
  ui->pureTuningDial->setValue(0);
  ui->formantShiftOnOffDial->setValue(0);
  ui->wahPedalToPitchDial->setValue(0);
  setCurrentDisplayPage(mCurrentPage);

  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::voice2PitchReceived, this, &PedalPitchFrame::onHeelPitch);
    connect(mpStomp, &Stomp::voice1PitchReceived, this, &PedalPitchFrame::onToePitch);
    connect(mpStomp, &Stomp::formantShiftReceived, this, &PedalPitchFrame::onFormantShift);
    connect(mpStomp, &Stomp::mixReceived, this, &PedalPitchFrame::onMix);
    connect(mpStomp, &Stomp::smoothChordsReceived, this, &PedalPitchFrame::onSmoothChords);
    connect(mpStomp, &Stomp::pureTuningReceived, this, &PedalPitchFrame::onPureTuning);
    connect(mpStomp, &Stomp::formantShiftOnOffReceived, this, &PedalPitchFrame::onFormantShiftOnOff);
    connect(mpStomp, &Stomp::volumeReceived, this, &PedalPitchFrame::onVolume);
    connect(mpStomp, &Stomp::duckingReceived, this, &PedalPitchFrame::onDucking);
    connect(&globalObj, &Global::wahPedalToPitchReceived, this, &PedalPitchFrame::onWahPedalToPitch);

    mpStomp->requestVoice2Pitch();
    mpStomp->requestVoice1Pitch();
    mpStomp->requestFormantShift();
    mpStomp->requestMix();
    mpStomp->requestSmoothChords();
    mpStomp->requestPureTuning();
    mpStomp->requestFormantShiftOnOff();
    mpStomp->requestVolume();
    mpStomp->requestDucking();
    globalObj.requestWahPedalToPitch();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void PedalPitchFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::voice2PitchReceived, this, &PedalPitchFrame::onHeelPitch);
    disconnect(mpStomp, &Stomp::voice1PitchReceived, this, &PedalPitchFrame::onToePitch);
    disconnect(mpStomp, &Stomp::formantShiftReceived, this, &PedalPitchFrame::onFormantShift);
    disconnect(mpStomp, &Stomp::mixReceived, this, &PedalPitchFrame::onMix);
    disconnect(mpStomp, &Stomp::smoothChordsReceived, this, &PedalPitchFrame::onSmoothChords);
    disconnect(mpStomp, &Stomp::pureTuningReceived, this, &PedalPitchFrame::onPureTuning);
    disconnect(mpStomp, &Stomp::formantShiftOnOffReceived, this, &PedalPitchFrame::onFormantShiftOnOff);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &PedalPitchFrame::onVolume);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &PedalPitchFrame::onDucking);
    mpStomp = nullptr;
  }

  disconnect(&globalObj, &Global::wahPedalToPitchReceived, this, &PedalPitchFrame::onWahPedalToPitch);

  if(ui != nullptr)
  {
    mCurrentPage = ui->lcdDisplay->currentPage();
    delete ui;
    ui = nullptr;
  }
}

QToasterLCD::Page PedalPitchFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page PedalPitchFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void PedalPitchFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
    ui->bigDials->setCurrentIndex((int) page);
  }
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
    globalObj.applyWahPedalToPitch(valueIndex != 0);
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

