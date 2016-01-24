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
#include "AnalogOctaverFrame.h"
#include "ui_AnalogOctaverFrame.h"
#include "Stomp.h"

AnalogOctaverFrame::AnalogOctaverFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::AnalogOctaverFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
}

AnalogOctaverFrame::~AnalogOctaverFrame()
{
  delete ui;
}
void AnalogOctaverFrame::activate(QObject& stomp)
{
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    connect(mpStomp, SIGNAL(voiceMixReceived(double)), this, SLOT(onVoiceMix(double)));
    connect(mpStomp, SIGNAL(IntensityReceived(double)), this, SLOT(onMix(double)));
    connect(mpStomp, SIGNAL(modulationCrossoverReceived(double)), this, SLOT(onLowCut(double)));

    mpStomp->requestVolume();
    mpStomp->requestDucking();
    mpStomp->requestVoiceMix();
    mpStomp->requestIntensity();
    mpStomp->requestModulationCrossover();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void AnalogOctaverFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpStomp, SIGNAL(voiceMixReceived(double)), this, SLOT(onVoiceMix(double)));
    disconnect(mpStomp, SIGNAL(IntensityReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(modulationCrossoverReceived(double)), this, SLOT(onLowCut(double)));
  }
  mpStomp = nullptr;
}

void AnalogOctaverFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void AnalogOctaverFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void AnalogOctaverFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void AnalogOctaverFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void AnalogOctaverFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void AnalogOctaverFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void AnalogOctaverFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void AnalogOctaverFrame::on_voiceMixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVoiceMix(value);
}

void AnalogOctaverFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyIntensity(value);
}

void AnalogOctaverFrame::on_lowCutDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyModulationCrossover(value);
}

void AnalogOctaverFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}

void AnalogOctaverFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void AnalogOctaverFrame::onVoiceMix(double value)
{
  ui->voiceMixDial->setValue(value);
  update();
}

void AnalogOctaverFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void AnalogOctaverFrame::onLowCut(double value)
{
  ui->lowCutDial->setValue(value);
  update();
}
