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
#include "MetalDSFrame.h"
#include "ui_MetalDSFrame.h"
#include "Stomp.h"

MetalDSFrame::MetalDSFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::MetalDSFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  ui->midFreqDial->setLookUpTable(LookUpTables::getFrequencyValues());
}

MetalDSFrame::~MetalDSFrame()
{
  delete ui;
}

void MetalDSFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::volumeReceived, this, &MetalDSFrame::onVolume);
    connect(mpStomp, &Stomp::distortionShaperDriveReceived, this, &MetalDSFrame::onDrive);
    connect(mpStomp, &Stomp::parametricEQLowGainReceived, this, &MetalDSFrame::onLow);
    connect(mpStomp, &Stomp::parametricEQPeakGainReceived, this, &MetalDSFrame::onMiddle);
    connect(mpStomp, &Stomp::parametricEQPeakFrequencyReceived, this, &MetalDSFrame::onMidFreq);
    connect(mpStomp, &Stomp::parametricEQHighGainReceived, this, &MetalDSFrame::onHigh);
    connect(mpStomp, &Stomp::mixReceived, this, &MetalDSFrame::onMix);

    mpStomp->requestVolume();
    mpStomp->requestDistortionShaperDrive();
    mpStomp->requestParametricEQLowGain();
    mpStomp->requestParametricEQPeakGain();
    mpStomp->requestParametricEQPeakFrequency();
    mpStomp->requestParametricEQHighGain();
    mpStomp->requestMix();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void MetalDSFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::volumeReceived, this, &MetalDSFrame::onVolume);
    disconnect(mpStomp, &Stomp::distortionShaperDriveReceived, this, &MetalDSFrame::onDrive);
    disconnect(mpStomp, &Stomp::parametricEQLowGainReceived, this, &MetalDSFrame::onLow);
    disconnect(mpStomp, &Stomp::parametricEQPeakGainReceived, this, &MetalDSFrame::onMiddle);
    disconnect(mpStomp, &Stomp::parametricEQPeakFrequencyReceived, this, &MetalDSFrame::onMidFreq);
    disconnect(mpStomp, &Stomp::parametricEQHighGainReceived, this, &MetalDSFrame::onHigh);
    disconnect(mpStomp, &Stomp::mixReceived, this, &MetalDSFrame::onMix);
  }
  mpStomp = nullptr;
}

QToasterLCD::Page MetalDSFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page MetalDSFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void MetalDSFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
  }
}

void MetalDSFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void MetalDSFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void MetalDSFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void MetalDSFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void MetalDSFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void MetalDSFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void MetalDSFrame::on_driveDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionShaperDrive(value);
}

void MetalDSFrame::on_lowDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQLowGain(value);
}

void MetalDSFrame::on_middleDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakGain(value);
}

void MetalDSFrame::on_midFreqDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakFrequency(value);
}

void MetalDSFrame::on_highDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQHighGain(value);
}

void MetalDSFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void MetalDSFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void MetalDSFrame::onDrive(double value)
{
  ui->driveDial->setValue(value);
  update();
}

void MetalDSFrame::onLow(double value)
{
  ui->lowDial->setValue(value);
  update();
}

void MetalDSFrame::onMiddle(double value)
{
  ui->middleDial->setValue(value);
  update();
}

void MetalDSFrame::onMidFreq(int value)
{
  ui->midFreqDial->setValue(value);
  update();
}

void MetalDSFrame::onHigh(double value)
{
  ui->highDial->setValue(value);
  update();
}

void MetalDSFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}
