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
#include "StompEditorFrame.h"
#include "Stomp.h"
#include "StompEditorPage.h"
#include "Input.h"
#include "Settings.h"
#include "Delay.h"
#include "Reverb.h"
#include "Profile.h"
#include "AirChorusFrame.h"
#include "AmpFrame.h"
#include "AnalogOctaverFrame.h"
#include "CabFrame.h"
#include "ChromaticPitchFrame.h"
#include "CompressorFrame.h"
#include "DelayFrame.h"
#include "DriveAndToneDSFrame.h"
#include "DriveDSFrame.h"
#include "FlangerFrame.h"
#include "FlangerOnewayFrame.h"
#include "GateFrame.h"
#include "GraphicEqualizerFrame.h"
#include "HarmonicPitchFrame.h"
#include "HyperChorusFrame.h"
#include "InputFrame.h"
#include "LegacyDelayFrame.h"
#include "LoopDistortionFrame.h"
#include "LoopFrame.h"
#include "MetalDSFrame.h"
#include "MetalEqualizerFrame.h"
#include "MicroPitchFrame.h"
#include "OutputFrame.h"
#include "PedalPitchFrame.h"
#include "PedalVinylStopFrame.h"
#include "PhaserFrame.h"
#include "PhaserOnewayFrame.h"
#include "PureBoosterFrame.h"
#include "RectiShaperFrame.h"
#include "ReverbFrame.h"
#include "RotarySpeakerFrame.h"
#include "SpaceFrame.h"
#include "StereoWidenerFrame.h"
#include "StudioEqualizerFrame.h"
#include "TapDelayFrame.h"
#include "ToneAndDuckingDSFrame.h"
#include "TransposeFrame.h"
#include "TremoloFrame.h"
#include "VibratoFrame.h"
#include "VintageChorusFrame.h"
#include "WahFormantShiftFrame.h"
#include "WahNoPeakFrame.h"
#include "WahPedalBoosterFrame.h"
#include "WahPhaserFrame.h"
#include "WahWahFrame.h"

StompEditorFrame::StompEditorFrame(QWidget *parent)
  : QWidget(parent)
  , mpActiveStomp(nullptr)
  , mActiveStompType(-1)
  , mpActivePage(nullptr)
{
  ui.setupUi(this);
}

StompEditorFrame::~StompEditorFrame()
{
}

