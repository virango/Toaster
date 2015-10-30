#include "StompEditorFrame.h"
#include "ui_StompEditorFrame.h"
#include "Stomp.h"

StompEditorFrame::StompEditorFrame(QWidget *parent)
  : QStackedWidget(parent)
  , ui(new Ui::StompEditorFrame)
  , mpStomp(nullptr)
{
  ui->setupUi(this);
}

StompEditorFrame::~StompEditorFrame()
{
  delete ui;
}

void StompEditorFrame::attach(Stomp& stomp)
{
  mpStomp = &stomp;
  connect(mpStomp, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompType(::FXType)));
  mpStomp->requestType();
}

void StompEditorFrame::detach()
{
  if(mpStomp != nullptr)
    QStackedWidget::disconnect(mpStomp, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompType(::FXType)));
  ui->wahWah->detach();
  mpStomp = nullptr;
}

void StompEditorFrame::onStompType(FXType type)
{
  switch(type)
  {
    case WahWah:
      if(mpStomp != nullptr && !ui->wahWah->isConnected())
      {
        ui->wahWah->attach(*mpStomp);
        setCurrentIndex(1);
      }
      break;
    default:
      setCurrentIndex(0);
  }
}
