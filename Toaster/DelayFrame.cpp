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
#include "DelayFrame.h"
#include "ui_DelayFrame.h"

DelayFrame::DelayFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::DelayFrame)
  , mpDelay(nullptr)
{
  ui->setupUi(this);
}

DelayFrame::~DelayFrame()
{
  delete ui;
}

void DelayFrame::activate(QObject& stomp)
{
  mpDelay = qobject_cast<Delay*>(&stomp);

  if(mpDelay != nullptr)
  {
    connect(mpDelay, SIGNAL(bandwidthReceived(double)), this, SLOT(onBandwidth(double)));
    connect(mpDelay, SIGNAL(centerFrequencyReceived(double)), this, SLOT(onCenterFrequency(double)));
    connect(mpDelay, SIGNAL(modulationReceived(double)), this, SLOT(onModulation(double)));
    connect(mpDelay, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    connect(mpDelay, SIGNAL(timeReceived(double)), this, SLOT(onTime(double)));
    connect(mpDelay, SIGNAL(ratioReceived(::DelayRatio)), this, SLOT(onRatio(::DelayRatio)));
    connect(mpDelay, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));

    mpDelay->requestBandwidth();
    mpDelay->requestCenterFrequency();
    mpDelay->requestModulation();
    mpDelay->requestDucking();
    mpDelay->requestTime();
    mpDelay->requestRatio();
    mpDelay->requestVolume();

    ui->lcdDisplay->setStompInstance("Delay Effect");
    ui->lcdDisplay->setStompName(LookUpTables::delayTypeName(mpDelay->getDelayType()));
  }
}

void DelayFrame::deactivate()
{
  if(mpDelay != nullptr)
  {
    disconnect(mpDelay, SIGNAL(bandwidthReceived(double)), this, SLOT(onBandwidth(double)));
    disconnect(mpDelay, SIGNAL(centerFrequencyReceived(double)), this, SLOT(onCenterFrequency(double)));
    disconnect(mpDelay, SIGNAL(modulationReceived(double)), this, SLOT(onModulation(double)));
    disconnect(mpDelay, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpDelay, SIGNAL(timeReceived(double)), this, SLOT(onTime(double)));
    disconnect(mpDelay, SIGNAL(ratioReceived(::DelayRatio)), this, SLOT(onRatio(::DelayRatio)));
    disconnect(mpDelay, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  }
  mpDelay = nullptr;
}

QToasterLCD::Page DelayFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page DelayFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void DelayFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
  }
}

void DelayFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void DelayFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void DelayFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void DelayFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void DelayFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void DelayFrame::on_bandwidthDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyBandwidth(value);
}

void DelayFrame::on_centerFrequencyDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyCenterFrequency(value);
}

void DelayFrame::on_modulationDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyModulation(value);
}

void DelayFrame::on_duckingDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyDucking(value);
}

void DelayFrame::on_timeDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyTime(value);
}

void DelayFrame::on_ratioDial_valueChanged(int valueIndex)
{
  if(mpDelay != nullptr)
    mpDelay->applyRatio((::DelayRatio)valueIndex);
}

void DelayFrame::on_volumeDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyVolume(value);
}

void DelayFrame::onBandwidth(double value)
{
  ui->bandwidthDial->setValue(value);
  update();
}

void DelayFrame::onCenterFrequency(double value)
{
  ui->centerFrequencyDial->setValue(value);
  update();
}

void DelayFrame::onModulation(double value)
{
  ui->modulationDial->setValue(value);
  update();
}

void DelayFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void DelayFrame::onTime(double value)
{
  ui->timeDial->setValue(value);
  update();
}

void DelayFrame::onRatio(::DelayRatio ratio)
{
  ui->ratioDial->setValue((int)ratio);
  update();
}

void DelayFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}
