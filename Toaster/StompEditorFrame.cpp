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
#include "StompEditorFrame.h"
#include "ui_StompEditorFrame.h"
#include "Stomp.h"
#include "StompEditorPage.h"
#include "Input.h"

StompEditorFrame::StompEditorFrame(QWidget *parent)
  : QStackedWidget(parent)
  , ui(new Ui::StompEditorFrame)
  , mpStompA(nullptr)
  , mpStompB(nullptr)
  , mpStompC(nullptr)
  , mpStompD(nullptr)
  , mpStompX(nullptr)
  , mpStompMod(nullptr)
  , mpDelay(nullptr)
  , mpReverb(nullptr)
  , mpProfile(nullptr)
  , mpActiveStomp(nullptr)
  , mActiveStompType(-1)
  , mpActivePage(nullptr)
{
  ui->setupUi(this);
}

StompEditorFrame::~StompEditorFrame()
{
  delete ui;
}

void StompEditorFrame::init(Stomp& stompA,
                            Stomp& stompB,
                            Stomp& stompC,
                            Stomp& stompD,
                            Stomp& stompX,
                            Stomp& stompMod,
                            Delay& delay,
                            Reverb& reverb,
                            Profile& profile)
{
  mpStompA = &stompA;
  mpStompB = &stompB;
  mpStompC = &stompC;
  mpStompD = &stompD;
  mpStompX = &stompX;
  mpStompMod = &stompMod;
  mpDelay = &delay;
  mpReverb = &reverb;
  mpProfile = &profile;

  // stomps
  connect(mpStompA, SIGNAL(onOffReceived(bool)), this, SLOT(onStompAOnOff(bool)));
  connect(mpStompB, SIGNAL(onOffReceived(bool)), this, SLOT(onStompBOnOff(bool)));
  connect(mpStompC, SIGNAL(onOffReceived(bool)), this, SLOT(onStompCOnOff(bool)));
  connect(mpStompD, SIGNAL(onOffReceived(bool)), this, SLOT(onStompDOnOff(bool)));
  connect(mpStompX, SIGNAL(onOffReceived(bool)), this, SLOT(onStompXOnOff(bool)));
  connect(mpStompMod, SIGNAL(onOffReceived(bool)), this, SLOT(onStompModOnOff(bool)));
  connect(mpStompA, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompAType(::FXType)));
  connect(mpStompB, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompBType(::FXType)));
  connect(mpStompC, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompCType(::FXType)));
  connect(mpStompD, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompDType(::FXType)));
  connect(mpStompX, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompXType(::FXType)));
  connect(mpStompMod, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompModType(::FXType)));
  // delay
  connect(mpDelay, SIGNAL(onOffCutsTailReceived(bool)), this, SLOT(onDelayOnOff(bool)));
  // reverb
  connect(mpReverb, SIGNAL(onOffCutsTailReceived(bool)), this, SLOT(onReverbOnOff(bool)));
  // profile
  connect(mpProfile, SIGNAL(ampNameReceived(const QString&)), this, SLOT(onAmpName(const QString&)));
}


void StompEditorFrame::activate(QObject& stomp)
{
  deactivate();
  mpActiveStomp = &stomp;

  if(mpActiveStomp != nullptr)
  {
    Stomp* pActiveStomp = qobject_cast<Stomp*>(mpActiveStomp);
    Delay* pDelay = qobject_cast<Delay*>(mpActiveStomp);
    Reverb* pReverb = qobject_cast<Reverb*>(mpActiveStomp);
    Amp* pAmp = qobject_cast<Amp*>(mpActiveStomp);
    Cab* pCab = qobject_cast<Cab*>(mpActiveStomp);
    Global* pGlobal = qobject_cast<Global*>(mpActiveStomp);
    Input* pInput = qobject_cast<Input*>(mpActiveStomp);
    if(pActiveStomp != nullptr)
    {
      connect(pActiveStomp, SIGNAL(typeReceived(::FXType)), this, SLOT(onActiveStompType(::FXType)));
      pActiveStomp->requestType();
    }
    else if(pDelay != nullptr)
    {
      connect(pDelay, SIGNAL(typeReceived(::DelayType)), this, SLOT(onDelayType(::DelayType)));
      pDelay->requestType();
    }
    else if(pReverb != nullptr)
    {
      connect(pReverb, SIGNAL(typeReceived(::ReverbType)), this, SLOT(onReverbType(::ReverbType)));
      pReverb->requestType();
    }
    else if (pAmp != nullptr)
    {
      activatePage(ui->amp, indexOf(ui->amp));
    }
    else if(pCab != nullptr)
    {
      activatePage(ui->cab, indexOf(ui->cab));
    }
    else if(pGlobal != nullptr)
    {
      activatePage(ui->output, indexOf(ui->output));
    }
    else if(pInput != nullptr)
    {
      activatePage(ui->input, indexOf(ui->input));
    }
  }

  requestValues();
}

