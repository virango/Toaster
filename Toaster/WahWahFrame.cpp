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
#include "ui_WahWahFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

WahWahFrame::WahWahFrame(QWidget *parent)
  : QWidget(parent)
  , ui(nullptr)
  , mpStomp(nullptr)
{
}

WahWahFrame::~WahWahFrame()
{
  if(ui != nullptr)
    delete ui;
}

void WahWahFrame::activate(QObject& stomp)
{
  ui = new Ui::WahWahFrame();
  ui->setupUi(this);
  setCurrentDisplayPage(mCurrentPage);

  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(wahManualReceived(double)), this, SLOT(onManual(double)));
    connect(mpStomp, SIGNAL(wahPeakReceived(double)), this, SLOT(onPeak(double)));
    connect(mpStomp, SIGNAL(wahRangeReceived(double)), this, SLOT(onPedalRange(double)));
    connect(mpStomp, SIGNAL(wahPeakRangeReceived(double)), this, SLOT(onPeakRange(double)));
    connect(mpStomp, SIGNAL(wahPedalModeReceived(::WahPedalMode)), this, SLOT(onPedalMode(::WahPedalMode)));
    connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(wahTouchAttackReceived(double)), this, SLOT(onTouchAttack(double)));
    connect(mpStomp, SIGNAL(wahTouchReleaseReceived(double)), this, SLOT(onTouchRelease(double)));
    connect(mpStomp, SIGNAL(wahTouchBoostReceived(double)), this, SLOT(onTouchBoost(double)));

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

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void WahWahFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(wahManualReceived(double)), this, SLOT(onManual(double)));
    disconnect(mpStomp, SIGNAL(wahPeakReceived(double)), this, SLOT(onPeak(double)));
    disconnect(mpStomp, SIGNAL(wahRangeReceived(double)), this, SLOT(onPedalRange(double)));
    disconnect(mpStomp, SIGNAL(wahPeakRangeReceived(double)), this, SLOT(onPeakRange(double)));
    disconnect(mpStomp, SIGNAL(wahPedalModeReceived(::WahPedalMode)), this, SLOT(onPedalMode(::WahPedalMode)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(wahTouchAttackReceived(double)), this, SLOT(onTouchAttack(double)));
    disconnect(mpStomp, SIGNAL(wahTouchReleaseReceived(double)), this, SLOT(onTouchRelease(double)));
    disconnect(mpStomp, SIGNAL(wahTouchBoostReceived(double)), this, SLOT(onTouchBoost(double)));
    mpStomp = nullptr;
  }

  if(ui != nullptr)
  {
    mCurrentPage = ui->lcdDisplay->currentPage();
    delete ui;
    ui = nullptr;
  }
}

QToasterLCD::Page WahWahFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page WahWahFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void WahWahFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
    ui->bigDials->setCurrentIndex((int) page);
    ui->smallDials->setCurrentIndex((int) page);
  }
}

void WahWahFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void WahWahFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void WahWahFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void WahWahFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void WahWahFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
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
  ui->manualDial->setValue(value);
  update();
}

void WahWahFrame::onPeak(double value)
{
  ui->peakDial->setValue(value);
  update();
}

void WahWahFrame::onPedalRange(double value)
{
  ui->pedalRangeDial->setValue(value);
  update();
}

void WahWahFrame::onPeakRange(double value)
{
  ui->peakRangeDial->setValue(value);
  update();
}

void WahWahFrame::onPedalMode(WahPedalMode value)
{
  ui->pedalModeDial->setValue((int)value);
  update();
}

void WahWahFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void WahWahFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void WahWahFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void WahWahFrame::onTouchAttack(double value)
{
  ui->touchAttackDial->setValue(value);
  update();
}

void WahWahFrame::onTouchRelease(double value)
{
  ui->touchReleaseDial->setValue(value);
  update();
}

void WahWahFrame::onTouchBoost(double value)
{
  ui->touchBoostDial->setValue(value);
  update();
}
