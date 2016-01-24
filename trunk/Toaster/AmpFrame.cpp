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
#include "AmpFrame.h"
#include "ui_AmpFrame.h"

AmpFrame::AmpFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::AmpFrame)
  , mpAmp(nullptr)
{
  ui->setupUi(this);
}

AmpFrame::~AmpFrame()
{
  delete ui;
}

void AmpFrame::activate(QObject& amp)
{
  mpAmp = qobject_cast<Amp*>(&amp);

  if(mpAmp != nullptr)
  {
    connect(mpAmp, &Amp::definitionReceived, this, &AmpFrame::onDefinition);
    connect(mpAmp, &Amp::powerSaggingReceived, this, &AmpFrame::onPowerSagging);
    connect(mpAmp, &Amp::pickReceived, this, &AmpFrame::onPick);
    connect(mpAmp, &Amp::compressorReceived, this, &AmpFrame::onCompressor);
    connect(mpAmp, &Amp::clarityReceived, this, &AmpFrame::onClarity);
    connect(mpAmp, &Amp::tubeShapeReceived, this, &AmpFrame::onTubeShape);
    connect(mpAmp, &Amp::tubeBiasReceived, this, &AmpFrame::onTubeBias);
    connect(mpAmp, &Amp::directMixReceived, this, &AmpFrame::onDirectMix);

    mpAmp->requestDefinition();
    mpAmp->requestPowerSagging();
    mpAmp->requestPick();
    mpAmp->requestCompressor();
    mpAmp->requestClarity();
    mpAmp->requestTubeShape();
    mpAmp->requestTubeBias();
    mpAmp->requestDirectMix();
  }
}

void AmpFrame::deactivate()
{
  if(mpAmp != nullptr)
  {
    disconnect(mpAmp, &Amp::definitionReceived, this, &AmpFrame::onDefinition);
    disconnect(mpAmp, &Amp::powerSaggingReceived, this, &AmpFrame::onPowerSagging);
    disconnect(mpAmp, &Amp::pickReceived, this, &AmpFrame::onPick);
    disconnect(mpAmp, &Amp::compressorReceived, this, &AmpFrame::onCompressor);
    disconnect(mpAmp, &Amp::clarityReceived, this, &AmpFrame::onClarity);
    disconnect(mpAmp, &Amp::tubeShapeReceived, this, &AmpFrame::onTubeShape);
    disconnect(mpAmp, &Amp::tubeBiasReceived, this, &AmpFrame::onTubeBias);
    disconnect(mpAmp, &Amp::directMixReceived, this, &AmpFrame::onDirectMix);
    mpAmp = nullptr;
  }
}

void AmpFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void AmpFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void AmpFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void AmpFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void AmpFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}


void AmpFrame::on_definitionDial_valueChanged(double value)
{
  if(mpAmp != nullptr)
    mpAmp->applyDefinition(value);
}

void AmpFrame::on_powerSaggingDial_valueChanged(double value)
{
  if(mpAmp != nullptr)
    mpAmp->applyPowerSagging(value);
}

void AmpFrame::on_pickDial_valueChanged(double value)
{
  if(mpAmp != nullptr)
    mpAmp->applyPick(value);
}

void AmpFrame::on_compressorDial_valueChanged(double value)
{
  if(mpAmp != nullptr)
    mpAmp->applyCompressor(value);
}

void AmpFrame::on_clarityDial_valueChanged(double value)
{
  if(mpAmp != nullptr)
    mpAmp->applyClarity(value);
}

void AmpFrame::on_tubeShapeDial_valueChanged(double value)
{
  if(mpAmp != nullptr)
    mpAmp->applyTubeShape(value);
}

void AmpFrame::on_tubeBiasDial_valueChanged(double value)
{
  if(mpAmp != nullptr)
    mpAmp->applyTubeBias(value);
}

void AmpFrame::on_directMixDial_valueChanged(double value)
{
  if(mpAmp != nullptr)
    mpAmp->applyDirectMix(value);
}

void AmpFrame::onDefinition(double value)
{
  ui->definitionDial->setValue(value);
}

void AmpFrame::onPowerSagging(double value)
{
  ui->powerSaggingDial->setValue(value);
}

void AmpFrame::onPick(double value)
{
  ui->pickDial->setValue(value);
}

void AmpFrame::onCompressor(double value)
{
  ui->compressorDial->setValue(value);
}

void AmpFrame::onClarity(double value)
{
  ui->clarityDial->setValue(value);
}

void AmpFrame::onTubeShape(double value)
{
  ui->tubeShapeDial->setValue(value);
}

void AmpFrame::onTubeBias(double value)
{
  ui->tubeBiasDial->setValue(value);
}

void AmpFrame::onDirectMix(double value)
{
  ui->directMixDial->setValue(value);
}

