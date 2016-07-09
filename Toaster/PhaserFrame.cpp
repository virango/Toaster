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
#include "PhaserFrame.h"
#include "ui_PhaserFrame.h"
#include "Stomp.h"

PhaserFrame::PhaserFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::PhaserFrame)
  , mpStomp(nullptr)
{
  ui->setupUi(this);
  ui->rateDial->setLookUpTable(LookUpTables::getFlangerRateValues());
  setCurrentDisplayPage(QToasterLCD::Page1);
}

PhaserFrame::~PhaserFrame()
{
  delete ui;
}

void PhaserFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, static_cast<void (Stomp::*)(int)>(&Stomp::modulationRateReceived), this, &PhaserFrame::onRate);
    connect(mpStomp, &Stomp::modulationDepthReceived, this, &PhaserFrame::onDepth);
    connect(mpStomp, &Stomp::modulationManualReceived, this, &PhaserFrame::onManual);
    connect(mpStomp, &Stomp::modulationFeedbackReceived, this, &PhaserFrame::onFeedback);
    connect(mpStomp, &Stomp::modulationPhaserPeakSpreadReceived, this, &PhaserFrame::onPeakSpread);
    connect(mpStomp, &Stomp::modulationPhaserStagesReceived, this, &PhaserFrame::onStages);
    connect(mpStomp, &Stomp::mixReceived, this, &PhaserFrame::onMix);
    connect(mpStomp, &Stomp::duckingReceived, this, &PhaserFrame::onDucking);
    connect(mpStomp, &Stomp::volumeReceived, this, &PhaserFrame::onVolume);
    connect(mpStomp, &Stomp::stereoReceived, this, &PhaserFrame::onStereo);

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

void PhaserFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, static_cast<void (Stomp::*)(int)>(&Stomp::modulationRateReceived), this, &PhaserFrame::onRate);
    disconnect(mpStomp, &Stomp::modulationDepthReceived, this, &PhaserFrame::onDepth);
    disconnect(mpStomp, &Stomp::modulationManualReceived, this, &PhaserFrame::onManual);
    disconnect(mpStomp, &Stomp::modulationFeedbackReceived, this, &PhaserFrame::onFeedback);
    disconnect(mpStomp, &Stomp::modulationPhaserPeakSpreadReceived, this, &PhaserFrame::onPeakSpread);
    disconnect(mpStomp, &Stomp::modulationPhaserStagesReceived, this, &PhaserFrame::onStages);
    disconnect(mpStomp, &Stomp::mixReceived, this, &PhaserFrame::onMix);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &PhaserFrame::onDucking);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &PhaserFrame::onVolume);
    disconnect(mpStomp, &Stomp::stereoReceived, this, &PhaserFrame::onStereo);

  }
  mpStomp = nullptr;
}

QToasterLCD::Page PhaserFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page PhaserFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void PhaserFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
    ui->bigDials->setCurrentIndex((int) page);
    ui->smallDials->setCurrentIndex((int) page);
  }
}

void PhaserFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void PhaserFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void PhaserFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void PhaserFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void PhaserFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void PhaserFrame::on_rateDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationRate(value);
}

void PhaserFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void PhaserFrame::on_manualDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationManual(value);
}

void PhaserFrame::on_feedbackDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationFeedback(value);
}

void PhaserFrame::on_peakSpreadDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationPhaserPeakSpread(value);
}

void PhaserFrame::on_stagesDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationPhaserStages(value);
}

void PhaserFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void PhaserFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void PhaserFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void PhaserFrame::on_stereoDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyStereo(value);
}

void PhaserFrame::onRate(int value)
{
  ui->rateDial->setValue(value*128);
  update();
}

void PhaserFrame::onDepth(double value)
{
  ui->depthDial->setValue(value);
  update();
}

void PhaserFrame::onManual(double value)
{
  ui->manualDial->setValue(value);
  update();
}

void PhaserFrame::onFeedback(double value)
{
  ui->feedbackDial->setValue(value);
  update();
}

void PhaserFrame::onPeakSpread(double value)
{
  ui->peakSpreadDial->setValue(value);
  update();
}

void PhaserFrame::onStages(double value)
{
  ui->stagesDial->setValue(value);
  update();
}

void PhaserFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void PhaserFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void PhaserFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void PhaserFrame::onStereo(double value)
{
  ui->stereoDial->setValue(value);
  update();
}
