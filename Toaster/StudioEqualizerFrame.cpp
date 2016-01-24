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
#include "StudioEqualizerFrame.h"
#include "ui_StudioEqualizerFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

StudioEqualizerFrame::StudioEqualizerFrame(QWidget *parent)
  : QWidget(parent)
  ,ui(new Ui::StudioEqualizerFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  ui->pageDial->setValue(0);
  ui->lowCutDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui->highCutDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui->lowFreqDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui->mid1FreqDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui->mid2FreqDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui->highFreqDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui->mid1QFactorDial->setLookUpTable(LookUpTables::getQFactorValues());
  ui->mid2QFactorDial->setLookUpTable(LookUpTables::getQFactorValues());
}

StudioEqualizerFrame::~StudioEqualizerFrame()
{
  delete ui;
}
void StudioEqualizerFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(lowCutReceived(int)), this, SLOT(onLowCut(int)));
    connect(mpStomp, SIGNAL(highCutReceived(int)), this, SLOT(onHighCut(int)));
    connect(mpStomp, SIGNAL(parametricEQLowGainReceived(double)), this, SLOT(onLowGain(double)));
    connect(mpStomp, SIGNAL(parametricEQLowFrequencyReceived(int)), this, SLOT(onLowFreq(int)));
    connect(mpStomp, SIGNAL(parametricEQHighGainReceived(double)), this, SLOT(onHighGain(double)));
    connect(mpStomp, SIGNAL(parametricEQHighFrequencyReceived(int)), this, SLOT(onHighFreq(int)));
    connect(mpStomp, SIGNAL(parametricEQPeakGainReceived(double)), this, SLOT(onMid1Gain(double)));
    connect(mpStomp, SIGNAL(parametricEQPeakFrequencyReceived(int)), this, SLOT(onMid1Freq(int)));
    connect(mpStomp, SIGNAL(parametricEQPeakQFactorReceived(int)), this, SLOT(onMid1QFactor(int)));
    connect(mpStomp, SIGNAL(parametricEQPeakGain2Received(double)), this, SLOT(onMid2Gain(double)));
    connect(mpStomp, SIGNAL(parametricEQPeakFrequency2Received(int)), this, SLOT(onMid2Freq(int)));
    connect(mpStomp, SIGNAL(parametricEQPeakQFactor2Received(int)), this, SLOT(onMid2QFactor(int)));

    mpStomp->requestMix();
    mpStomp->requestDucking();
    mpStomp->requestVolume();
    mpStomp->requestLowCut();
    mpStomp->requestHighCut();
    mpStomp->requestParametricEQLowGain();
    mpStomp->requestParametricEQLowFrequency();
    mpStomp->requestParametricEQHighGain();
    mpStomp->requestParametricEQHighFrequency();
    mpStomp->requestParametricEQPeakGain();
    mpStomp->requestParametricEQPeakFrequency();
    mpStomp->requestParametricEQPeakQFactor();
    mpStomp->requestParametricEQPeakGain2();
    mpStomp->requestParametricEQPeakFrequency2();
    mpStomp->requestParametricEQPeakQFactor2();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void StudioEqualizerFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(lowCutReceived(int)), this, SLOT(onLowCut(int)));
    disconnect(mpStomp, SIGNAL(highCutReceived(int)), this, SLOT(onHighCut(int)));
    disconnect(mpStomp, SIGNAL(parametricEQLowGainReceived(double)), this, SLOT(onLowGain(double)));
    disconnect(mpStomp, SIGNAL(parametricEQLowFrequencyReceived(int)), this, SLOT(onLowFreq(int)));
    disconnect(mpStomp, SIGNAL(parametricEQHighGainReceived(double)), this, SLOT(onHighGain(double)));
    disconnect(mpStomp, SIGNAL(parametricEQHighFrequencyReceived(int)), this, SLOT(onHighFreq(int)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakGainReceived(double)), this, SLOT(onMid1Gain(double)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakFrequencyReceived(int)), this, SLOT(onMid1Freq(int)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakQFactorReceived(int)), this, SLOT(onMid1QFactor(int)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakGain2Received(double)), this, SLOT(onMid2Gain(double)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakFrequency2Received(int)), this, SLOT(onMid2Freq(int)));
    disconnect(mpStomp, SIGNAL(parametricEQPeakQFactor2Received(int)), this, SLOT(onMid2QFactor(int)));
  }
  mpStomp = nullptr;
}

void StudioEqualizerFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void StudioEqualizerFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void StudioEqualizerFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void StudioEqualizerFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void StudioEqualizerFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void StudioEqualizerFrame::on_pageDial_valueChanged(int valueIndex)
{
  ui->lcdDisplay->setCurrentPage((QToasterStompEditLCD::Page)valueIndex);
}

void StudioEqualizerFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void StudioEqualizerFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void StudioEqualizerFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void StudioEqualizerFrame::on_lowCutDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyLowCut(value);
}

void StudioEqualizerFrame::on_highCutDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyHighCut(value);
}

void StudioEqualizerFrame::on_lowGainDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQLowGain(value);
}

void StudioEqualizerFrame::on_lowFreqDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQLowFrequency(value);
}

void StudioEqualizerFrame::on_highGainDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQHighGain(value);
}

void StudioEqualizerFrame::on_highFreqDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQHighFrequency(value);
}
void StudioEqualizerFrame::on_mid1GainDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakGain(value);
}

void StudioEqualizerFrame::on_mid1FreqDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakFrequency(value);
}

void StudioEqualizerFrame::on_mid1QFactorDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakQFactor(value);
}

void StudioEqualizerFrame::on_mid2GainDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakGain2(value);
}

void StudioEqualizerFrame::on_mid2FreqDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakFrequency2(value);
}

void StudioEqualizerFrame::on_mid2QFactorDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyParametricEQPeakQFactor2(value);
}

void StudioEqualizerFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onLowCut(int value)
{
  ui->lowCutDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onHighCut(int value)
{
  ui->highCutDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onLowGain(double value)
{
  ui->lowGainDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onLowFreq(int value)
{
  ui->lowFreqDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onHighGain(double value)
{
  ui->highGainDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onHighFreq(int value)
{
  ui->highFreqDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid1Gain(double value)
{
  ui->mid1GainDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid1Freq(int value)
{
  ui->mid1FreqDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid1QFactor(int value)
{
  ui->mid1QFactorDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid2Gain(double value)
{
  ui->mid2GainDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid2Freq(int value)
{
  ui->mid2FreqDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid2QFactor(int value)
{
  ui->mid2QFactorDial->setValue(value);
  update();
}
