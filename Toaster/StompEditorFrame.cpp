#include "StompEditorFrame.h"
#include "ui_StompEditorFrame.h"
#include "Stomp.h"
#include "StompEditorPage.h"

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
    Stomp* pActiveStomp = dynamic_cast<Stomp*>(mpActiveStomp);
    Delay* pDelay = dynamic_cast<Delay*>(mpActiveStomp);
    Reverb* pReverb = dynamic_cast<Reverb*>(mpActiveStomp);
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
  }

  requestValues();
}

void StompEditorFrame::deactivate()
{
  if(mpActiveStomp != nullptr)
  {
    Stomp* pActiveStomp = dynamic_cast<Stomp*>(mpActiveStomp);
    Delay* pDelay = dynamic_cast<Delay*>(mpActiveStomp);
    Reverb* pReverb = dynamic_cast<Reverb*>(mpActiveStomp);

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
    }
  }

  pActiveStomp = dynamic_cast<Stomp*>(mpActiveStomp);

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
        break;
      case WahRingModulator:
      case WahFrequencyShifter:
        mpActivePage = ui->wahNoPeak;
        break;
      case WahFormantShifter:
        mpActivePage = ui->wahFormantShift;
        break;
      case WahPhaser:
        mpActivePage = ui->wahPhaser;
        break;
      case PureBooster:
        mpActivePage = ui->pureBooster;
        break;
      case SoftShaper:
      case HardShaper:
      case WaveShaper:
      case PlusDS:
      case FuzzDS:
        mpActivePage = ui->driveDS;
        break;
      case BitShaper:
      case GreenScream:
      case OneDS:
      case Muffin:
      case MouseDS:
        mpActivePage = ui->driveAndToneDS;
        break;
      case RectiShaper:
        mpActivePage = ui->rectiShaper;
        break;
      case TrebleBooster:
      case LeadBooster:
        mpActivePage = ui->toneAndDuckingDS;
        break;
      case WahPedalBooster:
        mpActivePage = ui->wahPedalBooster;
        break;
      case MetalDS:
        mpActivePage = ui->metalDS;
        break;
      case GraphicEqualizer:
        mpActivePage = ui->graphicEqualizer;
        break;
      case StudioEqualizer:
        mpActivePage = ui->studioEqualizer;
        break;
      case MetalEqualizer:
        mpActivePage = ui->metalEqualizer;
        break;
      case StereoWeidener:
        mpActivePage = ui->stereoWeidener;
        break;
      case Compressor:
        mpActivePage = ui->compressorFrame;
        break;
      case NoiseGate21:
      case NoiseGate41:
        mpActivePage = ui->gateFrame;
        break;
      case VintageChorus:
        mpActivePage = ui->vintageChorusFrame;
        break;
      case HyperChorus:
        mpActivePage = ui->hyperChorusFrame;
        break;
      case AirChorus:
        mpActivePage = ui->airChorusFrame;
        break;
      case MicroPitch:
        mpActivePage = ui->microPitch;
        break;
      case Vibrato:
        mpActivePage = ui->vibrato;
        break;
      case RotarySpeaker:
        mpActivePage = ui->rotarySpeaker;
        break;
      case Tremolo:
        mpActivePage = ui->tremolo;
        break;
      case Phaser:
      case PhaserVibe:
      case PhaserOneway:
        mpActivePage = ui->phaser;
        break;
      case Flanger:
      case FlangerOneway:
        mpActivePage = ui->flanger;
        break;
      case Space:
        mpActivePage = ui->space;
        break;
      case Transpose:
        mpActivePage = ui->transpose;
        break;
      case PedalPitch:
        mpActivePage = ui->pedalPitch;
        break;
      case PedalVinylStop:
        mpActivePage = ui->pedalVinylStop;
        break;
      case ChromaticPitch:
        mpActivePage = ui->chromaticPitch;
        break;
      case AnalogOctaver:
        mpActivePage = ui->analogOctaver;
        break;
      case LoopMono:
      case LoopStereo:
        mpActivePage = ui->loop;
        break;
      case LoopDistortion:
        mpActivePage = ui->loopDistortion;
        break;
      default:
         mpActivePage = ui->dummyStomp;
         break;
    }

    if(mpActivePage != nullptr && !mpActivePage->isActive())
    {
      int index = 0; // dummy page => default
      QWidget* pTmp = dynamic_cast<QWidget*>(mpActivePage);
      if(pTmp != nullptr)
        index = indexOf(pTmp);
      setCurrentIndex(index);
      mActiveStompType = fxType;
      mpActivePage->activate(*pActiveStomp);
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
    }
  }

  pActiveDelay = dynamic_cast<Delay*>(mpActiveStomp);

  if(pActiveDelay != nullptr)
  {
    switch(delayType)
    {
      case FreeDelay:
      case AnalogDelay:
        mpActivePage = ui->delay;
        break;
      case TapDelay:
        mpActivePage = ui->tapDelay;
        break;
      default:
        mpActivePage = ui->dummyStomp;
    }

    if(mpActivePage != nullptr && !mpActivePage->isActive())
    {
      int index = 0; // dummy page => default
      QWidget* pTmp = dynamic_cast<QWidget*>(mpActivePage);
      if(pTmp != nullptr)
        index = indexOf(pTmp);
      setCurrentIndex(index);
      mActiveStompType = delayType;
      mpActivePage->activate(*pActiveDelay);
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
    }
  }

  pActiveReverb = dynamic_cast<Reverb*>(mpActiveStomp);

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
        break;
      default:
        mpActivePage = ui->dummyStomp;
    }

    if(mpActivePage != nullptr && !mpActivePage->isActive())
    {
      int index = 0; // dummy page => default
      QWidget* pTmp = dynamic_cast<QWidget*>(mpActivePage);
      if(pTmp != nullptr)
        index = indexOf(pTmp);
      setCurrentIndex(index);
      mActiveStompType = reverbType;
      mpActivePage->activate(*pActiveReverb);
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
