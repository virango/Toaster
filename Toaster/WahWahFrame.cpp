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
#include "WahWahFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

WahWahFrame::WahWahFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);
}

WahWahFrame::~WahWahFrame()
{
}

void WahWahFrame::activate(QObject& stomp)
{
  show();
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::wahManualReceived, this, &WahWahFrame::onManual);
    connect(mpStomp, &Stomp::wahPeakReceived, this, &WahWahFrame::onPeak);
    connect(mpStomp, &Stomp::wahRangeReceived, this, &WahWahFrame::onPedalRange);
    connect(mpStomp, &Stomp::wahPeakRangeReceived, this, &WahWahFrame::onPeakRange);
    connect(mpStomp, &Stomp::wahPedalModeReceived, this, &WahWahFrame::onPedalMode);
    connect(mpStomp, &Stomp::mixReceived, this, &WahWahFrame::onMix);
    connect(mpStomp, &Stomp::duckingReceived, this, &WahWahFrame::onDucking);
    connect(mpStomp, &Stomp::volumeReceived, this, &WahWahFrame::onVolume);
    connect(mpStomp, &Stomp::wahTouchAttackReceived, this, &WahWahFrame::onTouchAttack);
    connect(mpStomp, &Stomp::wahTouchReleaseReceived, this, &WahWahFrame::onTouchRelease);
    connect(mpStomp, &Stomp::wahTouchBoostReceived, this, &WahWahFrame::onTouchBoost);

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

    ui.lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui.lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void WahWahFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::wahManualReceived, this, &WahWahFrame::onManual);
    disconnect(mpStomp, &Stomp::wahPeakReceived, this, &WahWahFrame::onPeak);
    disconnect(mpStomp, &Stomp::wahRangeReceived, this, &WahWahFrame::onPedalRange);
    disconnect(mpStomp, &Stomp::wahPeakRangeReceived, this, &WahWahFrame::onPeakRange);
    disconnect(mpStomp, &Stomp::wahPedalModeReceived, this, &WahWahFrame::onPedalMode);
    disconnect(mpStomp, &Stomp::mixReceived, this, &WahWahFrame::onMix);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &WahWahFrame::onDucking);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &WahWahFrame::onVolume);
    disconnect(mpStomp, &Stomp::wahTouchAttackReceived, this, &WahWahFrame::onTouchAttack);
    disconnect(mpStomp, &Stomp::wahTouchReleaseReceived, this, &WahWahFrame::onTouchRelease);
    disconnect(mpStomp, &Stomp::wahTouchBoostReceived, this, &WahWahFrame::onTouchBoost);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page WahWahFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page WahWahFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void WahWahFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
    ui.bigDials->setCurrentIndex((int) page);
    ui.smallDials->setCurrentIndex((int) page);
  }
}

void WahWahFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void WahWahFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void WahWahFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void WahWahFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void WahWahFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
}

void WahWahFrame::on_manualDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahManual(value);
}

void WahWahFrame::on_peakDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahPeak(value);
}

void WahWahFrame::on_pedalRangeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahRange(value);
}

void WahWahFrame::on_peakRangeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahPeakRange(value);
}

void WahWahFrame::on_pedalModeDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahPedalMode((::WahPedalMode)valueIndex);
}

void WahWahFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void WahWahFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void WahWahFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void WahWahFrame::on_touchAttackDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahTouchAttack(value);
}

void WahWahFrame::on_touchReleaseDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahTouchRelease(value);
}

void WahWahFrame::on_touchBoostDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahTouchBoost(value);
}

void WahWahFrame::onManual(double value)
{
  ui.manualDial->setValue(value);
  update();
}

void WahWahFrame::onPeak(double value)
{
  ui.peakDial->setValue(value);
  update();
}

void WahWahFrame::onPedalRange(double value)
{
  ui.pedalRangeDial->setValue(value);
  update();
}

void WahWahFrame::onPeakRange(double value)
{
  ui.peakRangeDial->setValue(value);
  update();
}

void WahWahFrame::onPedalMode(WahPedalMode value)
{
  ui.pedalModeDial->setValue((int)value);
  update();
}

void WahWahFrame::onMix(double value)
{
  ui.mixDial->setValue(value);
  update();
}

void WahWahFrame::onDucking(double value)
{
  ui.duckingDial->setValue(value);
  update();
}

void WahWahFrame::onVolume(double value)
{
  ui.volumeDial->setValue(value);
  update();
}

void WahWahFrame::onTouchAttack(double value)
{
  ui.touchAttackDial->setValue(value);
  update();
}

void WahWahFrame::onTouchRelease(double value)
{
  ui.touchReleaseDial->setValue(value);
  update();
}

void WahWahFrame::onTouchBoost(double value)
{
  ui.touchBoostDial->setValue(value);
  update();
}
