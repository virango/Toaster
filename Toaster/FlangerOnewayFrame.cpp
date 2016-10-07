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
#include "FlangerOnewayFrame.h"
#include "ui_FlangerOnewayFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

FlangerOnewayFrame::FlangerOnewayFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::FlangerOnewayFrame)
  , mpStomp(nullptr)
{
  ui->setupUi(this);
}

FlangerOnewayFrame::~FlangerOnewayFrame()
{
  delete ui;
}

void FlangerOnewayFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, static_cast<void (Stomp::*)(double)>(&Stomp::modulationRateReceived), this, &FlangerOnewayFrame::onRate);
    connect(mpStomp, &Stomp::modulationDepthReceived, this, &FlangerOnewayFrame::onDepth);
    connect(mpStomp, &Stomp::modulationManualReceived, this, &FlangerOnewayFrame::onManual);
    connect(mpStomp, &Stomp::modulationFeedbackReceived, this, &FlangerOnewayFrame::onFeedback);
    connect(mpStomp, &Stomp::mixReceived, this, &FlangerOnewayFrame::onMix);
    connect(mpStomp, &Stomp::duckingReceived, this, &FlangerOnewayFrame::onDucking);
    connect(mpStomp, &Stomp::volumeReceived, this, &FlangerOnewayFrame::onVolume);
    connect(mpStomp, &Stomp::stereoReceived, this, &FlangerOnewayFrame::onStereo);

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));

    mpStomp->requestModulationRate();
    mpStomp->requestModulationDepth();
    mpStomp->requestModulationManual();
    mpStomp->requestModulationFeedback();
    mpStomp->requestMix();
    mpStomp->requestDucking();
    mpStomp->requestVolume();

    StompInstance si = mpStomp->getInstance();
    if(si != StompX && si != StompMod && si != StompDelay)
    {
      ui->lcdDisplay->setValue7("");
      ui->lcdDisplay->setValue7Title("");
      ui->stereoDial->setIsActive(false);
    }
    else
    {
      ui->lcdDisplay->setValue7Title("Stereo");
      ui->stereoDial->setIsActive(true);
      mpStomp->requestStereo();
    }
  }
}

void FlangerOnewayFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, static_cast<void (Stomp::*)(double)>(&Stomp::modulationRateReceived), this, &FlangerOnewayFrame::onRate);
    disconnect(mpStomp, &Stomp::modulationDepthReceived, this, &FlangerOnewayFrame::onDepth);
    disconnect(mpStomp, &Stomp::modulationManualReceived, this, &FlangerOnewayFrame::onManual);
    disconnect(mpStomp, &Stomp::modulationFeedbackReceived, this, &FlangerOnewayFrame::onFeedback);
    disconnect(mpStomp, &Stomp::mixReceived, this, &FlangerOnewayFrame::onMix);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &FlangerOnewayFrame::onDucking);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &FlangerOnewayFrame::onVolume);
    disconnect(mpStomp, &Stomp::stereoReceived, this, &FlangerOnewayFrame::onStereo);
  }

  mpStomp = nullptr;
}

QToasterLCD::Page FlangerOnewayFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page FlangerOnewayFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void FlangerOnewayFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
  }
}

void FlangerOnewayFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void FlangerOnewayFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void FlangerOnewayFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void FlangerOnewayFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void FlangerOnewayFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void FlangerOnewayFrame::on_rateDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationRate(value + 5.0);
}

void FlangerOnewayFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void FlangerOnewayFrame::on_manualDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationManual(value + 5.0);
}

void FlangerOnewayFrame::on_feedbackDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationFeedback(value);
}

void FlangerOnewayFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void FlangerOnewayFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void FlangerOnewayFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void FlangerOnewayFrame::on_stereoDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyStereo(value);
}

void FlangerOnewayFrame::onRate(double value)
{
  ui->rateDial->setValue(value - 5.0);
  update();
}

void FlangerOnewayFrame::onDepth(double value)
{
  ui->depthDial->setValue(value);
  update();
}

void FlangerOnewayFrame::onManual(double value)
{
  ui->manualDial->setValue(value - 5.0);
  update();
}

void FlangerOnewayFrame::onFeedback(double value)
{
  ui->feedbackDial->setValue(value);
  update();
}

void FlangerOnewayFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void FlangerOnewayFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void FlangerOnewayFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void FlangerOnewayFrame::onStereo(double value)
{
  ui->stereoDial->setValue(value);
  update();
}
