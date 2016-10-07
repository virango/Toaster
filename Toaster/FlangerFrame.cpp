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
#include "FlangerFrame.h"
#include "ui_FlangerFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

FlangerFrame::FlangerFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::FlangerFrame)
  , mpStomp(nullptr)
{
  ui->setupUi(this);
  ui->rateDial->setLookUpTable(LookUpTables::getFlangerRateValues());
}

FlangerFrame::~FlangerFrame()
{
  delete ui;
}
void FlangerFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, static_cast<void (Stomp::*)(int)>(&Stomp::modulationRateReceived), this, &FlangerFrame::onRate);
    connect(mpStomp, &Stomp::modulationDepthReceived, this, &FlangerFrame::onDepth);
    connect(mpStomp, &Stomp::modulationManualReceived, this, &FlangerFrame::onManual);
    connect(mpStomp, &Stomp::modulationFeedbackReceived, this, &FlangerFrame::onFeedback);
    connect(mpStomp, &Stomp::mixReceived, this, &FlangerFrame::onMix);
    connect(mpStomp, &Stomp::duckingReceived, this, &FlangerFrame::onDucking);
    connect(mpStomp, &Stomp::volumeReceived, this, &FlangerFrame::onVolume);
    connect(mpStomp, &Stomp::stereoReceived, this, &FlangerFrame::onStereo);

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

void FlangerFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, static_cast<void (Stomp::*)(int)>(&Stomp::modulationRateReceived), this, &FlangerFrame::onRate);
    disconnect(mpStomp, &Stomp::modulationDepthReceived, this, &FlangerFrame::onDepth);
    disconnect(mpStomp, &Stomp::modulationManualReceived, this, &FlangerFrame::onManual);
    disconnect(mpStomp, &Stomp::modulationFeedbackReceived, this, &FlangerFrame::onFeedback);
    disconnect(mpStomp, &Stomp::mixReceived, this, &FlangerFrame::onMix);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &FlangerFrame::onDucking);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &FlangerFrame::onVolume);
    disconnect(mpStomp, &Stomp::stereoReceived, this, &FlangerFrame::onStereo);
  }

  mpStomp = nullptr;
}

QToasterLCD::Page FlangerFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page FlangerFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void FlangerFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
  }
}

void FlangerFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void FlangerFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void FlangerFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void FlangerFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void FlangerFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void FlangerFrame::on_rateDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationRate(value);
}

void FlangerFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void FlangerFrame::on_manualDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationManual(value);
}

void FlangerFrame::on_feedbackDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationFeedback(value);
}

void FlangerFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void FlangerFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void FlangerFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void FlangerFrame::on_stereoDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyStereo(value);
}

void FlangerFrame::onRate(int value)
{
  ui->rateDial->setValue(value*128);
  update();
}

void FlangerFrame::onDepth(double value)
{
  ui->depthDial->setValue(value);
  update();
}

void FlangerFrame::onManual(double value)
{
  ui->manualDial->setValue(value);
  update();
}

void FlangerFrame::onFeedback(double value)
{
  ui->feedbackDial->setValue(value);
  update();
}

void FlangerFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void FlangerFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void FlangerFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void FlangerFrame::onStereo(double value)
{
  ui->stereoDial->setValue(value);
  update();
}
