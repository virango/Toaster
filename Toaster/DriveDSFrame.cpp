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
#include "DriveDSFrame.h"
#include "ui_DriveDSFrame.h"
#include "Stomp.h"
#include "Settings.h"

DriveDSFrame::DriveDSFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::DriveDSFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  if(Settings::get().getKPAOSVersion() < 0x04000000)
  {
    ui->mixDial->setValue(0);
    ui->lcdDisplay->setValue3Title("");
    ui->lcdDisplay->setValue3("");
    ui->mixDial->setIsActive(false);
  }
}

DriveDSFrame::~DriveDSFrame()
{
  delete ui;
}

void DriveDSFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::volumeReceived, this, &DriveDSFrame::onVolume);
    connect(mpStomp, &Stomp::distortionShaperDriveReceived, this, &DriveDSFrame::onDrive);

    if(Settings::get().getKPAOSVersion() >= 0x04000000)
    {
      if(mpStomp->getFXType() == FuzzDS)
      {
        ui->lcdDisplay->setValue3Title("Mix");
        ui->mixDial->setIsActive(true);
        connect(mpStomp, &Stomp::mixReceived, this, &DriveDSFrame::onMix);
        mpStomp->requestMix();
      }
      else
      {
        ui->lcdDisplay->setValue3Title("");
        ui->mixDial->setValue(0);
        ui->lcdDisplay->setValue3("");
        ui->mixDial->setIsActive(false);
      }
    }

    mpStomp->requestVolume();
    mpStomp->requestDistortionShaperDrive();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void DriveDSFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::volumeReceived, this, &DriveDSFrame::onVolume);
    disconnect(mpStomp, &Stomp::distortionShaperDriveReceived, this, &DriveDSFrame::onDrive);

    if((Settings::get().getKPAOSVersion() >= 0x04000000) && (mpStomp->getFXType() == FuzzDS))
      disconnect(mpStomp, &Stomp::mixReceived, this, &DriveDSFrame::onMix);
  }
  mpStomp = nullptr;
}

QToasterLCD::Page DriveDSFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page DriveDSFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void DriveDSFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
  }
}

void DriveDSFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void DriveDSFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void DriveDSFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void DriveDSFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void DriveDSFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void DriveDSFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void DriveDSFrame::on_driveDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionShaperDrive(value);
}

void DriveDSFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void DriveDSFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void DriveDSFrame::onDrive(double value)
{
  ui->driveDial->setValue(value);
  update();
}

void DriveDSFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}
