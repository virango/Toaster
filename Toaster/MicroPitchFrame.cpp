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
#include "MicroPitchFrame.h"
#include "ui_MicroPitchFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

MicroPitchFrame::MicroPitchFrame(QWidget *parent)
  : QWidget(parent)
  , ui(nullptr)
  , mpStomp(nullptr)
{
}

MicroPitchFrame::~MicroPitchFrame()
{
  if(ui != nullptr)
    delete ui;
}

void MicroPitchFrame::activate(QObject& stomp)
{
  ui = new Ui::MicroPitchFrame();
  ui->setupUi(this);
  ui->crossoverDial->setLookUpTable(LookUpTables::getFrequencyValues());
  setCurrentDisplayPage(mCurrentPage);

  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::modulationDepthReceived, this, &MicroPitchFrame::onDetune);
    connect(mpStomp, static_cast<void (Stomp::*)(int)>(&Stomp::modulationCrossoverReceived), this, &MicroPitchFrame::onCrossover);
    connect(mpStomp, &Stomp::volumeReceived, this, &MicroPitchFrame::onVolume);
    connect(mpStomp, &Stomp::mixReceived, this, &MicroPitchFrame::onMix);
    connect(mpStomp, &Stomp::duckingReceived, this, &MicroPitchFrame::onDucking);

    mpStomp->requestModulationDepth();
    mpStomp->requestModulationCrossover();
    mpStomp->requestVolume();
    mpStomp->requestMix();
    mpStomp->requestDucking();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void MicroPitchFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::modulationDepthReceived, this, &MicroPitchFrame::onDetune);
    disconnect(mpStomp, static_cast<void (Stomp::*)(int)>(&Stomp::modulationCrossoverReceived), this, &MicroPitchFrame::onCrossover);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &MicroPitchFrame::onVolume);
    disconnect(mpStomp, &Stomp::mixReceived, this, &MicroPitchFrame::onMix);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &MicroPitchFrame::onDucking);
    mpStomp = nullptr;
  }

  if(ui != nullptr)
  {
    mCurrentPage = ui->lcdDisplay->currentPage();
    delete ui;
    ui = nullptr;
  }
}

QToasterLCD::Page MicroPitchFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page MicroPitchFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void MicroPitchFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
  }
}

void MicroPitchFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void MicroPitchFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void MicroPitchFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void MicroPitchFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void MicroPitchFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void MicroPitchFrame::on_detuneDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void MicroPitchFrame::on_crossoverDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationCrossover(value);
}

void MicroPitchFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void MicroPitchFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void MicroPitchFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void MicroPitchFrame::onDetune(double value)
{
  ui->detuneDial->setValue(value);
  update();
}

void MicroPitchFrame::onCrossover(int value)
{
  ui->crossoverDial->setValue(value);
  update();
}

void MicroPitchFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void MicroPitchFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void MicroPitchFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}
