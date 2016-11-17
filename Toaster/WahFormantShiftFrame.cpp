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
#include "WahFormantShiftFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

WahFormantShiftFrame::WahFormantShiftFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);
}

WahFormantShiftFrame::~WahFormantShiftFrame()
{
}

void WahFormantShiftFrame::activate(QObject& stomp)
{
  show();
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::wahManualReceived, this, &WahFormantShiftFrame::onManual);
    connect(mpStomp, &Stomp::wahRangeReceived, this, &WahFormantShiftFrame::onPedalRange);
    connect(mpStomp, &Stomp::voice2PitchReceived, this, &WahFormantShiftFrame::onPitchShift);
    connect(mpStomp, &Stomp::wahPedalModeReceived, this, &WahFormantShiftFrame::onPedalMode);
    connect(mpStomp, &Stomp::mixReceived, this, &WahFormantShiftFrame::onMix);
    connect(mpStomp, &Stomp::duckingReceived, this, &WahFormantShiftFrame::onDucking);
    connect(mpStomp, &Stomp::volumeReceived, this, &WahFormantShiftFrame::onVolume);
    connect(mpStomp, &Stomp::wahTouchAttackReceived, this, &WahFormantShiftFrame::onTouchAttack);
    connect(mpStomp, &Stomp::wahTouchReleaseReceived, this, &WahFormantShiftFrame::onTouchRelease);
    connect(mpStomp, &Stomp::wahTouchBoostReceived, this, &WahFormantShiftFrame::onTouchBoost);

    mpStomp->requestWahManual();
    mpStomp->requestWahRange();
    mpStomp->requestVoice2Pitch();
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

void WahFormantShiftFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::wahManualReceived, this, &WahFormantShiftFrame::onManual);
    disconnect(mpStomp, &Stomp::wahRangeReceived, this, &WahFormantShiftFrame::onPedalRange);
    disconnect(mpStomp, &Stomp::voice2PitchReceived, this, &WahFormantShiftFrame::onPitchShift);
    disconnect(mpStomp, &Stomp::wahPedalModeReceived, this, &WahFormantShiftFrame::onPedalMode);
    disconnect(mpStomp, &Stomp::mixReceived, this, &WahFormantShiftFrame::onMix);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &WahFormantShiftFrame::onDucking);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &WahFormantShiftFrame::onVolume);
    disconnect(mpStomp, &Stomp::wahTouchAttackReceived, this, &WahFormantShiftFrame::onTouchAttack);
    disconnect(mpStomp, &Stomp::wahTouchReleaseReceived, this, &WahFormantShiftFrame::onTouchRelease);
    disconnect(mpStomp, &Stomp::wahTouchBoostReceived, this, &WahFormantShiftFrame::onTouchBoost);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page WahFormantShiftFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page WahFormantShiftFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void WahFormantShiftFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
    ui.bigDials->setCurrentIndex((int) page);
    ui.smallDials->setCurrentIndex((int) page);
  }
}

void WahFormantShiftFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void WahFormantShiftFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void WahFormantShiftFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void WahFormantShiftFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void WahFormantShiftFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
}

void WahFormantShiftFrame::on_manualDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahManual(value + 5.0);
}

void WahFormantShiftFrame::on_pedalRangeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahRange(value);
}

void WahFormantShiftFrame::on_pitchShiftDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVoice2Pitch(value);
}

void WahFormantShiftFrame::on_pedalModeDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahPedalMode((::WahPedalMode)valueIndex);
}

void WahFormantShiftFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void WahFormantShiftFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void WahFormantShiftFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void WahFormantShiftFrame::on_touchAttackDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahTouchAttack(value);
}

void WahFormantShiftFrame::on_touchReleaseDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahTouchRelease(value);
}

void WahFormantShiftFrame::on_touchBoostDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyWahTouchBoost(value);
}

void WahFormantShiftFrame::onManual(double value)
{
  ui.manualDial->setValue(value - 5.0);
  update();
}

void WahFormantShiftFrame::onPedalRange(double value)
{
  ui.pedalRangeDial->setValue(value);
  update();
}

void  WahFormantShiftFrame::onPitchShift(double value)
{
  ui.pitchShiftDial->setValue(value);
  update();
}

void WahFormantShiftFrame::onPedalMode(WahPedalMode value)
{
  ui.pedalModeDial->setValue((int)value);
  update();
}

void WahFormantShiftFrame::onMix(double value)
{
  ui.mixDial->setValue(value);
  update();
}

void WahFormantShiftFrame::onDucking(double value)
{
  ui.duckingDial->setValue(value);
  update();
}

void WahFormantShiftFrame::onVolume(double value)
{
  ui.volumeDial->setValue(value);
  update();
}

void WahFormantShiftFrame::onTouchAttack(double value)
{
  ui.touchAttackDial->setValue(value);
  update();
}

void WahFormantShiftFrame::onTouchRelease(double value)
{
  ui.touchReleaseDial->setValue(value);
  update();
}

void WahFormantShiftFrame::onTouchBoost(double value)
{
  ui.touchBoostDial->setValue(value);
  update();
}