void StompEditorFrame::deactivate()
{
  if(mpActiveStomp != nullptr)
  {
    Stomp* pActiveStomp = qobject_cast<Stomp*>(mpActiveStomp);
    Delay* pDelay = qobject_cast<Delay*>(mpActiveStomp);
    Reverb* pReverb = qobject_cast<Reverb*>(mpActiveStomp);

    if(pActiveStomp != nullptr)
      disconnect(mpActiveStomp, SIGNAL(typeReceived(::FXType)), this, SLOT(onActiveStompType(::FXType)));
    else if(pDelay != nullptr)
      disconnect(pDelay, SIGNAL(typeReceived(::DelayType)), this, SLOT(onDelayType(::DelayType)));
    else if(pReverb != nullptr)
      connect(pReverb, SIGNAL(typeReceived(::ReverbType)), this, SLOT(onReverbType(::ReverbType)));

    mpActiveStomp = nullptr;
  }

  mActiveStompType = -1;

  if(mpActivePage != nullptr)
  {
    mpActivePage->deactivate();
    mpActivePage = nullptr;
    emit editorPageChanged(mpActivePage);
  }
}

void StompEditorFrame::onActiveStompType(FXType fxType)
{
  Stomp* pActiveStomp = nullptr;
  if(mpActivePage != nullptr)
  {
    if(fxType != mActiveStompType)
    {
      mpActivePage->deactivate();
      mpActivePage = nullptr;
      emit editorPageChanged(mpActivePage);
    }
  }

  int index = 0;

  pActiveStomp = qobject_cast<Stomp*>(mpActiveStomp);

  if(pActiveStomp != nullptr)
  {
    switch(fxType)
    {
      case WahWah:
      case WahHighPass:
      case WahLowPass:
      case WahVowelFilter:
      case WahFlanger:
      case WahRateReducer:
        mpActivePage = ui->wahWah;
        index = indexOf(ui->wahWah);
        break;
      case WahRingModulator:
      case WahFrequencyShifter:
        mpActivePage = ui->wahNoPeak;
        index = indexOf(ui->wahNoPeak);
        break;
      case WahFormantShifter:
        mpActivePage = ui->wahFormantShift;
        index = indexOf(ui->wahFormantShift);
        break;
      case WahPhaser:
        mpActivePage = ui->wahPhaser;
        index = indexOf(ui->wahPhaser);
        break;
      case PureBooster:
        mpActivePage = ui->pureBooster;
        index = indexOf(ui->pureBooster);
        break;
      case SoftShaper:
      case HardShaper:
      case WaveShaper:
      case PlusDS:
      case FuzzDS:
        mpActivePage = ui->driveDS;
        index = indexOf(ui->driveDS);
        break;
      case BitShaper:
      case GreenScream:
      case OneDS:
      case Muffin:
      case MouseDS:
        mpActivePage = ui->driveAndToneDS;
        index = indexOf(ui->driveAndToneDS);
        break;
      case RectiShaper:
        mpActivePage = ui->rectiShaper;
        index = indexOf(ui->rectiShaper);
        break;
      case TrebleBooster:
      case LeadBooster:
        mpActivePage = ui->toneAndDuckingDS;
        index = indexOf(ui->toneAndDuckingDS);
        break;
      case WahPedalBooster:
        mpActivePage = ui->wahPedalBooster;
        index = indexOf(ui->wahPedalBooster);
        break;
      case MetalDS:
        mpActivePage = ui->metalDS;
        index = indexOf(ui->metalDS);
        break;
      case GraphicEqualizer:
        mpActivePage = ui->graphicEqualizer;
        index = indexOf(ui->graphicEqualizer);
        break;
      case StudioEqualizer:
        mpActivePage = ui->studioEqualizer;
        index = indexOf(ui->studioEqualizer);
        break;
      case MetalEqualizer:
        mpActivePage = ui->metalEqualizer;
        index = indexOf(ui->metalEqualizer);
        break;
      case StereoWeidener:
        mpActivePage = ui->stereoWeidener;
        index = indexOf(ui->stereoWeidener);
        break;
      case Compressor:
        mpActivePage = ui->compressorFrame;
        index = indexOf(ui->compressorFrame);
        break;
      case NoiseGate21:
      case NoiseGate41:
        mpActivePage = ui->gateFrame;
        index = indexOf(ui->gateFrame);
        break;
      case VintageChorus:
        mpActivePage = ui->vintageChorusFrame;
        index = indexOf(ui->vintageChorusFrame);
        break;
      case HyperChorus:
        mpActivePage = ui->hyperChorusFrame;
        index = indexOf(ui->hyperChorusFrame);
        break;
      case AirChorus:
        mpActivePage = ui->airChorusFrame;
        index = indexOf(ui->airChorusFrame);
        break;
      case MicroPitch:
        mpActivePage = ui->microPitch;
        index = indexOf(ui->microPitch);
        break;
      case Vibrato:
        mpActivePage = ui->vibrato;
        index = indexOf(ui->vibrato);
        break;
      case RotarySpeaker:
        mpActivePage = ui->rotarySpeaker;
        index = indexOf(ui->rotarySpeaker);
        break;
      case Tremolo:
        mpActivePage = ui->tremolo;
        index = indexOf(ui->tremolo);
        break;
      case Phaser:
      case PhaserVibe:
        mpActivePage = ui->phaser;
        index = indexOf(ui->phaser);
        break;
      case PhaserOneway:
        mpActivePage = ui->phaserOneway;
        index = indexOf(ui->phaserOneway);
        break;
      case Flanger:
        mpActivePage = ui->flanger;
        index = indexOf(ui->flanger);
        break;
      case FlangerOneway:
        mpActivePage = ui->flangerOneway;
        index = indexOf(ui->flangerOneway);
        break;
      case Space:
        mpActivePage = ui->space;
        index = indexOf(ui->space);
        break;
      case Transpose:
        mpActivePage = ui->transpose;
        index = indexOf(ui->transpose);
        break;
      case PedalPitch:
        mpActivePage = ui->pedalPitch;
        index = indexOf(ui->pedalPitch);
        break;
      case PedalVinylStop:
        mpActivePage = ui->pedalVinylStop;
        index = indexOf(ui->pedalVinylStop);
        break;
      case ChromaticPitch:
        mpActivePage = ui->chromaticPitch;
        index = indexOf(ui->chromaticPitch);
        break;
      case HarmonicPitch:
        mpActivePage = ui->harmonicPitch;
        index = indexOf(ui->harmonicPitch);
        break;
      case AnalogOctaver:
        mpActivePage = ui->analogOctaver;
        index = indexOf(ui->analogOctaver);
        break;
      case LoopMono:
      case LoopStereo:
        mpActivePage = ui->loop;
        index = indexOf(ui->loop);
        break;
      case LoopDistortion:
        mpActivePage = ui->loopDistortion;
        index = indexOf(ui->loopDistortion);
        break;
      case LegacyDelay:
        mpActivePage = ui->legacyDelay;
        index = indexOf(ui->legacyDelay);
        break;
      default:
        mpActivePage = ui->dummyStomp;
        index = indexOf(ui->dummyStomp);
        break;
    }

    if(mpActivePage != nullptr && !mpActivePage->isActive())
    {
      setCurrentIndex(index);
      mActiveStompType = fxType;
      mpActivePage->activate(*pActiveStomp);
      emit editorPageChanged(mpActivePage);
      requestValues();
    }
  }
}

