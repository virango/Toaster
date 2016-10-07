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
#include "DriveAndToneDSFrame.h"
#include "ui_DriveAndToneDSFrame.h"
#include "Stomp.h"
#include "Settings.h"
#include "LookUpTables.h"

DriveAndToneDSFrame::DriveAndToneDSFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::DriveAndToneDSFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  if(Settings::get().getKPAOSVersion() < 0x04000000)
  {
    ui->mixDial->setValue(0);
    ui->toneDial->setMinValue(-5);
    ui->toneDial->setMaxValue(5);
    ui->toneDial->setLEDRingType(QToasterDial::Bi);
    ui->lcdDisplay->setValue3Title("");
    ui->lcdDisplay->setValue3("");
    ui->mixDial->setIsActive(false);
  }
}

DriveAndToneDSFrame::~DriveAndToneDSFrame()
{
  delete ui;
}

void DriveAndToneDSFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::volumeReceived, this, &DriveAndToneDSFrame::onVolume);
    connect(mpStomp, &Stomp::distortionShaperDriveReceived, this, &DriveAndToneDSFrame::onDrive);
    connect(mpStomp, &Stomp::distortionBoosterToneReceived, this, &DriveAndToneDSFrame::onTone);

    if(Settings::get().getKPAOSVersion() >= 0x04000000)
    {
      if(mpStomp->getFXType() == BitShaper)
      {
        ui->lcdDisplay->setValue3Title("");
        ui->mixDial->setValue(0);
        ui->lcdDisplay->setValue3("");
        ui->mixDial->setIsActive(false);
      }
      else
      {
        ui->lcdDisplay->setValue3Title("Mix");
        ui->mixDial->setIsActive(true);
        connect(mpStomp, &Stomp::mixReceived, this, &DriveAndToneDSFrame::onMix);
        mpStomp->requestMix();
      }
    }

    mpStomp->requestVolume();
    mpStomp->requestDistortionShaperDrive();
    mpStomp->requestDistortionBoosterTone();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void DriveAndToneDSFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::volumeReceived, this, &DriveAndToneDSFrame::onVolume);
    disconnect(mpStomp, &Stomp::distortionShaperDriveReceived, this, &DriveAndToneDSFrame::onDrive);
    disconnect(mpStomp, &Stomp::distortionBoosterToneReceived, this, &DriveAndToneDSFrame::onTone);

    if((Settings::get().getKPAOSVersion() >= 0x04000000) && (mpStomp->getFXType() != BitShaper))
    {
      disconnect(mpStomp, &Stomp::mixReceived, this, &DriveAndToneDSFrame::onMix);
    }
  }
  mpStomp = nullptr;
}

QToasterLCD::Page DriveAndToneDSFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page DriveAndToneDSFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void DriveAndToneDSFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
  }
}

void DriveAndToneDSFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void DriveAndToneDSFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void DriveAndToneDSFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void DriveAndToneDSFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void DriveAndToneDSFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void DriveAndToneDSFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void DriveAndToneDSFrame::on_driveDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionShaperDrive(value);
}

void DriveAndToneDSFrame::on_toneDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDistortionBoosterTone(value);
}

void DriveAndToneDSFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void DriveAndToneDSFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void DriveAndToneDSFrame::onDrive(double value)
{
  ui->driveDial->setValue(value);
  update();
}

void DriveAndToneDSFrame::onTone(double value)
{
  ui->toneDial->setValue(value);
  update();
}

void DriveAndToneDSFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}
