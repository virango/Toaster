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
#include "RectiShaperFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

RectiShaperFrame::RectiShaperFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);
}

RectiShaperFrame::~RectiShaperFrame()
{
}

void RectiShaperFrame::activate(QObject& stomp)
{
  show();
  mpStomp = qobject_cast<Stomp*>(&stomp);

  connect(mpStomp, &Stomp::volumeReceived, this, &RectiShaperFrame::onVolume);
  connect(mpStomp, &Stomp::distortionShaperDriveReceived, this, &RectiShaperFrame::onDrive);
  connect(mpStomp, &Stomp::duckingReceived, this, &RectiShaperFrame::onDucking);

  mpStomp->requestVolume();
  mpStomp->requestDistortionShaperDrive();
  mpStomp->requestDucking();

  ui.lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
  ui.lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
}

void RectiShaperFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::volumeReceived, this, &RectiShaperFrame::onVolume);
    disconnect(mpStomp, &Stomp::distortionShaperDriveReceived, this, &RectiShaperFrame::onDrive);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &RectiShaperFrame::onDucking);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page RectiShaperFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page RectiShaperFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void RectiShaperFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
  }
}

void RectiShaperFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void RectiShaperFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void RectiShaperFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void RectiShaperFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void RectiShaperFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
}

void RectiShaperFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void RectiShaperFrame::on_driveDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionShaperDrive(value);
}

void RectiShaperFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void RectiShaperFrame::onVolume(double value)
{
  ui.volumeDial->setValue(value);
  update();
}

void RectiShaperFrame::onDrive(double value)
{
  ui.driveDial->setValue(value);
  update();
}

void RectiShaperFrame::onDucking(double value)
{
  ui.duckingDial->setValue(value);
  update();
}
