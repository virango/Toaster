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
#include "GraphicEqualizerFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

GraphicEqualizerFrame::GraphicEqualizerFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);
  ui.lowCutDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui.highCutDial->setLookUpTable(LookUpTables::getFrequencyValues());
}

GraphicEqualizerFrame::~GraphicEqualizerFrame()
{
}

void GraphicEqualizerFrame::activate(QObject& stomp)
{
  show();
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::mixReceived, this, &GraphicEqualizerFrame::onMix);
    connect(mpStomp, &Stomp::duckingReceived, this, &GraphicEqualizerFrame::onDucking);
    connect(mpStomp, &Stomp::volumeReceived, this, &GraphicEqualizerFrame::onVolume);
    connect(mpStomp, &Stomp::graphicEQBand1Received, this, &GraphicEqualizerFrame::onBand1);
    connect(mpStomp, &Stomp::graphicEQBand2Received, this, &GraphicEqualizerFrame::onBand2);
    connect(mpStomp, &Stomp::graphicEQBand3Received, this, &GraphicEqualizerFrame::onBand3);
    connect(mpStomp, &Stomp::graphicEQBand4Received, this, &GraphicEqualizerFrame::onBand4);
    connect(mpStomp, &Stomp::graphicEQBand5Received, this, &GraphicEqualizerFrame::onBand5);
    connect(mpStomp, &Stomp::graphicEQBand6Received, this, &GraphicEqualizerFrame::onBand6);
    connect(mpStomp, &Stomp::graphicEQBand7Received, this, &GraphicEqualizerFrame::onBand7);
    connect(mpStomp, &Stomp::graphicEQBand8Received, this, &GraphicEqualizerFrame::onBand8);
    connect(mpStomp, &Stomp::lowCutReceived, this, &GraphicEqualizerFrame::onLowCut);
    connect(mpStomp, &Stomp::highCutReceived, this, &GraphicEqualizerFrame::onHighCut);

    mpStomp->requestMix();
    mpStomp->requestDucking();
    mpStomp->requestVolume();
    mpStomp->requestGraphicEQBand1();
    mpStomp->requestGraphicEQBand2();
    mpStomp->requestGraphicEQBand3();
    mpStomp->requestGraphicEQBand4();
    mpStomp->requestGraphicEQBand5();
    mpStomp->requestGraphicEQBand6();
    mpStomp->requestGraphicEQBand7();
    mpStomp->requestGraphicEQBand8();
    mpStomp->requestLowCut();
    mpStomp->requestHighCut();

    ui.lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui.lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}
void GraphicEqualizerFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::mixReceived, this, &GraphicEqualizerFrame::onMix);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &GraphicEqualizerFrame::onDucking);
    disconnect(mpStomp, &Stomp::volumeReceived, this, &GraphicEqualizerFrame::onVolume);
    disconnect(mpStomp, &Stomp::graphicEQBand1Received, this, &GraphicEqualizerFrame::onBand1);
    disconnect(mpStomp, &Stomp::graphicEQBand2Received, this, &GraphicEqualizerFrame::onBand2);
    disconnect(mpStomp, &Stomp::graphicEQBand3Received, this, &GraphicEqualizerFrame::onBand3);
    disconnect(mpStomp, &Stomp::graphicEQBand4Received, this, &GraphicEqualizerFrame::onBand4);
    disconnect(mpStomp, &Stomp::graphicEQBand5Received, this, &GraphicEqualizerFrame::onBand5);
    disconnect(mpStomp, &Stomp::graphicEQBand6Received, this, &GraphicEqualizerFrame::onBand6);
    disconnect(mpStomp, &Stomp::graphicEQBand7Received, this, &GraphicEqualizerFrame::onBand7);
    disconnect(mpStomp, &Stomp::graphicEQBand8Received, this, &GraphicEqualizerFrame::onBand8);
    disconnect(mpStomp, &Stomp::lowCutReceived, this, &GraphicEqualizerFrame::onLowCut);
    disconnect(mpStomp, &Stomp::highCutReceived, this, &GraphicEqualizerFrame::onHighCut);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page GraphicEqualizerFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page GraphicEqualizerFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void GraphicEqualizerFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
    ui.bigDials->setCurrentIndex((int) page);
    ui.smallDials->setCurrentIndex((int) page);
  }
}

void GraphicEqualizerFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void GraphicEqualizerFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void GraphicEqualizerFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void GraphicEqualizerFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void GraphicEqualizerFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
}

void GraphicEqualizerFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void GraphicEqualizerFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void GraphicEqualizerFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void GraphicEqualizerFrame::on_band1Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand1(value);
}

void GraphicEqualizerFrame::on_band2Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand2(value);
}

void GraphicEqualizerFrame::on_band3Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand3(value);
}

void GraphicEqualizerFrame::on_band4Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand4(value);
}

void GraphicEqualizerFrame::on_band5Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand5(value);
}

void GraphicEqualizerFrame::on_band6Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand6(value);
}

void GraphicEqualizerFrame::on_band7Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand7(value);
}

void GraphicEqualizerFrame::on_band8Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand8(value);
}

void GraphicEqualizerFrame::on_lowCutDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyLowCut(value);
}

void GraphicEqualizerFrame::on_highCutDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyHighCut(value);
}


void GraphicEqualizerFrame::onMix(double value)
{
  ui.mixDial->setValue(value);
  update();
}

void GraphicEqualizerFrame::onDucking(double value)
{
  ui.duckingDial->setValue(value);
  update();
}

void GraphicEqualizerFrame::onVolume(double value)
{
  ui.volumeDial->setValue(value);
  update();
}


void GraphicEqualizerFrame::onBand1(double value)
{
  ui.band1Dial->setValue(value);
  ui.lcdDisplay->setEqBand1Value(value);
  update();
}

void GraphicEqualizerFrame::onBand2(double value)
{
  ui.band2Dial->setValue(value);
  ui.lcdDisplay->setEqBand2Value(value);
  update();
}

void GraphicEqualizerFrame::onBand3(double value)
{
  ui.band3Dial->setValue(value);
  ui.lcdDisplay->setEqBand3Value(value);
  update();
}

void GraphicEqualizerFrame::onBand4(double value)
{
  ui.band4Dial->setValue(value);
  ui.lcdDisplay->setEqBand4Value(value);
  update();
}

void GraphicEqualizerFrame::onBand5(double value)
{
  ui.band5Dial->setValue(value);
  ui.lcdDisplay->setEqBand5Value(value);
  update();
}

void GraphicEqualizerFrame::onBand6(double value)
{
  ui.band6Dial->setValue(value);
  ui.lcdDisplay->setEqBand6Value(value);
  update();
}

void GraphicEqualizerFrame::onBand7(double value)
{
  ui.band7Dial->setValue(value);
  ui.lcdDisplay->setEqBand7Value(value);
  update();
}

void GraphicEqualizerFrame::onBand8(double value)
{
  ui.band8Dial->setValue(value);
  ui.lcdDisplay->setEqBand8Value(value);
  update();
}

void GraphicEqualizerFrame::onLowCut(int value)
{
  ui.lowCutDial->setValue(value);
  update();
}

void GraphicEqualizerFrame::onHighCut(int value)
{
  ui.highCutDial->setValue(value);
  update();
}


