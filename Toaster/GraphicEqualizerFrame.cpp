#include "GraphicEqualizerFrame.h"
#include "ui_GraphicEqualizerFrame.h"
#include "Stomp.h"
#include "LookUpTables.h"

GraphicEqualizerFrame::GraphicEqualizerFrame(QWidget *parent)
  : QWidget(parent)
  ,ui(new Ui::GraphicEqualizerFrame)
  , mpStomp(nullptr)
  , mFXType(None)
{
  ui->setupUi(this);
  ui->pageDial->setValue(0);
  ui->lowCutDial->setLookUpTable(LookUpTables::getFrequencyValues());
  ui->highCutDial->setLookUpTable(LookUpTables::getFrequencyValues());
}

GraphicEqualizerFrame::~GraphicEqualizerFrame()
{
  delete ui;
}

void GraphicEqualizerFrame::activate(QObject& stomp)
{
  mpStomp = dynamic_cast<Stomp*>(&stomp);

  if(mpStomp != nullptr)
  {
    connect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    connect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    connect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    connect(mpStomp, SIGNAL(graphicEQBand1Received(double)), this, SLOT(onBand1(double)));
    connect(mpStomp, SIGNAL(graphicEQBand2Received(double)), this, SLOT(onBand2(double)));
    connect(mpStomp, SIGNAL(graphicEQBand3Received(double)), this, SLOT(onBand3(double)));
    connect(mpStomp, SIGNAL(graphicEQBand4Received(double)), this, SLOT(onBand4(double)));
    connect(mpStomp, SIGNAL(graphicEQBand5Received(double)), this, SLOT(onBand5(double)));
    connect(mpStomp, SIGNAL(graphicEQBand6Received(double)), this, SLOT(onBand6(double)));
    connect(mpStomp, SIGNAL(graphicEQBand7Received(double)), this, SLOT(onBand7(double)));
    connect(mpStomp, SIGNAL(graphicEQBand8Received(double)), this, SLOT(onBand8(double)));
    connect(mpStomp, SIGNAL(lowCutReceived(int)), this, SLOT(onLowCut(int)));
    connect(mpStomp, SIGNAL(highCutReceived(int)), this, SLOT(onHighCut(int)));

    mpStomp->requestMix();
    mpStomp->requestDucking();
    mpStomp->requestVolume();
    mpStomp->requestGraphicEQBand1();
    mpStomp->requestGraphicEQBand2();
    mpStomp->requestGraphicEQBand3();
    mpStomp->requestGraphicEQBand4();
    mpStomp->requestGraphicEQBand5();
    mpStomp->requestGraphicEQBand6();
    mpStomp->requestGraphicEQBand7();
    mpStomp->requestGraphicEQBand8();
    mpStomp->requestLowCut();
    mpStomp->requestHighCut();

    ui->lcdDisplay->setStompInstance(LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui->lcdDisplay->setStompName(LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}
void GraphicEqualizerFrame::deactivate()
{
  if(mpStomp != nullptr)
  {
    disconnect(mpStomp, SIGNAL(mixReceived(double)), this, SLOT(onMix(double)));
    disconnect(mpStomp, SIGNAL(duckingReceived(double)), this, SLOT(onDucking(double)));
    disconnect(mpStomp, SIGNAL(volumeReceived(double)), this, SLOT(onVolume(double)));
    disconnect(mpStomp, SIGNAL(graphicEQBand1Received(double)), this, SLOT(onBand1(double)));
    disconnect(mpStomp, SIGNAL(graphicEQBand2Received(double)), this, SLOT(onBand2(double)));
    disconnect(mpStomp, SIGNAL(graphicEQBand3Received(double)), this, SLOT(onBand3(double)));
    disconnect(mpStomp, SIGNAL(graphicEQBand4Received(double)), this, SLOT(onBand4(double)));
    disconnect(mpStomp, SIGNAL(graphicEQBand5Received(double)), this, SLOT(onBand5(double)));
    disconnect(mpStomp, SIGNAL(graphicEQBand6Received(double)), this, SLOT(onBand6(double)));
    disconnect(mpStomp, SIGNAL(graphicEQBand7Received(double)), this, SLOT(onBand7(double)));
    disconnect(mpStomp, SIGNAL(graphicEQBand8Received(double)), this, SLOT(onBand8(double)));
    disconnect(mpStomp, SIGNAL(lowCutReceived(int)), this, SLOT(onLowCut(int)));
    disconnect(mpStomp, SIGNAL(highCutReceived(int)), this, SLOT(onhighCut(int)));
  }
  mpStomp = nullptr;
}

void GraphicEqualizerFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void GraphicEqualizerFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void GraphicEqualizerFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void GraphicEqualizerFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void GraphicEqualizerFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void GraphicEqualizerFrame::on_pageDial_valueChanged(int valueIndex)
{
  ui->lcdDisplay->setCurrentPage((QToasterStompEditLCD::Page)valueIndex);
}

void GraphicEqualizerFrame::on_mixDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void GraphicEqualizerFrame::on_duckingDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void GraphicEqualizerFrame::on_volumeDial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void GraphicEqualizerFrame::on_band1Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand1(value);
}

void GraphicEqualizerFrame::on_band2Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand2(value);
}

void GraphicEqualizerFrame::on_band3Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand3(value);
}

