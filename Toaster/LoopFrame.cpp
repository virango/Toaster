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
#include "LoopFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

LoopFrame::LoopFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);
}

LoopFrame::~LoopFrame()
{
}

void LoopFrame::activate(QObject& stomp)
{
  show();
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::volumeReceived, this, &LoopFrame::onVolume);
    connect(mpStomp, &Stomp::mixReceived, this, &LoopFrame::onMix);
    connect(mpStomp, &Stomp::duckingReceived, this, &LoopFrame::onDucking);

    mpStomp->requestVolume();
    mpStomp->requestMix();
    mpStomp->requestDucking();

    ui.lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui.lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void LoopFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::volumeReceived, this, &LoopFrame::onVolume);
    disconnect(mpStomp, &Stomp::mixReceived, this, &LoopFrame::onMix);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &LoopFrame::onDucking);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page LoopFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page LoopFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void LoopFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
  }
}

void LoopFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void LoopFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void LoopFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void LoopFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void LoopFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
}

void LoopFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void LoopFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionShaperDrive(value);
}

void LoopFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void LoopFrame::onVolume(double value)
{
  ui.volumeDial->setValue(value);
  update();
}

void LoopFrame::onMix(double value)
{
  ui.mixDial->setValue(value);
  update();
}

void LoopFrame::onDucking(double value)
{
  ui.duckingDial->setValue(value);
  update();
}
