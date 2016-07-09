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
#include "VibratoFrame.h"
#include "ui_VibratoFrame.h"
#include "Stomp.h"
#include "Settings.h"

VibratoFrame::VibratoFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::VibratoFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  ui->crossoverDial->setLookUpTable(LookUpTables::getFrequencyValues());
}

VibratoFrame::~VibratoFrame()
{
  delete ui;
}

void VibratoFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, static_cast<void (Stomp::*)(double)>(&Stomp::modulationRateReceived), this, &VibratoFrame::onRate);
    connect(mpStomp, &Stomp::modulationDepthReceived, this, &VibratoFrame::onDepth);
    connect(mpStomp, static_cast<void (Stomp::*)(int)>(&Stomp::modulationCrossoverReceived), this, &VibratoFrame::onCrossover);
    connect(mpStomp, &Stomp::volumeReceived, this, &VibratoFrame::onVolume);

    if(Settings::get().getKPAOSVersion() >= 0x04000000)
    {
      connect(mpStomp, &Stomp::duckingReceived, this, &VibratoFrame::onDucking);
      mpStomp->requestDucking();
    }

    mpStomp->requestModulationRate();
    mpStomp->requestModulationDepth();
    mpStomp->requestModulationCrossover();
    mpStomp->requestVolume();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void VibratoFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, static_cast<void (Stomp::*)(double)>(&Stomp::modulationRateReceived), this, &VibratoFrame::onRate);
    disconnect(mpStomp, &Stomp::modulationDepthReceived, this, &VibratoFrame::onDepth);
    disconnect(mpStomp, static_cast<void (Stomp::*)(int)>(&Stomp::modulationCrossoverReceived), this, &VibratoFrame::onCrossover);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &VibratoFrame::onVolume);

    if(Settings::get().getKPAOSVersion() >= 0x04000000)
      disconnect(mpStomp, &Stomp::duckingReceived, this, &VibratoFrame::onDucking);

  }
  mpStomp = nullptr;
}

QToasterLCD::Page VibratoFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page VibratoFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void VibratoFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
  }
}

void VibratoFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void VibratoFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void VibratoFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void VibratoFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void VibratoFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void VibratoFrame::on_rateDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationRate(value);
}

void VibratoFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void VibratoFrame::on_crossoverDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationCrossover(value);
}

void VibratoFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void VibratoFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void VibratoFrame::onRate(double value)
{
  ui->rateDial->setValue(value);
  update();
}

void VibratoFrame::onDepth(double value)
{
  ui->depthDial->setValue(value);
  update();
}

void VibratoFrame::onCrossover(int value)
{
  ui->crossoverDial->setValue(value);
  update();
}

void VibratoFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}


void VibratoFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}
