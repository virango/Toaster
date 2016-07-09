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
#include "LegacyDelayFrame.h"
#include "ui_LegacyDelayFrame.h"
#include "LookUpTables.h"
#include "Stomp.h"

LegacyDelayFrame::LegacyDelayFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::LegacyDelayFrame)
  , mpStomp(nullptr)
  , mToTempo(false)
{
  ui->setupUi(this);
  ui->mixDial->setLookUpTable(LookUpTables::getMixValuesV4());
}

LegacyDelayFrame::~LegacyDelayFrame()
{
  delete ui;
}

void LegacyDelayFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::delayMixReceived, this, &LegacyDelayFrame::OnMix);
    connect(mpStomp, &Stomp::delay1TimeReceived, this, &LegacyDelayFrame::OnDelay1Time);
    connect(mpStomp, &Stomp::delay2RatioReceived, this, &LegacyDelayFrame::OnDelay2Ratio);
    connect(mpStomp, &Stomp::delayFeedbackReceived, this, &LegacyDelayFrame::OnFeedback);
    connect(mpStomp, &Stomp::delayNoteValue1Received, this, &LegacyDelayFrame::OnNoteValue1);
    connect(mpStomp, &Stomp::delayNoteValue2Received, this, &LegacyDelayFrame::OnNoteValue2);
    connect(mpStomp, &Stomp::delayToTempoReceived, this, &LegacyDelayFrame::OnToTempo);
    connect(mpStomp, &Stomp::distortionShaperDriveReceived, this, &LegacyDelayFrame::OnBandwidth);
    connect(mpStomp, &Stomp::distortionBoosterToneReceived, this, &LegacyDelayFrame::OnFrequency);
    connect(mpStomp, &Stomp::delayModulationReceived, this, &LegacyDelayFrame::OnModulation);
    connect(mpStomp, &Stomp::duckingReceived, this, &LegacyDelayFrame::OnDucking);

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));

    mpStomp->requestDelayToTempo();
    mpStomp->requestDelayMix();
    mpStomp->requestDelay1Time();
    mpStomp->requestDelay2Ratio();
    mpStomp->requestDelayFeedback();
    mpStomp->requestDelayNoteValue1();
    mpStomp->requestDelayNoteValue2();
    mpStomp->requestDistortionShaperDrive();
    mpStomp->requestDistortionBoosterTone();
    mpStomp->requestDelayModulation();
    mpStomp->requestDucking();
  }
}

void LegacyDelayFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::delayMixReceived, this, &LegacyDelayFrame::OnMix);
    disconnect(mpStomp, &Stomp::delay1TimeReceived, this, &LegacyDelayFrame::OnDelay1Time);
    disconnect(mpStomp, &Stomp::delay2RatioReceived, this, &LegacyDelayFrame::OnDelay2Ratio);
    disconnect(mpStomp, &Stomp::delayFeedbackReceived, this, &LegacyDelayFrame::OnFeedback);
    disconnect(mpStomp, &Stomp::delayNoteValue1Received, this, &LegacyDelayFrame::OnNoteValue1);
    disconnect(mpStomp, &Stomp::delayNoteValue2Received, this, &LegacyDelayFrame::OnNoteValue2);
    disconnect(mpStomp, &Stomp::delayToTempoReceived, this, &LegacyDelayFrame::OnToTempo);
    disconnect(mpStomp, &Stomp::distortionShaperDriveReceived, this, &LegacyDelayFrame::OnBandwidth);
    disconnect(mpStomp, &Stomp::distortionBoosterToneReceived, this, &LegacyDelayFrame::OnFrequency);
    disconnect(mpStomp, &Stomp::delayModulationReceived, this, &LegacyDelayFrame::OnModulation);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &LegacyDelayFrame::OnDucking);
  }
  mpStomp = nullptr;
}

QToasterLCD::Page LegacyDelayFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page LegacyDelayFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void LegacyDelayFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
    ui->bigDials->setCurrentIndex((int) page);
    ui->smallDials->setCurrentIndex((int) page);
  }
}

void LegacyDelayFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void LegacyDelayFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void LegacyDelayFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void LegacyDelayFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}
void LegacyDelayFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void LegacyDelayFrame::on_mixDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDelayMix(value);
}

void LegacyDelayFrame::on_delay1TimeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDelay1Time(value);
}

void LegacyDelayFrame::on_delay2RatioDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDelay2Ratio(value);
}

void LegacyDelayFrame::on_feedbackDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDelayFeedback(value);
}

void LegacyDelayFrame::on_noteValue1Dial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applyDelayNoteValue1(valueIndex);
}

void LegacyDelayFrame::on_noteValue2Dial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applyDelayNoteValue2(valueIndex);
}

void LegacyDelayFrame::on_toTempoDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
  {
    mpStomp->applyDelayToTempo(valueIndex);
    mToTempo = valueIndex != 0;
    UpdateLCD();
  }
}

void LegacyDelayFrame::on_bandwidthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionShaperDrive(value);
}

void LegacyDelayFrame::on_frequencyDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionBoosterTone(value);
}

void LegacyDelayFrame::on_modulationDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDelayModulation(value);
}

void LegacyDelayFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void LegacyDelayFrame::OnMix(int value)
{
  ui->mixDial->setValue(value);
  update();
}

void LegacyDelayFrame::OnDelay1Time(double value)
{
  ui->delay1TimeDial->setValue(value);
  update();
}

void LegacyDelayFrame::OnDelay2Ratio(double value)
{
  ui->delay2RatioDial->setValue(value);
  update();
}

void LegacyDelayFrame::OnFeedback(double value)
{
  ui->feedbackDial->setValue(value);
  update();
}

void LegacyDelayFrame::OnNoteValue1(int valueIndex)
{
  ui->noteValue1Dial->setValue(valueIndex);
  update();
}

void LegacyDelayFrame::OnNoteValue2(int valueIndex)
{
  ui->noteValue2Dial->setValue(valueIndex);
  update();
}

void LegacyDelayFrame::OnToTempo(int valueIndex)
{
  ui->toTempoDial->setValue(valueIndex);
  mToTempo = valueIndex != 0;
  UpdateLCD();
  update();
}

void LegacyDelayFrame::OnBandwidth(double value)
{
  ui->bandwidthDial->setValue(value);
  update();
}

void LegacyDelayFrame::OnFrequency(double value)
{
  ui->frequencyDial->setValue(value);
  update();
}

void LegacyDelayFrame::OnModulation(double value)
{
  ui->modulationDial->setValue(value);
  update();
}

void LegacyDelayFrame::OnDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void LegacyDelayFrame::UpdateLCD()
{
  if(mToTempo)
  {
    ui->lcdDisplay->setValue2Title("Note Value 1");
    ui->lcdDisplay->setValue3Title("Note Value 2");
    ui->lcdDisplay->setValue2(ui->noteValue1Dial->valueText());
    ui->lcdDisplay->setValue3(ui->noteValue1Dial->valueText());
  }
  else
  {
    ui->lcdDisplay->setValue2Title("Delay 1 Time");
    ui->lcdDisplay->setValue3Title("Delay 2 Ratio");
    ui->lcdDisplay->setValue2(ui->delay1TimeDial->valueText());
    ui->lcdDisplay->setValue3(ui->delay2RatioDial->valueText());
  }
}
