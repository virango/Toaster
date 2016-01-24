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

CompressorFrame::CompressorFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::CompressorFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

CompressorFrame::~CompressorFrame()
{
  delete ui;
}

void CompressorFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(compressorGateIntensityReceived(double)), this, SLOT(onIntensity(double)));
    connect(mpStomp, SIGNAL(compressorAttackReceived(double)), this, SLOT(onAttack(double)));
    connect(mpStomp, SIGNAL(compressorSquashReceived(double)), this, SLOT(onSquash(double)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));

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
    disconnect(mpStomp, SIGNAL(compressorGateIntensityReceived(double)), this, SLOT(onIntensity(double)));
    disconnect(mpStomp, SIGNAL(compressorAttackReceived(double)), this, SLOT(onAttack(double)));
    disconnect(mpStomp, SIGNAL(compressorSquashReceived(double)), this, SLOT(onSquash(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
  }

  mpStomp = nullptr;
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
