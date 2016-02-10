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
#include "RotarySpeakerFrame.h"
#include "ui_RotarySpeakerFrame.h"
#include "Stomp.h"

RotarySpeakerFrame::RotarySpeakerFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::RotarySpeakerFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  ui->distanceDial->setLookUpTable(LookUpTables::getRotaryDistanceValues());
}

RotarySpeakerFrame::~RotarySpeakerFrame()
{
  delete ui;
}

void RotarySpeakerFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(rotaryDistanceReceived(int)), this, SLOT(onDistance(int)));
    connect(mpStomp, SIGNAL(rotaryBalanceReceived(double)), this, SLOT(onLowHighBalance(double)));
    connect(mpStomp, SIGNAL(rotarySpeedReceived(::RotarySpeed)), this, SLOT(onRotarySpeed(::RotarySpeed)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));

    mpStomp->requestRotaryDistance();
    mpStomp->requestRotaryBalance();
    mpStomp->requestRotarySpeed();
    mpStomp->requestVolume();
    mpStomp->requestMix();
    mpStomp->requestDucking();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void RotarySpeakerFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(rotaryDistanceReceived(int)), this, SLOT(onDistance(int)));
    disconnect(mpStomp, SIGNAL(rotaryBalanceReceived(double)), this, SLOT(onLowHighBalance(double)));
    disconnect(mpStomp, SIGNAL(rotarySpeedReceived(::RotarySpeed)), this, SLOT(onRotarySpeed(::RotarySpeed)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
  }
  mpStomp = nullptr;
}

QToasterLCD::Page RotarySpeakerFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page RotarySpeakerFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void RotarySpeakerFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
  }
}

void RotarySpeakerFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void RotarySpeakerFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void RotarySpeakerFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void RotarySpeakerFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void RotarySpeakerFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void RotarySpeakerFrame::on_distanceDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyRotaryDistance(value);
}

void RotarySpeakerFrame::on_lowHighBalanceDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyRotaryBalance(value);
}

void RotarySpeakerFrame::on_rotarySpeedDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyRotarySpeed((::RotarySpeed)value);
}

void RotarySpeakerFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void RotarySpeakerFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void RotarySpeakerFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void RotarySpeakerFrame::onDistance(int value)
{
  ui->distanceDial->setValue(value);
  update();
}

void RotarySpeakerFrame::onLowHighBalance(double value)
{
  ui->lowHighBalanceDial->setValue(value);
  update();
}

void RotarySpeakerFrame::onRotarySpeed(::RotarySpeed value)
{
  ui->rotarySpeedDial->setValue(value);
  update();
}

void RotarySpeakerFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void RotarySpeakerFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void RotarySpeakerFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}
