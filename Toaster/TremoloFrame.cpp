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
#include "TremoloFrame.h"
#include "ui_TremoloFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

TremoloFrame::TremoloFrame(QWidget *parent)
  : QWidget(parent)
  , ui(nullptr)
  , mpStomp(nullptr)
{
}

TremoloFrame::~TremoloFrame()
{
  if(ui != nullptr)
    delete ui;
}

void TremoloFrame::activate(QObject& stomp)
{
  ui = new Ui::TremoloFrame();
  ui->setupUi(this);
  ui->crossoverDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui->rateDial->setLookUpTable(LookUpTables::getTremoloRateValues());
  setCurrentDisplayPage(mCurrentPage);

  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, static_cast<void (Stomp::*)(int)>(&Stomp::modulationRateReceived), this, &TremoloFrame::onRate);
    connect(mpStomp, &Stomp::modulationDepthReceived, this, &TremoloFrame::onDepth);
    connect(mpStomp, static_cast<void (Stomp::*)(int)>(&Stomp::modulationCrossoverReceived), this, &TremoloFrame::onCrossover);
    connect(mpStomp, &Stomp::volumeReceived, this, &TremoloFrame::onVolume);
    connect(mpStomp, &Stomp::duckingReceived, this, &TremoloFrame::onDucking);
    connect(mpStomp, &Stomp::stereoReceived, this, &TremoloFrame::onStereo);

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));

    mpStomp->requestModulationRate();
    mpStomp->requestModulationDepth();
    mpStomp->requestModulationCrossover();
    mpStomp->requestVolume();
    mpStomp->requestDucking();

    StompInstance si = mpStomp->getInstance();
    if(si != StompX && si != StompMod && si != StompDelay)
    {
      ui->lcdDisplay->setValue4("");
      ui->lcdDisplay->setValue4Title("");
      ui->stereoDial->setIsActive(false);
    }
    else
    {
      ui->lcdDisplay->setValue4Title("Stereo");
      ui->stereoDial->setIsActive(true);
      mpStomp->requestStereo();
    }
  }
}

void TremoloFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, static_cast<void (Stomp::*)(int)>(&Stomp::modulationRateReceived), this, &TremoloFrame::onRate);
    disconnect(mpStomp, &Stomp::modulationDepthReceived, this, &TremoloFrame::onDepth);
    disconnect(mpStomp, static_cast<void (Stomp::*)(int)>(&Stomp::modulationCrossoverReceived), this, &TremoloFrame::onCrossover);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &TremoloFrame::onVolume);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &TremoloFrame::onDucking);
    disconnect(mpStomp, &Stomp::stereoReceived, this, &TremoloFrame::onStereo);
    mpStomp = nullptr;
  }

  if(ui != nullptr)
  {
    mCurrentPage = ui->lcdDisplay->currentPage();
    delete ui;
    ui = nullptr;
  }
}

QToasterLCD::Page TremoloFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page TremoloFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void TremoloFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
  }
}

void TremoloFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void TremoloFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void TremoloFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void TremoloFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void TremoloFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void TremoloFrame::on_rateDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationRate((int)value);
}

void TremoloFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void TremoloFrame::on_crossoverDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationCrossover(value);
}

void TremoloFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void TremoloFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void TremoloFrame::on_stereoDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyStereo(value);
}

void TremoloFrame::onRate(int value)
{
  ui->rateDial->setValue(value*128);
  update();
}

void TremoloFrame::onDepth(double value)
{
  ui->depthDial->setValue(value);
  update();
}

void TremoloFrame::onCrossover(int value)
{
  ui->crossoverDial->setValue(value);
  update();
}

void TremoloFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void TremoloFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void TremoloFrame::onStereo(double value)
{
  ui->stereoDial->setValue(value);
  update();
}
