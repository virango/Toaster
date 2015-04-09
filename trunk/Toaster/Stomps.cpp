#include "Stomps.h"
#include "ui_Stomps.h"
#include "StompMidi.h"

Stomps::Stomps(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Stomps)
{
  ui->setupUi(this);
  ui->stompADock->hide();
  ui->stompBDock->hide();
  ui->stompCDock->hide();
  ui->stompDDock->hide();

  if(ui->stompAFrame)
    ui->stompAFrame->createStomp(StompMidi::A);
  if(ui->stompBFrame)
    ui->stompBFrame->createStomp(StompMidi::B);
  if(ui->stompCFrame)
    ui->stompCFrame->createStomp(StompMidi::C);
  if(ui->stompDFrame)
    ui->stompDFrame->createStomp(StompMidi::D);
}

Stomps::~Stomps()
{
    delete ui;
}

void Stomps::on_minmaxBt_clicked(bool checked)
{
  if(checked){
    ui->stompADock->show();
    ui->stompBDock->show();
    ui->stompCDock->show();
    ui->stompDDock->show();
    ui->minmaxBt->setText("-");
    adjustParentsSize();
  }
  else{
    ui->stompADock->hide();
    ui->stompBDock->hide();
    ui->stompCDock->hide();
    ui->stompDDock->hide();
    ui->minmaxBt->setText("+");
    adjustParentsSize();
  }
}

void Stomps::adjustParentsSize()
{
  QWidget* parent = parentWidget();
  while(parent){
    if(parent->layout())
        parent->layout()->invalidate();
    if(parent->parentWidget())
      parent->adjustSize();
    parent = parent->parentWidget();
  }
}

void Stomps::requestValues()
{
  if(ui->stompAFrame)
    ui->stompAFrame->requestValues();
  if(ui->stompBFrame)
    ui->stompBFrame->requestValues();
  if(ui->stompCFrame)
    ui->stompCFrame->requestValues();
  if(ui->stompDFrame)
    ui->stompDFrame->requestValues();
}

