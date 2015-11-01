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

void StompEditorFrame::onActiveStompType(FXType type)
{
  if(mpActivePage != nullptr && type != mpActivePage->getFXType())
  {
    mpActivePage->deactivate();
    mpActivePage = nullptr;
  }

  switch(type)
  {
  case WahWah:
    if(mpActiveStomp != nullptr && !ui->wahWah->isActive())
    {
      ui->wahWah->activate(*mpActiveStomp);
      setCurrentIndex(1);
      mpActivePage = ui->wahWah;
      requestValues();
    }
    break;
  default:
    if(mpActiveStomp != nullptr && !ui->dummyStomp->isActive())
    {
      ui->dummyStomp->activate(*mpActiveStomp);
      setCurrentIndex(0);
      mpActivePage = ui->dummyStomp;
      requestValues();
    }
  }
}

void StompEditorFrame::onStompAOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->setStompEnabled(StompA, onOff);
}

void StompEditorFrame::onStompBOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->setStompEnabled(StompB, onOff);
}

void StompEditorFrame::onStompCOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->setStompEnabled(StompC, onOff);
}

void StompEditorFrame::onStompDOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->setStompEnabled(StompD, onOff);
}

void StompEditorFrame::onStompXOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->setStompEnabled(StompX, onOff);
}

void StompEditorFrame::onStompModOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->setStompEnabled(StompMOD, onOff);
}

void StompEditorFrame::onStompAType(::FXType type)
{
  if(mpActivePage != nullptr)
    mpActivePage->setStompType(StompA, type);
}

void StompEditorFrame::onStompBType(::FXType type)
{
  if(mpActivePage != nullptr)
    mpActivePage->setStompType(StompB, type);
}

void StompEditorFrame::onStompCType(::FXType type)
{
  if(mpActivePage != nullptr)
    mpActivePage->setStompType(StompC, type);
}

void StompEditorFrame::onStompDType(::FXType type)
{
  if(mpActivePage != nullptr)
    mpActivePage->setStompType(StompD, type);
}

void StompEditorFrame::onStompXType(::FXType type)
{
  if(mpActivePage != nullptr)
    mpActivePage->setStompType(StompX, type);
}

void StompEditorFrame::onStompModType(::FXType type)
{
  if(mpActivePage != nullptr)
    mpActivePage->setStompType(StompMOD, type);
}

// delay
// kpa => ui
void StompEditorFrame::onDelayOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->setDelayEnabled(onOff);
}
//------------------------------------------------------------------------------------------

// reverb
// kpa => ui
void StompEditorFrame::onReverbOnOff(bool onOff)
{
  if(mpActivePage != nullptr)
    mpActivePage->setReverbEnabled(onOff);
}
//------------------------------------------------------------------------------------------

// profile
// kpa => ui
void StompEditorFrame::onAmpName(const QString& ampName)
{
  if(mpActivePage != nullptr)
    mpActivePage->setAmpName(ampName);
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

}
