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
#include "TapDelayFrame.h"
#include "LookUpTables.h"

TapDelayFrame::TapDelayFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);
}

TapDelayFrame::~TapDelayFrame()
{
}

void TapDelayFrame::activate(QObject& stomp)
{
  mpDelay = qobject_cast<Delay*>(&stomp);

  if(mpDelay != nullptr)
  {
    connect(mpDelay, &Delay::bandwidthReceived, this, &TapDelayFrame::onBandwidth);
    connect(mpDelay, &Delay::centerFrequencyReceived, this, &TapDelayFrame::onCenterFrequency);
    connect(mpDelay, &Delay::modulationReceived, this, &TapDelayFrame::onModulation);
    connect(mpDelay, &Delay::duckingReceived, this, &TapDelayFrame::onDucking);
    connect(mpDelay, &Delay::clockLeftReceived, this, &TapDelayFrame::onClockLeft);
    connect(mpDelay, &Delay::clockRightReceived, this, &TapDelayFrame::onClockRight);
    connect(mpDelay, &Delay::volumeReceived, this, &TapDelayFrame::onVolume);

    mpDelay->requestBandwidth();
    mpDelay->requestCenterFrequency();
    mpDelay->requestModulation();
    mpDelay->requestDucking();
    mpDelay->requestClockLeft();
    mpDelay->requestClockRight();
    mpDelay->requestVolume();

    ui.lcdDisplay->setStompInstance("Delay Effect");
    ui.lcdDisplay->setStompName(LookUpTables::delayTypeName(mpDelay->getDelayType()));
  }
}

void TapDelayFrame::deactivate()
{
  if(mpDelay != nullptr)
  {
    disconnect(mpDelay, &Delay::bandwidthReceived, this, &TapDelayFrame::onBandwidth);
    disconnect(mpDelay, &Delay::centerFrequencyReceived, this, &TapDelayFrame::onCenterFrequency);
    disconnect(mpDelay, &Delay::modulationReceived, this, &TapDelayFrame::onModulation);
    disconnect(mpDelay, &Delay::duckingReceived, this, &TapDelayFrame::onDucking);
    disconnect(mpDelay, &Delay::clockLeftReceived, this, &TapDelayFrame::onClockLeft);
    disconnect(mpDelay, &Delay::clockRightReceived, this, &TapDelayFrame::onClockRight);
    disconnect(mpDelay, &Delay::volumeReceived, this, &TapDelayFrame::onVolume);
    mpDelay = nullptr;
  }
}

QToasterLCD::Page TapDelayFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page TapDelayFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void TapDelayFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
  }
}

void TapDelayFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void TapDelayFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void TapDelayFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void TapDelayFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void TapDelayFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
}

void TapDelayFrame::on_bandwidthDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyBandwidth(value);
}

void TapDelayFrame::on_centerFrequencyDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyCenterFrequency(value);
}

void TapDelayFrame::on_modulationDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyModulation(value);
}

void TapDelayFrame::on_duckingDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyDucking(value);
}

void TapDelayFrame::on_clockLeftDial_valueChanged(int valueIndex)
{
  if(mpDelay != nullptr)
    mpDelay->applyClockLeft((::DelayClock)valueIndex);
}

void TapDelayFrame::on_clockRightDial_valueChanged(int valueIndex)
{
  if(mpDelay != nullptr)
    mpDelay->applyClockRight((::DelayClock)valueIndex);
}

void TapDelayFrame::on_volumeDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyVolume(value);
}

void TapDelayFrame::onBandwidth(double value)
{
  ui.bandwidthDial->setValue(value);
}

void TapDelayFrame::onCenterFrequency(double value)
{
  ui.centerFrequencyDial->setValue(value);
}

void TapDelayFrame::onModulation(double value)
{
  ui.modulationDial->setValue(value);
}

void TapDelayFrame::onDucking(double value)
{
  ui.duckingDial->setValue(value);
}

void TapDelayFrame::onClockLeft(::DelayClock clockLeft)
{
  ui.clockLeftDial->setValue((int)clockLeft);
}

void TapDelayFrame::onClockRight(::DelayClock clockRight)
{
  ui.clockRightDial->setValue((int)clockRight);
}

void TapDelayFrame::onVolume(double value)
{
  ui.volumeDial->setValue(value);
}
