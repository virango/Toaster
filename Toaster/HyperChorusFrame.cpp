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
#include "HyperChorusFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

HyperChorusFrame::HyperChorusFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);
  ui.crossoverDial->setLookUpTable(LookUpTables::getFrequencyValues());
}

HyperChorusFrame::~HyperChorusFrame()
{
}

void HyperChorusFrame::activate(QObject& stomp)
{
  show();
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::modulationDepthReceived, this, &HyperChorusFrame::onDepth);
    connect(mpStomp, &Stomp::modulationHyperChorusAmountReceived, this, &HyperChorusFrame::onAmount);
    connect(mpStomp, static_cast<void (Stomp::*)(int)>(&Stomp::modulationCrossoverReceived), this, &HyperChorusFrame::onCrossover);
    connect(mpStomp, &Stomp::mixReceived, this, &HyperChorusFrame::onMix);
    connect(mpStomp, &Stomp::volumeReceived, this, &HyperChorusFrame::onVolume);
    connect(mpStomp, &Stomp::duckingReceived, this, &HyperChorusFrame::onDucking);

    mpStomp->requestModulationDepth();
    mpStomp->requestModulationHyperChorusAmount();
    mpStomp->requestModulationCrossover();
    mpStomp->requestMix();
    mpStomp->requestVolume();
    mpStomp->requestDucking();

    ui.lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui.lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void HyperChorusFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::modulationDepthReceived, this, &HyperChorusFrame::onDepth);
    disconnect(mpStomp, &Stomp::modulationHyperChorusAmountReceived, this, &HyperChorusFrame::onAmount);
    disconnect(mpStomp, static_cast<void (Stomp::*)(int)>(&Stomp::modulationCrossoverReceived), this, &HyperChorusFrame::onCrossover);
    disconnect(mpStomp, &Stomp::mixReceived, this, &HyperChorusFrame::onMix);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &HyperChorusFrame::onVolume);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &HyperChorusFrame::onDucking);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page HyperChorusFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page HyperChorusFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void HyperChorusFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
  }
}

void HyperChorusFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void HyperChorusFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void HyperChorusFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void HyperChorusFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void HyperChorusFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
}

void HyperChorusFrame::on_depthDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void HyperChorusFrame::on_amountDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationHyperChorusAmount(value);
}

void HyperChorusFrame::on_crossoverDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationCrossover(value);
}

void HyperChorusFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void HyperChorusFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void HyperChorusFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void HyperChorusFrame::onDepth(double value)
{
  ui.depthDial->setValue(value);
  update();
}

void HyperChorusFrame::onAmount(double value)
{
  ui.amountDial->setValue(value);
  update();
}

void HyperChorusFrame::onCrossover(int value)
{
  ui.crossoverDial->setValue(value);
  update();
}

void HyperChorusFrame::onMix(double value)
{
  ui.mixDial->setValue(value);
  update();
}

void HyperChorusFrame::onVolume(double value)
{
  ui.volumeDial->setValue(value);
  update();
}

void HyperChorusFrame::onDucking(double value)
{
  ui.duckingDial->setValue(value);
  update();
}
