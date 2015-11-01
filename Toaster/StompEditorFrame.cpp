#include "StompEditorFrame.h"
#include "ui_StompEditorFrame.h"
#include "Stomp.h"

StompEditorFrame::StompEditorFrame(QWidget *parent)
  : QStackedWidget(parent)
  , ui(new Ui::StompEditorFrame)
  , mpActiveStomp(nullptr)
  , mpActivePage(nullptr)
{
  ui->setupUi(this);
}

StompEditorFrame::~StompEditorFrame()
{
  delete ui;
}

void StompEditorFrame::activate(StompInstance stompInstance)
{
  Stomp* mActiveStomp = nullptr;
  switch(stompInstance)
  {
  case StompA:
    mActiveStomp = &mStompA;
    break;
  case StompB:
    mActiveStomp = &mStompB;
    break;
  case StompC:
    mActiveStomp = &mStompC;
    break;
  case StompD:
    mActiveStomp = &mStompD;
    break;
  case StompX:
    mActiveStomp = &mStompX;
    break;
  case StompMOD:
    mActiveStomp = &mStompMod;
    break;
  }

  if(mActiveStomp != nullptr)
  {
    connect(mActiveStomp, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompType(::FXType)));
    mActiveStomp->requestType();
  }
}

void StompEditorFrame::deactivate()
{
  if(mpActiveStomp != nullptr)
  {
    disconnect(mpActiveStomp, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompType(::FXType)));
    mpActivePage->deactivate();
    mpActivePage = nullptr;
  }

  mpActiveStomp = nullptr;
}

void StompEditorFrame::onStompType(FXType type)
{
  switch(type)
  {
    case WahWah:
      if(mpActiveStomp != nullptr && !ui->wahWah->isActive())
      {
        ui->wahWah->activate(*mpStomp);
        setCurrentIndex(1);
        mActiveStomp = ui->wahWah;
      }
      break;
    default:
      if(mpActiveStomp != nullptr && !ui->dummyStomp->isActive())
      {
        ui->dummyStomp->activate(*mpStomp);
        setCurrentIndex(0);
        mActiveStomp = ui->wahWah;
    }
  }
}
