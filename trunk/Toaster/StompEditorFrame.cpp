#include "StompEditorFrame.h"
#include "ui_StompEditorFrame.h"
#include "Stomp.h"
#include "StompEditorPage.h"

StompEditorFrame::StompEditorFrame(QWidget *parent)
  : QStackedWidget(parent)
  , ui(new Ui::StompEditorFrame)
  , mStompA(StompA)
  , mStompB(StompB)
  , mStompC(StompC)
  , mStompD(StompD)
  , mStompX(StompX)
  , mStompMod(StompMOD)
  , mpActiveStomp(nullptr)
  , mpActivePage(nullptr)
{
  ui->setupUi(this);
  // stomps
  connect(&mStompA, SIGNAL(onOffReceived(bool)), this, SLOT(onStompAOnOff(bool)));
  connect(&mStompB, SIGNAL(onOffReceived(bool)), this, SLOT(onStompBOnOff(bool)));
  connect(&mStompC, SIGNAL(onOffReceived(bool)), this, SLOT(onStompCOnOff(bool)));
  connect(&mStompD, SIGNAL(onOffReceived(bool)), this, SLOT(onStompDOnOff(bool)));
  connect(&mStompX, SIGNAL(onOffReceived(bool)), this, SLOT(onStompXOnOff(bool)));
  connect(&mStompMod, SIGNAL(onOffReceived(bool)), this, SLOT(onStompModOnOff(bool)));
  connect(&mStompA, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompAType(::FXType)));
  connect(&mStompB, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompBType(::FXType)));
  connect(&mStompC, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompCType(::FXType)));
  connect(&mStompD, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompDType(::FXType)));
  connect(&mStompX, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompXType(::FXType)));
  connect(&mStompMod, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompModType(::FXType)));
  // delay
  connect(&mDelay, SIGNAL(onOffCutsTailReceived(bool)), this, SLOT(onDelayOnOff(bool)));
  // reverb
  connect(&mReverb, SIGNAL(onOffCutsTailReceived(bool)), this, SLOT(onReverbOnOff(bool)));
  // profile
  connect(&mProfile, SIGNAL(ampNameReceived(const QString&)), this, SLOT(onAmpName(const QString&)));
}

StompEditorFrame::~StompEditorFrame()
{
  delete ui;
}

void StompEditorFrame::activate(StompInstance stompInstance)
{
  deactivate();
  switch(stompInstance)
  {
  case StompA:
    mpActiveStomp = &mStompA;
    break;
  case StompB:
    mpActiveStomp = &mStompB;
    break;
  case StompC:
    mpActiveStomp = &mStompC;
    break;
  case StompD:
    mpActiveStomp = &mStompD;
    break;
  case StompX:
    mpActiveStomp = &mStompX;
    break;
  case StompMOD:
    mpActiveStomp = &mStompMod;
    break;
  }

  if(mpActiveStomp != nullptr)
  {
    connect(mpActiveStomp, SIGNAL(typeReceived(::FXType)), this, SLOT(onActiveStompType(::FXType)));
    mpActiveStomp->requestType();
  }

  requestValues();
}

void StompEditorFrame::deactivate()
{
  if(mpActiveStomp != nullptr)
  {
    disconnect(mpActiveStomp, SIGNAL(typeReceived(::FXType)), this, SLOT(onActiveStompType(::FXType)));
    mpActiveStomp = nullptr;
  }

  if(mpActivePage != nullptr)
  {
    mpActivePage->deactivate();
    mpActivePage = nullptr;
  }
}

void StompEditorFrame::onActiveStompType(FXType fxType)
{
  if(mpActivePage != nullptr && fxType != mpActivePage->getFXType())
  {
    mpActivePage->deactivate();
    mpActivePage = nullptr;
  }

  if(mpActiveStomp != nullptr)
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
      mpActivePage->activate(*mpActiveStomp);
      mpActivePage->setFXType(fxType);
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
  mStompA.requestOnOff();
  mStompB.requestOnOff();
  mStompC.requestOnOff();
  mStompD.requestOnOff();
  mStompX.requestOnOff();
  mStompMod.requestOnOff();

  mStompA.requestType();
  mStompB.requestType();
  mStompC.requestType();
  mStompD.requestType();
  mStompX.requestType();
  mStompMod.requestType();

  mDelay.requestOnOffCutsTail();
  mReverb.requestOnOffCutsTail();
  mProfile.requestAmpName();
}
