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
#include "Stomp.h"
#include "LookUpTables.h"

StudioEqualizerFrame::StudioEqualizerFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);
  ui.lowCutDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui.highCutDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui.lowFreqDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui.mid1FreqDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui.mid2FreqDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui.highFreqDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui.mid1QFactorDial->setLookUpTable(LookUpTables::getQFactorValues());
  ui.mid2QFactorDial->setLookUpTable(LookUpTables::getQFactorValues());
}

StudioEqualizerFrame::~StudioEqualizerFrame()
{
}

void StudioEqualizerFrame::activate(QObject& stomp)
{
  show();
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::mixReceived, this, &StudioEqualizerFrame::onMix);
    connect(mpStomp, &Stomp::duckingReceived, this, &StudioEqualizerFrame::onDucking);
    connect(mpStomp, &Stomp::volumeReceived, this, &StudioEqualizerFrame::onVolume);
    connect(mpStomp, &Stomp::lowCutReceived, this, &StudioEqualizerFrame::onLowCut);
    connect(mpStomp, &Stomp::highCutReceived, this, &StudioEqualizerFrame::onHighCut);
    connect(mpStomp, &Stomp::parametricEQLowGainReceived, this, &StudioEqualizerFrame::onLowGain);
    connect(mpStomp, &Stomp::parametricEQLowFrequencyReceived, this, &StudioEqualizerFrame::onLowFreq);
    connect(mpStomp, &Stomp::parametricEQHighGainReceived, this, &StudioEqualizerFrame::onHighGain);
    connect(mpStomp, &Stomp::parametricEQHighFrequencyReceived, this, &StudioEqualizerFrame::onHighFreq);
    connect(mpStomp, &Stomp::parametricEQPeakGainReceived, this, &StudioEqualizerFrame::onMid1Gain);
    connect(mpStomp, &Stomp::parametricEQPeakFrequencyReceived, this, &StudioEqualizerFrame::onMid1Freq);
    connect(mpStomp, &Stomp::parametricEQPeakQFactorReceived, this, &StudioEqualizerFrame::onMid1QFactor);
    connect(mpStomp, &Stomp::parametricEQPeakGain2Received, this, &StudioEqualizerFrame::onMid2Gain);
    connect(mpStomp, &Stomp::parametricEQPeakFrequency2Received, this, &StudioEqualizerFrame::onMid2Freq);
    connect(mpStomp, &Stomp::parametricEQPeakQFactor2Received, this, &StudioEqualizerFrame::onMid2QFactor);

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

    ui.lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui.lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void StudioEqualizerFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::mixReceived, this, &StudioEqualizerFrame::onMix);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &StudioEqualizerFrame::onDucking);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &StudioEqualizerFrame::onVolume);
    disconnect(mpStomp, &Stomp::lowCutReceived, this, &StudioEqualizerFrame::onLowCut);
    disconnect(mpStomp, &Stomp::highCutReceived, this, &StudioEqualizerFrame::onHighCut);
    disconnect(mpStomp, &Stomp::parametricEQLowGainReceived, this, &StudioEqualizerFrame::onLowGain);
    disconnect(mpStomp, &Stomp::parametricEQLowFrequencyReceived, this, &StudioEqualizerFrame::onLowFreq);
    disconnect(mpStomp, &Stomp::parametricEQHighGainReceived, this, &StudioEqualizerFrame::onHighGain);
    disconnect(mpStomp, &Stomp::parametricEQHighFrequencyReceived, this, &StudioEqualizerFrame::onHighFreq);
    disconnect(mpStomp, &Stomp::parametricEQPeakGainReceived, this, &StudioEqualizerFrame::onMid1Gain);
    disconnect(mpStomp, &Stomp::parametricEQPeakFrequencyReceived, this, &StudioEqualizerFrame::onMid1Freq);
    disconnect(mpStomp, &Stomp::parametricEQPeakQFactorReceived, this, &StudioEqualizerFrame::onMid1QFactor);
    disconnect(mpStomp, &Stomp::parametricEQPeakGain2Received, this, &StudioEqualizerFrame::onMid2Gain);
    disconnect(mpStomp, &Stomp::parametricEQPeakFrequency2Received, this, &StudioEqualizerFrame::onMid2Freq);
    disconnect(mpStomp, &Stomp::parametricEQPeakQFactor2Received, this, &StudioEqualizerFrame::onMid2QFactor);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page StudioEqualizerFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page StudioEqualizerFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void StudioEqualizerFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
    ui.bigDials->setCurrentIndex((int) page);
    ui.smallDials->setCurrentIndex((int) page);
  }
}

void StudioEqualizerFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void StudioEqualizerFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void StudioEqualizerFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void StudioEqualizerFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void StudioEqualizerFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
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
  ui.mixDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onDucking(double value)
{
  ui.duckingDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onVolume(double value)
{
  ui.volumeDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onLowCut(int value)
{
  ui.lowCutDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onHighCut(int value)
{
  ui.highCutDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onLowGain(double value)
{
  ui.lowGainDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onLowFreq(int value)
{
  ui.lowFreqDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onHighGain(double value)
{
  ui.highGainDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onHighFreq(int value)
{
  ui.highFreqDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid1Gain(double value)
{
  ui.mid1GainDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid1Freq(int value)
{
  ui.mid1FreqDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid1QFactor(int value)
{
  ui.mid1QFactorDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid2Gain(double value)
{
  ui.mid2GainDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid2Freq(int value)
{
  ui.mid2FreqDial->setValue(value);
  update();
}

void StudioEqualizerFrame::onMid2QFactor(int value)
{
  ui.mid2QFactorDial->setValue(value);
  update();
}