void GraphicEqualizerFrame::on_band4Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand4(value);
}

void GraphicEqualizerFrame::on_band5Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand5(value);
}

void GraphicEqualizerFrame::on_band6Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand6(value);
}

void GraphicEqualizerFrame::on_band7Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand7(value);
}

void GraphicEqualizerFrame::on_band8Dial_valueChanged(double value)
{
  if(mpStomp != nullptr)
    mpStomp->applyGraphicEQBand8(value);
}

void GraphicEqualizerFrame::on_lowCutDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyLowCut(value);
}

void GraphicEqualizerFrame::on_highCutDial_valueChanged(int value)
{
  if(mpStomp != nullptr)
    mpStomp->applyHighCut(value);
}


void GraphicEqualizerFrame::onMix(double value)
{
  ui->mixDial->setValue(value);
  update();
}

void GraphicEqualizerFrame::onDucking(double value)
{
  ui->duckingDial->setValue(value);
  update();
}

void GraphicEqualizerFrame::onVolume(double value)
{
  ui->volumeDial->setValue(value);
  update();
}


void GraphicEqualizerFrame::onBand1(double value)
{
  ui->band1Dial->setValue(value);
  ui->lcdDisplay->setEqBand1Value(value);
  update();
}

void GraphicEqualizerFrame::onBand2(double value)
{
  ui->band2Dial->setValue(value);
  ui->lcdDisplay->setEqBand2Value(value);
  update();
}

void GraphicEqualizerFrame::onBand3(double value)
{
  ui->band3Dial->setValue(value);
  ui->lcdDisplay->setEqBand3Value(value);
  update();
}

void GraphicEqualizerFrame::onBand4(double value)
{
  ui->band4Dial->setValue(value);
  ui->lcdDisplay->setEqBand4Value(value);
  update();
}

void GraphicEqualizerFrame::onBand5(double value)
{
  ui->band5Dial->setValue(value);
  ui->lcdDisplay->setEqBand5Value(value);
  update();
}

void GraphicEqualizerFrame::onBand6(double value)
{
  ui->band6Dial->setValue(value);
  ui->lcdDisplay->setEqBand6Value(value);
  update();
}

void GraphicEqualizerFrame::onBand7(double value)
{
  ui->band7Dial->setValue(value);
  ui->lcdDisplay->setEqBand7Value(value);
  update();
}

void GraphicEqualizerFrame::onBand8(double value)
{
  ui->band8Dial->setValue(value);
  ui->lcdDisplay->setEqBand8Value(value);
  update();
}

void GraphicEqualizerFrame::onLowCut(int value)
{
  ui->lowCutDial->setValue(value);
  update();
}

void GraphicEqualizerFrame::onHighCut(int value)
{
  ui->highCutDial->setValue(value);
  update();
}


