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
#include "ToneAndDuckingDSFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

ToneAndDuckingDSFrame::ToneAndDuckingDSFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);
}

ToneAndDuckingDSFrame::~ToneAndDuckingDSFrame()
{
}

void ToneAndDuckingDSFrame::activate(QObject& stomp)
{
  show();
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::volumeReceived, this, &ToneAndDuckingDSFrame::onVolume);
    connect(mpStomp, &Stomp::distortionBoosterToneReceived, this, &ToneAndDuckingDSFrame::onTone);
    connect(mpStomp, &Stomp::duckingReceived, this, &ToneAndDuckingDSFrame::onDucking);

    mpStomp->requestVolume();
    mpStomp->requestDistortionBoosterTone();
    mpStomp->requestDucking();

    ui.lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui.lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void ToneAndDuckingDSFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::volumeReceived, this, &ToneAndDuckingDSFrame::onVolume);
    disconnect(mpStomp, &Stomp::distortionBoosterToneReceived, this, &ToneAndDuckingDSFrame::onTone);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &ToneAndDuckingDSFrame::onDucking);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page ToneAndDuckingDSFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page ToneAndDuckingDSFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void ToneAndDuckingDSFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
  }
}

void ToneAndDuckingDSFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void ToneAndDuckingDSFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void ToneAndDuckingDSFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void ToneAndDuckingDSFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void ToneAndDuckingDSFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
}

void ToneAndDuckingDSFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void ToneAndDuckingDSFrame::on_toneDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionBoosterTone(value);
}

void ToneAndDuckingDSFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void ToneAndDuckingDSFrame::onVolume(double value)
{
  ui.volumeDial->setValue(value);
  update();
}

void ToneAndDuckingDSFrame::onTone(double value)
{
  ui.toneDial->setValue(value);
  update();
}

void ToneAndDuckingDSFrame::onDucking(double value)
{
  ui.duckingDial->setValue(value);
  update();
}

