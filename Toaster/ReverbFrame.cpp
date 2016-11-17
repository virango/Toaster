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
#include <QLayout>
#include "ReverbFrame.h"
#include "Reverb.h"
#include "LookUpTables.h"

ReverbFrame::ReverbFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);
}

ReverbFrame::~ReverbFrame()
{
}

void ReverbFrame::activate(QObject& stomp)
{
  show();
  mpReverb = qobject_cast<Reverb*>(&stomp);

  if(mpReverb != nullptr)
  {
    connect(mpReverb, &Reverb::preDelayReceived, this, &ReverbFrame::onPredaly);
    connect(mpReverb, &Reverb::bandwidthReceived, this, &ReverbFrame::onBandwidth);
    connect(mpReverb, &Reverb::centerFrequencyReceived, this, &ReverbFrame::onFrequency);
    connect(mpReverb, &Reverb::duckingReceived, this, &ReverbFrame::onDucking);
    connect(mpReverb, &Reverb::delRevBalanceReceived, this, &ReverbFrame::onDelRevBalance);
    connect(mpReverb, &Reverb::dampingReceived, this, &ReverbFrame::onDamping);
    connect(mpReverb, &Reverb::volumeReceived, this, &ReverbFrame::onVolume);

    mpReverb->requestPreDelay();
    mpReverb->requestBandwidth();
    mpReverb->requestCenterFrequency();
    mpReverb->requestDucking();
    mpReverb->requestDelRevBalance();
    mpReverb->requestDamping();
    mpReverb->requestVolume();

    ui.lcdDisplay->setStompInstance("Reverb module");
    ui.lcdDisplay->setStompName(LookUpTables::reverbTypeName(mpReverb->getReverbType()));
  }
}

void ReverbFrame::deactivate()
{
  if(mpReverb != nullptr)
  {
    disconnect(mpReverb, &Reverb::preDelayReceived, this, &ReverbFrame::onPredaly);
    disconnect(mpReverb, &Reverb::bandwidthReceived, this, &ReverbFrame::onBandwidth);
    disconnect(mpReverb, &Reverb::centerFrequencyReceived, this, &ReverbFrame::onFrequency);
    disconnect(mpReverb, &Reverb::duckingReceived, this, &ReverbFrame::onDucking);
    disconnect(mpReverb, &Reverb::delRevBalanceReceived, this, &ReverbFrame::onDelRevBalance);
    disconnect(mpReverb, &Reverb::dampingReceived, this, &ReverbFrame::onDamping);
    disconnect(mpReverb, &Reverb::volumeReceived, this, &ReverbFrame::onVolume);
    mpReverb = nullptr;
  }
}

QToasterLCD::Page ReverbFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page ReverbFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void ReverbFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
  }
}

void ReverbFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void ReverbFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void ReverbFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void ReverbFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void ReverbFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
}

void ReverbFrame::on_predelayDial_valueChanged(double value)
{
  if(mpReverb != nullptr)
    mpReverb->applyPreDelay(value);
}

void ReverbFrame::on_bandwidthDial_valueChanged(double value)
{
  if(mpReverb != nullptr)
    mpReverb->applyBandwidth(value);
}

void ReverbFrame::on_frequencyDial_valueChanged(double value)
{
  if(mpReverb != nullptr)
    mpReverb->applyCenterFrequency(value);
}

void ReverbFrame::on_duckingDial_valueChanged(double value)
{
  if(mpReverb != nullptr)
    mpReverb->applyDucking(value);
}

void ReverbFrame::on_delRevBalanceDial_valueChanged(double value)
{
  if(mpReverb != nullptr)
    mpReverb->applyDelRevBalance(value);
}

void ReverbFrame::on_dampingDial_valueChanged(double value)
{
  if(mpReverb != nullptr)
    mpReverb->applyDamping(value);
}

void ReverbFrame::on_volumeDial_valueChanged(double value)
{
  if(mpReverb != nullptr)
    mpReverb->applyVolume(value);
}

void ReverbFrame::onPredaly(double value)
{
  ui.predelayDial->setValue(value);
  update();
}

void ReverbFrame::onBandwidth(double value)
{
  ui.bandwidthDial->setValue(value);
  update();
}

void ReverbFrame::onFrequency(double value)
{
  ui.frequencyDial->setValue(value);
  update();
}

void ReverbFrame::onDucking(double value)
{
  ui.duckingDial->setValue(value);
  update();
}

void ReverbFrame::onDelRevBalance(double value)
{
  ui.delRevBalanceDial->setValue(value);
  update();
}

void ReverbFrame::onDamping(double value)
{
  ui.dampingDial->setValue(value);
  update();
}

void ReverbFrame::onVolume(double value)
{
  ui.volumeDial->setValue(value);
  update();
}
