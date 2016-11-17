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
#include "Stomp.h"
#include "Settings.h"
#include "LookUpTables.h"

AnalogOctaverFrame::AnalogOctaverFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);

  if(Settings::get().getKPAOSVersion() >= 0x04000000)
  {
    ui.lcdDisplay->setValue5Title("Voice Balance");
  }
  else
  {
    ui.lcdDisplay->setValue5Title("Voice Mix");
  }
}

AnalogOctaverFrame::~AnalogOctaverFrame()
{
}

void AnalogOctaverFrame::activate(QObject& stomp)
{
  show();
  mpStomp = qobject_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, &Stomp::volumeReceived, this, &AnalogOctaverFrame::onVolume);
    connect(mpStomp, &Stomp::duckingReceived, this, &AnalogOctaverFrame::onDucking);
    connect(mpStomp, &Stomp::voiceMixReceived, this, &AnalogOctaverFrame::onVoiceMix);
    connect(mpStomp, &Stomp::intensityReceived, this, &AnalogOctaverFrame::onMix);
    connect(mpStomp, static_cast<void (Stomp::*)(double)>(&Stomp::modulationCrossoverReceived), this, &AnalogOctaverFrame::onLowCut);
    connect(mpStomp, &Stomp::stereoReceived, this, &AnalogOctaverFrame::onStereo);

    ui.lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui.lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));

    mpStomp->requestVolume();
    mpStomp->requestDucking();
    mpStomp->requestVoiceMix();
    mpStomp->requestIntensity();
    mpStomp->requestModulationCrossover();

    StompInstance si = mpStomp->getInstance();
    if(si != StompX && si != StompMod && si != StompDelay)
    {
      ui.lcdDisplay->setValue8("");
      ui.lcdDisplay->setValue8Title("");
      ui.stereoDial->setIsActive(false);
    }
    else
    {
      ui.lcdDisplay->setValue8Title("Stereo");
      ui.stereoDial->setIsActive(true);
      mpStomp->requestStereo();
    }
  }
}

void AnalogOctaverFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, &Stomp::volumeReceived, this, &AnalogOctaverFrame::onVolume);
    disconnect(mpStomp, &Stomp::duckingReceived, this, &AnalogOctaverFrame::onDucking);
    disconnect(mpStomp, &Stomp::voiceMixReceived, this, &AnalogOctaverFrame::onVoiceMix);
    disconnect(mpStomp, &Stomp::intensityReceived, this, &AnalogOctaverFrame::onMix);
    disconnect(mpStomp, static_cast<void (Stomp::*)(double)>(&Stomp::modulationCrossoverReceived), this, &AnalogOctaverFrame::onLowCut);
    disconnect(mpStomp, &Stomp::stereoReceived, this, &AnalogOctaverFrame::onStereo);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page AnalogOctaverFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page AnalogOctaverFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void AnalogOctaverFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
  }
}

void AnalogOctaverFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void AnalogOctaverFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void AnalogOctaverFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void AnalogOctaverFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void AnalogOctaverFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
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

void AnalogOctaverFrame::on_stereoDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyStereo(value);
}

void AnalogOctaverFrame::onVolume(double value)
{
  ui.volumeDial->setValue(value);
  update();
}

void AnalogOctaverFrame::onDucking(double value)
{
  ui.duckingDial->setValue(value);
  update();
}

void AnalogOctaverFrame::onVoiceMix(double value)
{
  ui.voiceMixDial->setValue(value);
  update();
}

void AnalogOctaverFrame::onMix(double value)
{
  ui.mixDial->setValue(value);
  update();
}

void AnalogOctaverFrame::onLowCut(double value)
{
  ui.lowCutDial->setValue(value);
  update();
}

void AnalogOctaverFrame::onStereo(double value)
{
  ui.stereoDial->setValue(value);
  update();
}
