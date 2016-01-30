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
#include "MetalEqualizerFrame.h"
#include "ui_MetalEqualizerFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

MetalEqualizerFrame::MetalEqualizerFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::MetalEqualizerFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  ui->pageDial->setValue(0);
  ui->lowCutDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui->highCutDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui->midFreqDial->setLookUpTable(LookUpTables::getFrequencyValues());
}

MetalEqualizerFrame::~MetalEqualizerFrame()
{
  delete ui;
}

void MetalEqualizerFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(parametricEQLowGainReceived(double)), this, SLOT(onLowDial(double)));
    connect(mpStomp, SIGNAL(parametricEQPeakGainReceived(double)), this, SLOT(onMiddleDial(double)));
    connect(mpStomp, SIGNAL(parametricEQPeakFrequencyReceived(int)), this, SLOT(onMidFreqDial(int)));
    connect(mpStomp, SIGNAL(parametricEQHighGainReceived(double)), this, SLOT(onHighDial(double)));
    connect(mpStomp, SIGNAL(lowCutReceived(int)), this, SLOT(onLowCut(int)));
    connect(mpStomp, SIGNAL(highCutReceived(int)), this, SLOT(onHighCut(int)));
    connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));

    mpStomp->requestParametricEQLowGain();
    mpStomp->requestParametricEQPeakGain();
    mpStomp->requestParametricEQPeakFrequency();
    mpStomp->requestParametricEQHighGain();
    mpStomp->requestLowCut();
    mpStomp->requestHighCut();
    mpStomp->requestMix();
    mpStomp->requestDucking();
    mpStomp->requestVolume();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void MetalEqualizerFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(parametricEQLowGainReceived(double)), this, SLOT(onLowDial(double)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakGainReceived(double)), this, SLOT(onMiddleDial(double)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakFrequencyReceived(int)), this, SLOT(onMidFreqDial(int)));
    disconnect(mpStomp, SIGNAL(parametricEQHighGainReceived(double)), this, SLOT(onHighDial(double)));
    disconnect(mpStomp, SIGNAL(lowCutReceived(int)), this, SLOT(onLowCut(int)));
    disconnect(mpStomp, SIGNAL(highCutReceived(int)), this, SLOT(onHighCut(int)));
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  }
  mpStomp = nullptr;
}

QToasterLCD::Page MetalEqualizerFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page MetalEqualizerFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void MetalEqualizerFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
    ui->bigDials->setCurrentIndex((int) page);
    ui->smallDials->setCurrentIndex((int) page);
  }
}

void MetalEqualizerFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void MetalEqualizerFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void MetalEqualizerFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void MetalEqualizerFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void MetalEqualizerFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void MetalEqualizerFrame::on_pageDial_valueChanged(int valueIndex)
{
  ui->lcdDisplay->setCurrentPage((QToasterStompEditLCD::Page)valueIndex);
}

void MetalEqualizerFrame::on_lowDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQLowGain(value);
}

void MetalEqualizerFrame::on_middleDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakGain(value);
}

void MetalEqualizerFrame::on_midFreqDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakFrequency(value);
}

void MetalEqualizerFrame::on_highDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQHighGain(value);
}

void MetalEqualizerFrame::on_lowCutDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyLowCut(value);
}

void MetalEqualizerFrame::on_highCutDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyHighCut(value);
}

void MetalEqualizerFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void MetalEqualizerFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void MetalEqualizerFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void MetalEqualizerFrame::onLowDial(double value)
{
  ui->lowDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onMiddleDial(double value)
{
  ui->middleDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onMidFreqDial(int value)
{
  ui->midFreqDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onHighDial(double value)
{
  ui->highDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onLowCut(int value)
{
  ui->lowCutDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onHighCut(int value)
{
  ui->highCutDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void MetalEqualizerFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