void StompEditorFrame::onDelayType(::DelayType delayType)
{
  Delay* pActiveDelay = nullptr;
  if(mpActivePage != nullptr)
  {
    if(delayType != mActiveStompType)
    {
      mpActivePage->deactivate();
      mpActivePage = nullptr;
      emit editorPageChanged(mpActivePage);
    }
  }

  int index = 0;

  pActiveDelay = qobject_cast<Delay*>(mpActiveStomp);

  if(pActiveDelay != nullptr)
  {
    switch(delayType)
    {
      case FreeDelay:
      case AnalogDelay:
        mpActivePage = ui->delay;
        index = indexOf(ui->delay);
        break;
      case TapDelay:
        mpActivePage = ui->tapDelay;
        index = indexOf(ui->tapDelay);
        break;
      default:
        mpActivePage = ui->dummyStomp;
        index = indexOf(ui->dummyStomp);
        break;
    }

    if(mpActivePage != nullptr && !mpActivePage->isActive())
    {
      setCurrentIndex(index);
      mActiveStompType = delayType;
      mpActivePage->activate(*pActiveDelay);
      emit editorPageChanged(mpActivePage);
      requestValues();
    }
  }
}

void StompEditorFrame::onReverbType(::ReverbType reverbType)
{
  Reverb* pActiveReverb = nullptr;
  if(mpActivePage != nullptr)
  {
    if(reverbType != mActiveStompType)
    {
      mpActivePage->deactivate();
      mpActivePage = nullptr;
      emit editorPageChanged(mpActivePage);
    }
  }

  int index = 0;

  pActiveReverb = qobject_cast<Reverb*>(mpActiveStomp);

  if(pActiveReverb != nullptr)
  {
    switch(reverbType)
    {
      case Hall:
      case LargeRoom:
      case SmallRoom:
      case Ambience:
      case Matchbox:
        mpActivePage = ui->reverb;
        index = indexOf(ui->reverb);
        break;
      default:
        mpActivePage = ui->dummyStomp;
        index = indexOf(ui->dummyStomp);
        break;
    }

    if(mpActivePage != nullptr && !mpActivePage->isActive())
    {
      setCurrentIndex(index);
      mActiveStompType = reverbType;
      mpActivePage->activate(*pActiveReverb);
      emit editorPageChanged(mpActivePage);
      requestValues();
    }
  }
}

