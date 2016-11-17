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
#include "GateFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

GateFrame::GateFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);
}

GateFrame::~GateFrame()
{
}

void GateFrame::activate(QObject& stomp)
{
  show();
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::compressorGateIntensityReceived, this, &GateFrame::onThreshold);

    mpStomp->requestCompressorGateIntensity();

    ui.lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui.lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void GateFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::compressorGateIntensityReceived, this, &GateFrame::onThreshold);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page GateFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page GateFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void GateFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
  }
}

void GateFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void GateFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void GateFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void GateFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void GateFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
}
void GateFrame::on_thresholdDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyCompressorGateIntensity(value);
}

void GateFrame::onThreshold(double value)
{
  ui.thresholdDial->setValue(value);
  update();
}