void StompEditorFrame::init()
{
  // stomps
  connect(&stompAObj, &Stomp::onOffReceived, this, &StompEditorFrame::onStompAOnOff);
  connect(&stompBObj, &Stomp::onOffReceived, this, &StompEditorFrame::onStompBOnOff);
  connect(&stompCObj, &Stomp::onOffReceived, this, &StompEditorFrame::onStompCOnOff);
  connect(&stompDObj, &Stomp::onOffReceived, this, &StompEditorFrame::onStompDOnOff);
  connect(&stompXObj, &Stomp::onOffReceived, this, &StompEditorFrame::onStompXOnOff);
  connect(&stompModObj, &Stomp::onOffReceived, this, &StompEditorFrame::onStompModOnOff);
  connect(&stompAObj, &Stomp::typeReceived, this, &StompEditorFrame::onStompAType);
  connect(&stompBObj, &Stomp::typeReceived, this, &StompEditorFrame::onStompBType);
  connect(&stompCObj, &Stomp::typeReceived, this, &StompEditorFrame::onStompCType);
  connect(&stompDObj, &Stomp::typeReceived, this, &StompEditorFrame::onStompDType);
  connect(&stompXObj, &Stomp::typeReceived, this, &StompEditorFrame::onStompXType);
  connect(&stompModObj, &Stomp::typeReceived, this, &StompEditorFrame::onStompModType);
  // delay
  if(Settings::get().getKPAOSVersion() >= 0x04000000)
  {
    connect(&stompDelayObj, &Stomp::onOffReceived, this, &StompEditorFrame::onDelayOnOff);
    connect(&stompDelayObj, &Stomp::typeReceived, this, &StompEditorFrame::onStompDelayType);
  }
  else
  {
    connect(&delayObj, &Delay::onOffCutsTailReceived, this, &StompEditorFrame::onDelayOnOff);
  }

  // reverb
  connect(&reverbObj, &Reverb::onOffCutsTailReceived, this, &StompEditorFrame::onReverbOnOff);
  // profile
  connect(&profileObj, &Profile::ampNameReceived, this, &StompEditorFrame::onAmpName);
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
      activatePage(new AmpFrame(this));
    }
    else if(pCab != nullptr)
    {
      activatePage(new CabFrame(this));
    }
    else if(pGlobal != nullptr)
    {
      activatePage(new OutputFrame(this));
    }
    else if(pInput != nullptr)
    {
      activatePage(new InputFrame(this));
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
    ui.dummyStompFrame->show();
    delete mpActivePage;
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

  pActiveStomp = qobject_cast<Stomp*>(mpActiveStomp);

  if(mpActivePage == nullptr && pActiveStomp != nullptr)
  {
    switch(fxType)
    {
      case WahWah:
      case WahHighPass:
      case WahLowPass:
      case WahVowelFilter:
      case WahFlanger:
      case WahRateReducer:
        mpActivePage = new WahWahFrame(this);
        break;
      case WahRingModulator:
      case WahFrequencyShifter:
        mpActivePage = new WahNoPeakFrame(this);
        break;
      case WahFormantShifter:
        mpActivePage = new WahFormantShiftFrame(this);
        break;
      case WahPhaser:
        mpActivePage = new WahPhaserFrame(this);
        break;
      case PureBooster:
        mpActivePage = new PureBoosterFrame(this);
        break;
      case SoftShaper:
      case HardShaper:
      case WaveShaper:
      case PlusDS:
      case FuzzDS:
        mpActivePage = new DriveDSFrame(this);
        break;
      case BitShaper:
      case GreenScream:
      case OneDS:
      case Muffin:
      case MouseDS:
        mpActivePage = new DriveAndToneDSFrame(this);
        break;
      case RectiShaper:
        mpActivePage = new RectiShaperFrame(this);
        break;
      case TrebleBooster:
      case LeadBooster:
        mpActivePage = new ToneAndDuckingDSFrame(this);
        break;
      case WahPedalBooster:
        mpActivePage = new WahPedalBoosterFrame(this);
        break;
      case MetalDS:
        mpActivePage = new MetalDSFrame(this);
        break;
      case GraphicEqualizer:
        mpActivePage = new GraphicEqualizerFrame(this);
        break;
      case StudioEqualizer:
        mpActivePage = new StudioEqualizerFrame(this);
        break;
      case MetalEqualizer:
        mpActivePage = new MetalEqualizerFrame(this);
        break;
      case StereoWidener:
        mpActivePage = new StereoWidenerFrame(this);
        break;
      case Compressor:
        mpActivePage = new CompressorFrame(this);
        break;
      case NoiseGate21:
      case NoiseGate41:
        mpActivePage = new GateFrame(this);
        break;
      case VintageChorus:
        mpActivePage = new VintageChorusFrame(this);
        break;
      case HyperChorus:
        mpActivePage = new HyperChorusFrame(this);
        break;
      case AirChorus:
        mpActivePage = new AirChorusFrame(this);
        break;
      case MicroPitch:
        mpActivePage = new MicroPitchFrame(this);
        break;
      case Vibrato:
        mpActivePage = new VibratoFrame(this);
        break;
      case RotarySpeaker:
        mpActivePage = new RotarySpeakerFrame(this);
        break;
      case Tremolo:
        mpActivePage = new TremoloFrame(this);
        break;
      case Phaser:
      case PhaserVibe:
        mpActivePage = new PhaserFrame(this);
        break;
      case PhaserOneway:
        mpActivePage = new PhaserOnewayFrame(this);
        break;
      case Flanger:
        mpActivePage = new FlangerFrame(this);
        break;
      case FlangerOneway:
        mpActivePage = new FlangerOnewayFrame(this);
        break;
      case Space:
        mpActivePage = new SpaceFrame(this);
        break;
      case Transpose:
        mpActivePage = new TransposeFrame(this);
        break;
      case PedalPitch:
        mpActivePage = new PedalPitchFrame(this);
        break;
      case PedalVinylStop:
        mpActivePage = new PedalVinylStopFrame(this);
        break;
      case ChromaticPitch:
        mpActivePage = new ChromaticPitchFrame(this);
        break;
      case HarmonicPitch:
        mpActivePage = new HarmonicPitchFrame(this);
        break;
      case AnalogOctaver:
        mpActivePage = new AnalogOctaverFrame(this);
        break;
      case LoopMono:
      case LoopStereo:
        mpActivePage = new LoopFrame(this);
        break;
      case LoopDistortion:
        mpActivePage = new LoopDistortionFrame(this);
        break;
      case LegacyDelay:
        mpActivePage = new LegacyDelayFrame(this);
        break;
      default:
        ui.dummyStompFrame->show();
        break;
    }

    if(mpActivePage != nullptr && !mpActivePage->isActive())
    {
      setUpdatesEnabled(false);
      mActiveStompType = fxType;
      ui.dummyStompFrame->hide();
      mpActivePage->activate(*pActiveStomp);
      setUpdatesEnabled(true);
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

  pActiveDelay = qobject_cast<Delay*>(mpActiveStomp);

  if(mpActivePage == nullptr && pActiveDelay != nullptr)
  {
    switch(delayType)
    {
      case FreeDelay:
      case AnalogDelay:
        mpActivePage = new DelayFrame(this);
        break;
      case TapDelay:
        mpActivePage = new TapDelayFrame(this);
        break;
      default:
        ui.dummyStompFrame->show();
        break;
    }

    if(mpActivePage != nullptr && !mpActivePage->isActive())
    {
      setUpdatesEnabled(false);
      mActiveStompType = delayType;
      ui.dummyStompFrame->hide();
      mpActivePage->activate(*pActiveDelay);
      setUpdatesEnabled(true);
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

  pActiveReverb = qobject_cast<Reverb*>(mpActiveStomp);

  if(mpActivePage == nullptr && pActiveReverb != nullptr)
  {
    switch(reverbType)
    {
      case Hall:
      case LargeRoom:
      case SmallRoom:
      case Ambience:
      case Matchbox:
        mpActivePage = new ReverbFrame(this);
        break;
      default:
        ui.dummyStompFrame->show();
        break;
    }

    if(mpActivePage != nullptr && !mpActivePage->isActive())
    {
      setUpdatesEnabled(false);
      mActiveStompType = reverbType;      
      mpActivePage->activate(*pActiveReverb);
      ui.dummyStompFrame->hide();
      setUpdatesEnabled(true);
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
    mpActivePage->displayStompEnabled(StompMod, onOff);
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
    mpActivePage->displayStompType(StompMod, type);
}

void StompEditorFrame::onStompDelayType(::FXType type)
{
  if(mpActivePage != nullptr)
    mpActivePage->displayStompType(StompDelay, type);
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
  stompAObj.requestOnOff();
  stompBObj.requestOnOff();
  stompCObj.requestOnOff();
  stompDObj.requestOnOff();
  stompXObj.requestOnOff();
  stompModObj.requestOnOff();

  if(Settings::get().getKPAOSVersion() >= 0x04000000)
    stompDelayObj.requestOnOff();

  stompAObj.requestType();
  stompBObj.requestType();
  stompCObj.requestType();
  stompDObj.requestType();
  stompXObj.requestType();
  stompModObj.requestType();

  if(Settings::get().getKPAOSVersion() >= 0x04000000)
    stompDelayObj.requestType();

  if(Settings::get().getKPAOSVersion() < 0x04000000)
    delayObj.requestOnOffCutsTail();

  reverbObj.requestOnOffCutsTail();
  profileObj.requestAmpName();
}

void StompEditorFrame::activatePage(IStompEditorPage* page)
{
  mpActivePage = page;
  if(mpActivePage != nullptr && !mpActivePage->isActive())
  {
    setUpdatesEnabled(false);
    mpActivePage->activate(*mpActiveStomp);
    ui.dummyStompFrame->hide();
    setUpdatesEnabled(true);
    emit editorPageChanged(mpActivePage);
    requestValues();
  }
}
