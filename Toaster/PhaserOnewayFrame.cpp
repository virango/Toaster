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
#include "PhaserOnewayFrame.h"
#include "ui_PhaserOnewayFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

PhaserOnewayFrame::PhaserOnewayFrame(QWidget *parent)
  : QWidget(parent)
  , ui(nullptr)
  , mpStomp(nullptr)
{
}

PhaserOnewayFrame::~PhaserOnewayFrame()
{
  if(ui != nullptr)
    delete ui;
}

void PhaserOnewayFrame::activate(QObject& stomp)
{
  ui = new Ui::PhaserOnewayFrame();
  ui->setupUi(this);
  setCurrentDisplayPage(mCurrentPage);

  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, static_cast<void (Stomp::*)(double)>(&Stomp::modulationRateReceived), this, &PhaserOnewayFrame::onRate);
    connect(mpStomp, &Stomp::modulationDepthReceived, this, &PhaserOnewayFrame::onDepth);
    connect(mpStomp, &Stomp::modulationManualReceived, this, &PhaserOnewayFrame::onManual);
    connect(mpStomp, &Stomp::modulationFeedbackReceived, this, &PhaserOnewayFrame::onFeedback);
    connect(mpStomp, &Stomp::modulationPhaserPeakSpreadReceived, this, &PhaserOnewayFrame::onPeakSpread);
    connect(mpStomp, &Stomp::modulationPhaserStagesReceived, this, &PhaserOnewayFrame::onStages);
    connect(mpStomp, &Stomp::mixReceived, this, &PhaserOnewayFrame::onMix);
    connect(mpStomp, &Stomp::duckingReceived, this, &PhaserOnewayFrame::onDucking);
    connect(mpStomp, &Stomp::volumeReceived, this, &PhaserOnewayFrame::onVolume);
    connect(mpStomp, &Stomp::stereoReceived, this, &PhaserOnewayFrame::onStereo);

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));

    mpStomp->requestModulationRate();
    mpStomp->requestModulationDepth();
    mpStomp->requestModulationManual();
    mpStomp->requestModulationFeedback();
    mpStomp->requestModulationPhaserPeakSpread();
    mpStomp->requestModulationPhaserStages();
    mpStomp->requestMix();
    mpStomp->requestDucking();
    mpStomp->requestVolume();
    mpStomp->requestStereo();

    if(mpStomp->getInstance() != StompX && mpStomp->getInstance() != StompMod)
    {
      ui->stereoDial->setIsActive(false);
      ui->lcdDisplay->setValue7("");
      ui->lcdDisplay->setValue7Title("");
    }
    else
    {
      ui->stereoDial->setIsActive(true);
      ui->lcdDisplay->setValue7Title("Stereo");
    }
  }
}

void PhaserOnewayFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, static_cast<void (Stomp::*)(double)>(&Stomp::modulationRateReceived), this, &PhaserOnewayFrame::onRate);
    disconnect(mpStomp, &Stomp::modulationDepthReceived, this, &PhaserOnewayFrame::onDepth);
    disconnect(mpStomp, &Stomp::modulationManualReceived, this, &PhaserOnewayFrame::onManual);
    disconnect(mpStomp, &Stomp::modulationFeedbackReceived, this, &PhaserOnewayFrame::onFeedback);
    disconnect(mpStomp, &Stomp::modulationPhaserPeakSpreadReceived, this, &PhaserOnewayFrame::onPeakSpread);
    disconnect(mpStomp, &Stomp::modulationPhaserStagesReceived, this, &PhaserOnewayFrame::onStages);
    disconnect(mpStomp, &Stomp::mixReceived, this, &PhaserOnewayFrame::onMix);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &PhaserOnewayFrame::onDucking);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &PhaserOnewayFrame::onVolume);
    disconnect(mpStomp, &Stomp::stereoReceived, this, &PhaserOnewayFrame::onStereo);
    mpStomp = nullptr;
  }

  if(ui != nullptr)
  {
    mCurrentPage = ui->lcdDisplay->currentPage();
    delete ui;
    ui = nullptr;
  }
}

QToasterLCD::Page PhaserOnewayFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page PhaserOnewayFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void PhaserOnewayFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
    ui->bigDials->setCurrentIndex((int) page);
    ui->smallDials->setCurrentIndex((int) page);
  }
}

void PhaserOnewayFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void PhaserOnewayFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void PhaserOnewayFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void PhaserOnewayFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void PhaserOnewayFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void PhaserOnewayFrame::on_rateDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationRate(value + 5.0);
}

void PhaserOnewayFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void PhaserOnewayFrame::on_manualDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationManual(value + 5.0);
}

void PhaserOnewayFrame::on_feedbackDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationFeedback(value);
}

void PhaserOnewayFrame::on_peakSpreadDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationPhaserPeakSpread(value);
}

void PhaserOnewayFrame::on_stagesDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationPhaserStages(value);
}

void PhaserOnewayFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void PhaserOnewayFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void PhaserOnewayFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void PhaserOnewayFrame::on_stereoDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyStereo(value);
}

void PhaserOnewayFrame::onRate(double value)
{
  ui->rateDial->setValue(value - 5.0);
  update();
}

void PhaserOnewayFrame::onDepth(double value)
{
  ui->depthDial->setValue(value);
  update();
}

void PhaserOnewayFrame::onManual(double value)
{
  ui->manualDial->setValue(value - 5.0);
  update();
}

void PhaserOnewayFrame::onFeedback(double value)
{
  ui->feedbackDial->setValue(value);
  update();
}

void PhaserOnewayFrame::onPeakSpread(double value)
{
  ui->peakSpreadDial->setValue(value);
  update();
}

void PhaserOnewayFrame::onStages(double value)
{
  ui->stagesDial->setValue(value);
  update();
}

void PhaserOnewayFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void PhaserOnewayFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void PhaserOnewayFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void PhaserOnewayFrame::onStereo(double value)
{
  ui->stereoDial->setValue(value);
  update();
}


