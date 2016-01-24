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
#include "ReverbFrame.h"
#include "ui_ReverbFrame.h"
#include "Reverb.h"

ReverbFrame::ReverbFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::ReverbFrame)
  , mpReverb(nullptr)
{
  ui->setupUi(this);
}

ReverbFrame::~ReverbFrame()
{
  delete ui;
}

void ReverbFrame::activate(QObject& stomp)
{
  mpReverb = qobject_cast<Reverb*>(&stomp);

  if(mpReverb != nullptr)
  {
    connect(mpReverb, SIGNAL(preDelayReceived(double)), this, SLOT(onPredaly(double)));
    connect(mpReverb, SIGNAL(bandwidthReceived(double)), this, SLOT(onBandwidth(double)));
    connect(mpReverb, SIGNAL(centerFrequencyReceived(double)), this, SLOT(onFrequency(double)));
    connect(mpReverb, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    connect(mpReverb, SIGNAL(delRevBalanceReceived(double)), this, SLOT(onDelRevBalance(double)));
    connect(mpReverb, SIGNAL(dampingReceived(double)), this, SLOT(onDamping(double)));
    connect(mpReverb, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));

    mpReverb->requestPreDelay();
    mpReverb->requestBandwidth();
    mpReverb->requestCenterFrequency();
    mpReverb->requestDucking();
    mpReverb->requestDelRevBalance();
    mpReverb->requestDamping();
    mpReverb->requestVolume();

    ui->lcdDisplay->setStompInstance("Reverb Effect");
    ui->lcdDisplay->setStompName(LookUpTables::reverbTypeName(mpReverb->getReverbType()));
  }
}

void ReverbFrame::deactivate()
{
  if(mpReverb != nullptr)
  {
    disconnect(mpReverb, SIGNAL(preDelayReceived(double)), this, SLOT(onPredaly(double)));
    disconnect(mpReverb, SIGNAL(bandwidthReceived(double)), this, SLOT(onBandwidth(double)));
    disconnect(mpReverb, SIGNAL(centerFrequencyReceived(double)), this, SLOT(onFrequency(double)));
    disconnect(mpReverb, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpReverb, SIGNAL(delRevBalanceReceived(double)), this, SLOT(onDelRevBalance(double)));
    disconnect(mpReverb, SIGNAL(dampingReceived(double)), this, SLOT(onDamping(double)));
    disconnect(mpReverb, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
  }
  mpReverb = nullptr;
}

void ReverbFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void ReverbFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void ReverbFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void ReverbFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void ReverbFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
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
  ui->predelayDial->setValue(value);
  update();
}

void ReverbFrame::onBandwidth(double value)
{
  ui->bandwidthDial->setValue(value);
  update();
}

void ReverbFrame::onFrequency(double value)
{
  ui->frequencyDial->setValue(value);
  update();
}

void ReverbFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void ReverbFrame::onDelRevBalance(double value)
{
  ui->delRevBalanceDial->setValue(value);
  update();
}

void ReverbFrame::onDamping(double value)
{
  ui->dampingDial->setValue(value);
  update();
}

void ReverbFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}
