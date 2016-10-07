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
#include "TransposeFrame.h"
#include "ui_TransposeFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

TransposeFrame::TransposeFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::TransposeFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

TransposeFrame::~TransposeFrame()
{
  delete ui;
}

void TransposeFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(voice1PitchReceived(double)), this, SLOT(onPitch(double)));
    connect(mpStomp, SIGNAL(smoothChordsReceived(bool)), this, SLOT(onSmoothChords(bool)));

    mpStomp->requestVoice1Pitch();
    mpStomp->requestSmoothChords();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void TransposeFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(voice2PitchReceived(double)), this, SLOT(onPitch(double)));
    disconnect(mpStomp, SIGNAL(smoothChordsReceived(unsigned short)), this, SLOT(onSmoothChords(unsigned short)));
  }
  mpStomp = nullptr;
}

QToasterLCD::Page TransposeFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page TransposeFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void TransposeFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
  }
}

void TransposeFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void TransposeFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void TransposeFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void TransposeFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void TransposeFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void TransposeFrame::on_pitchDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVoice1Pitch(value);
}

void TransposeFrame::on_smoothChordsDial_valueChanged(int valueIndex)
{
  if(mpStomp != nullptr)
    mpStomp->applySmoothChords(valueIndex == 1);
}

void TransposeFrame::onPitch(double value)
{
  ui->pitchDial->setValue(value);
  update();
}

void TransposeFrame::onSmoothChords(bool onOff)
{
  ui->smoothChordsDial->setValue(onOff ? 1 : 0);
  update();
}
