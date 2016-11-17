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
#include "WahPhaserFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

WahPhaserFrame::WahPhaserFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);
}

WahPhaserFrame::~WahPhaserFrame()
{
}

void WahPhaserFrame::activate(QObject& stomp)
{
  show();
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::wahManualReceived, this, &WahPhaserFrame::onManual);
    connect(mpStomp, &Stomp::wahPeakReceived, this, &WahPhaserFrame::onPeak);
    connect(mpStomp, &Stomp::wahRangeReceived, this, &WahPhaserFrame::onPedalRange);
    connect(mpStomp, &Stomp::wahPeakRangeReceived, this, &WahPhaserFrame::onPeakRange);
    connect(mpStomp, &Stomp::wahPedalModeReceived, this, &WahPhaserFrame::onPedalMode);
    connect(mpStomp, &Stomp::mixReceived, this, &WahPhaserFrame::onMix);
    connect(mpStomp, &Stomp::duckingReceived, this, &WahPhaserFrame::onDucking);
    connect(mpStomp, &Stomp::volumeReceived, this, &WahPhaserFrame::onVolume);
    connect(mpStomp, &Stomp::wahTouchAttackReceived, this, &WahPhaserFrame::onTouchAttack);
    connect(mpStomp, &Stomp::wahTouchReleaseReceived, this, &WahPhaserFrame::onTouchRelease);
    connect(mpStomp, &Stomp::wahTouchBoostReceived, this, &WahPhaserFrame::onTouchBoost);
    connect(mpStomp, &Stomp::modulationPhaserPeakSpreadReceived, this, &WahPhaserFrame::onSpread);
    connect(mpStomp, &Stomp::modulationPhaserStagesReceived, this, &WahPhaserFrame::onStages);

    mpStomp->requestWahManual();
    mpStomp->requestWahPeak();
    mpStomp->requestWahRange();
    mpStomp->requestWahPeakRange();
    mpStomp->requestWahPedalMode();
    mpStomp->requestMix();
    mpStomp->requestDucking();
    mpStomp->requestVolume();
    mpStomp->requestWahTouchAttack();
    mpStomp->requestWahTouchRelease();
    mpStomp->requestWahTouchBoost();
    mpStomp->requestModulationPhaserPeakSpread();
    mpStomp->requestModulationPhaserStages();

    ui.lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui.lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void WahPhaserFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::wahManualReceived, this, &WahPhaserFrame::onManual);
    disconnect(mpStomp, &Stomp::wahPeakReceived, this, &WahPhaserFrame::onPeak);
    disconnect(mpStomp, &Stomp::wahRangeReceived, this, &WahPhaserFrame::onPedalRange);
    disconnect(mpStomp, &Stomp::wahPeakRangeReceived, this, &WahPhaserFrame::onPeakRange);
    disconnect(mpStomp, &Stomp::wahPedalModeReceived, this, &WahPhaserFrame::onPedalMode);
    disconnect(mpStomp, &Stomp::mixReceived, this, &WahPhaserFrame::onMix);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &WahPhaserFrame::onDucking);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &WahPhaserFrame::onVolume);
    disconnect(mpStomp, &Stomp::wahTouchAttackReceived, this, &WahPhaserFrame::onTouchAttack);
    disconnect(mpStomp, &Stomp::wahTouchReleaseReceived, this, &WahPhaserFrame::onTouchRelease);
    disconnect(mpStomp, &Stomp::wahTouchBoostReceived, this, &WahPhaserFrame::onTouchBoost);
    disconnect(mpStomp, &Stomp::modulationPhaserPeakSpreadReceived, this, &WahPhaserFrame::onSpread);
    disconnect(mpStomp, &Stomp::modulationPhaserStagesReceived, this, &WahPhaserFrame::onStages);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page WahPhaserFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page WahPhaserFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void WahPhaserFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
    ui.bigDials->setCurrentIndex((int) page);
    ui.smallDials->setCurrentIndex((int) page);
  }
}

void WahPhaserFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void WahPhaserFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void WahPhaserFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void WahPhaserFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void WahPhaserFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
}

void WahPhaserFrame::on_manualDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahManual(value);
}

void WahPhaserFrame::on_peakDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahPeak(value);
}

void WahPhaserFrame::on_pedalRangeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahRange(value);
}

void WahPhaserFrame::on_peakRangeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahPeakRange(value);
}

void WahPhaserFrame::on_pedalModeDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahPedalMode((::WahPedalMode)valueIndex);
}

void WahPhaserFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void WahPhaserFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void WahPhaserFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void WahPhaserFrame::on_touchAttackDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahTouchAttack(value);
}

void WahPhaserFrame::on_touchReleaseDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahTouchRelease(value);
}

void WahPhaserFrame::on_touchBoostDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahTouchBoost(value);
}

void WahPhaserFrame::on_spreadDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationPhaserPeakSpread(value);
}

void WahPhaserFrame::on_stagesDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationPhaserStages(value);
}

void WahPhaserFrame::onManual(double value)
{
  ui.manualDial->setValue(value);
  update();
}

void WahPhaserFrame::onPeak(double value)
{
  ui.peakDial->setValue(value);
  update();
}

void WahPhaserFrame::onPedalRange(double value)
{
  ui.pedalRangeDial->setValue(value);
  update();
}

void WahPhaserFrame::onPeakRange(double value)
{
  ui.peakRangeDial->setValue(value);
  update();
}

void WahPhaserFrame::onPedalMode(WahPedalMode value)
{
  ui.pedalModeDial->setValue((int)value);
  update();
}

void WahPhaserFrame::onMix(double value)
{
  ui.mixDial->setValue(value);
  update();
}

void WahPhaserFrame::onDucking(double value)
{
  ui.duckingDial->setValue(value);
  update();
}

void WahPhaserFrame::onVolume(double value)
{
  ui.volumeDial->setValue(value);
  update();
}

void WahPhaserFrame::onTouchAttack(double value)
{
  ui.touchAttackDial->setValue(value);
  update();
}

void WahPhaserFrame::onTouchRelease(double value)
{
  ui.touchReleaseDial->setValue(value);
  update();
}

void WahPhaserFrame::onTouchBoost(double value)
{
  ui.touchBoostDial->setValue(value);
  update();
}

void WahPhaserFrame::onSpread(double value)
{
  ui.spreadDial->setValue(value);
  update();
}

void WahPhaserFrame::onStages(double value)
{
  ui.stagesDial->setValue(value);
  update();
}
