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
#include "StereoWidenerFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

StereoWidenerFrame::StereoWidenerFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);
}

StereoWidenerFrame::~StereoWidenerFrame()
{
}

void StereoWidenerFrame::activate(QObject& stomp)
{
  show();
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::modulationDepthReceived, this, &StereoWidenerFrame::onIntensity);
    connect(mpStomp, static_cast<void (Stomp::*)(double)>(&Stomp::modulationRateReceived), this, &StereoWidenerFrame::onTune);
    connect(mpStomp, &Stomp::duckingReceived, this, &StereoWidenerFrame::onDucking);

    mpStomp->requestModulationDepth();
    mpStomp->requestModulationRate();
    mpStomp->requestDucking();

    ui.lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui.lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void StereoWidenerFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::modulationDepthReceived, this, &StereoWidenerFrame::onIntensity);
    disconnect(mpStomp, static_cast<void (Stomp::*)(double)>(&Stomp::modulationRateReceived), this, &StereoWidenerFrame::onTune);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &StereoWidenerFrame::onDucking);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page StereoWidenerFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page StereoWidenerFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void StereoWidenerFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
  }
}

void StereoWidenerFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void StereoWidenerFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void StereoWidenerFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void StereoWidenerFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void StereoWidenerFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
}

void StereoWidenerFrame::on_intensityDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationDepth(value);
}

void StereoWidenerFrame::on_tuneDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationRate(value);
}

void StereoWidenerFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void StereoWidenerFrame::onIntensity(double value)
{
  ui.intensityDial->setValue(value);
  update();
}

void StereoWidenerFrame::onTune(double value)
{
  ui.tuneDial->setValue(value);
  update();
}

void StereoWidenerFrame::onDucking(double value)
{
  ui.duckingDial->setValue(value);
  update();
}