void StompEditorFrame::onStompAOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayStompEnabled(StompA, onOff);
}

void StompEditorFrame::onStompBOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayStompEnabled(StompB, onOff);
}

void StompEditorFrame::onStompCOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayStompEnabled(StompC, onOff);
}

void StompEditorFrame::onStompDOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayStompEnabled(StompD, onOff);
}

void StompEditorFrame::onStompXOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayStompEnabled(StompX, onOff);
}

void StompEditorFrame::onStompModOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayStompEnabled(StompMOD, onOff);
}

void StompEditorFrame::onStompAType(::FXType type)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayStompType(StompA, type);
}

void StompEditorFrame::onStompBType(::FXType type)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayStompType(StompB, type);
}

void StompEditorFrame::onStompCType(::FXType type)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayStompType(StompC, type);
}

void StompEditorFrame::onStompDType(::FXType type)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayStompType(StompD, type);
}

void StompEditorFrame::onStompXType(::FXType type)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayStompType(StompX, type);
}

void StompEditorFrame::onStompModType(::FXType type)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayStompType(StompMOD, type);
}

// delay
// kpa => ui
void StompEditorFrame::onDelayOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayDelayEnabled(onOff);
}
//------------------------------------------------------------------------------------------

// reverb
// kpa => ui
void StompEditorFrame::onReverbOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayReverbEnabled(onOff);
}
//------------------------------------------------------------------------------------------

// profile
// kpa => ui
void StompEditorFrame::onAmpName(const QString& ampName)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayAmpName(ampName);
}
//------------------------------------------------------------------------------------------

void StompEditorFrame::nextDisplayPage()
{
  if(mpActivePage != nullptr)
  {
    QToasterLCD::Page maxPage = mpActivePage->getMaxDisplayPage();
    QToasterLCD::Page currentPage = mpActivePage->getCurrentDisplayPage();
    QToasterLCD::Page pageToSet = currentPage;

    if(currentPage < maxPage)
      pageToSet = (QToasterLCD::Page)(currentPage + 1);

    if(pageToSet != currentPage)
    {
      mpActivePage->setCurrentDisplayPage(pageToSet);
      emit editorPageChanged(mpActivePage);
    }
  }
}

void StompEditorFrame::prevDisplayPage()
{
  if(mpActivePage != nullptr)
  {
    QToasterLCD::Page currentPage = mpActivePage->getCurrentDisplayPage();
    QToasterLCD::Page pageToSet = currentPage;
    if(currentPage > QToasterLCD::Page1)
      pageToSet = (QToasterLCD::Page)(currentPage - 1);

    if(pageToSet != currentPage)
    {
      mpActivePage->setCurrentDisplayPage(pageToSet);
      emit editorPageChanged(mpActivePage);
    }
  }
}


void StompEditorFrame::requestValues()
{
  mpStompA->requestOnOff();
  mpStompB->requestOnOff();
  mpStompC->requestOnOff();
  mpStompD->requestOnOff();
  mpStompX->requestOnOff();
  mpStompMod->requestOnOff();

  mpStompA->requestType();
  mpStompB->requestType();
  mpStompC->requestType();
  mpStompD->requestType();
  mpStompX->requestType();
  mpStompMod->requestType();

  mpDelay->requestOnOffCutsTail();
  mpReverb->requestOnOffCutsTail();
  mpProfile->requestAmpName();
}

void StompEditorFrame::activatePage(IStompEditorPage* page, int index)
{
  mpActivePage = page;
  if(mpActivePage != nullptr && !mpActivePage->isActive())
  {
    setCurrentIndex(index);
    mpActivePage->activate(*mpActiveStomp);
    emit editorPageChanged(mpActivePage);
    requestValues();
  }
}
