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
#include "CompressorFrame.h"
#include "ui_CompressorFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

CompressorFrame::CompressorFrame(QWidget *parent)
  : QWidget(parent)
  , ui(nullptr)
  , mpStomp(nullptr)
{
}

CompressorFrame::~CompressorFrame()
{
  if(ui != nullptr)
    delete ui;
}

void CompressorFrame::activate(QObject& stomp)
{
  ui = new Ui::CompressorFrame();
  ui->setupUi(this);
  setCurrentDisplayPage(mCurrentPage);

  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::compressorGateIntensityReceived, this, &CompressorFrame::onIntensity);
    connect(mpStomp, &Stomp::compressorAttackReceived, this, &CompressorFrame::onAttack);
    connect(mpStomp, &Stomp::compressorSquashReceived, this, &CompressorFrame::onSquash);
    connect(mpStomp, &Stomp::volumeReceived, this, &CompressorFrame::onVolume);
    connect(mpStomp, &Stomp::mixReceived, this, &CompressorFrame::onMix);

    mpStomp->requestCompressorGateIntensity();
    mpStomp->requestCompressorAttack();
    mpStomp->requestCompressorSquash();
    mpStomp->requestVolume();
    mpStomp->requestMix();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void CompressorFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::compressorGateIntensityReceived, this, &CompressorFrame::onIntensity);
    disconnect(mpStomp, &Stomp::compressorAttackReceived, this, &CompressorFrame::onAttack);
    disconnect(mpStomp, &Stomp::compressorSquashReceived, this, &CompressorFrame::onSquash);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &CompressorFrame::onVolume);
    disconnect(mpStomp, &Stomp::mixReceived, this, &CompressorFrame::onMix);
  }

  mpStomp = nullptr;

  if(ui != nullptr)
  {
    mCurrentPage = ui->lcdDisplay->currentPage();
    delete ui;
    ui = nullptr;
  }
}

QToasterLCD::Page CompressorFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page CompressorFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void CompressorFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
  }
}

void CompressorFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void CompressorFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void CompressorFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void CompressorFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void CompressorFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void CompressorFrame::on_intensityDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyCompressorGateIntensity(value);
}

void CompressorFrame::on_attackDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyCompressorAttack(value);
}

void CompressorFrame::on_squashDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyCompressorSquash(value);
}

void CompressorFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void CompressorFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void CompressorFrame::onIntensity(double value)
{
  ui->intensityDial->setValue(value);
  update();
}
void CompressorFrame::onAttack(double value)
{
  ui->attackDial->setValue(value);
  update();
}

void CompressorFrame::onSquash(double value)
{
  ui->squashDial->setValue(value);
  update();
}

void CompressorFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void CompressorFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}
