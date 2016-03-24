#include "OutputFrame.h"
#include "ui_OutputFrame.h"

OutputFrame::OutputFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::OutputFrame)
  , mpGlobal(nullptr)
{
  ui->setupUi(this);
}

OutputFrame::~OutputFrame()
{
  delete ui;
}

void OutputFrame::activate(QObject& module)
{
  mpGlobal = qobject_cast<Global*>(&module);

  if(mpGlobal != nullptr)
  {
    connect(mpGlobal, &Global::mainOutputSourceReceived, this, &OutputFrame::OnMainOutputSource);
    connect(mpGlobal, &Global::mainOutputSourceReceived, this, &OutputFrame::OnMonitorOutputSource);
    connect(mpGlobal, &Global::directOutputSourceReceived, this, &OutputFrame::OnDirectOutputSource);
    connect(mpGlobal, &Global::spdifOutputSourceReceived, this, &OutputFrame::OnSpdifOutputSource);

    mpGlobal->requestMainOutputSource();
    mpGlobal->requestMonitorOutputSource();
    mpGlobal->requestDirectOutputSource();
    mpGlobal->requestSPDIFOutputSource();
  }
}

void OutputFrame::deactivate()
{
  if(mpGlobal != nullptr)
  {
    disconnect(mpGlobal, &Global::mainOutputSourceReceived, this, &OutputFrame::OnMainOutputSource);
    disconnect(mpGlobal, &Global::mainOutputSourceReceived, this, &OutputFrame::OnMonitorOutputSource);
    disconnect(mpGlobal, &Global::directOutputSourceReceived, this, &OutputFrame::OnDirectOutputSource);
    disconnect(mpGlobal, &Global::spdifOutputSourceReceived, this, &OutputFrame::OnSpdifOutputSource);
    mpGlobal = nullptr;
  }
}

QToasterLCD::Page OutputFrame::getMaxDisplayPage()
{
  return ui->lcdDisplay->maxPage();
}

QToasterLCD::Page OutputFrame::getCurrentDisplayPage()
{
  return ui->lcdDisplay->currentPage();
}

void OutputFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui->lcdDisplay->maxPage())
  {
    ui->lcdDisplay->setCurrentPage(page);
  }
}

void OutputFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui->lcdDisplay->setStompFXType(stompInstance, fxType);
}

void OutputFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui->lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void OutputFrame::displayDelayEnabled(bool enabled)
{
  ui->lcdDisplay->setDelayEnabled(enabled);
}

void OutputFrame::displayReverbEnabled(bool enabled)
{
  ui->lcdDisplay->setReverbEnabled(enabled);
}

void OutputFrame::displayAmpName(const QString&  ampName)
{
  ui->lcdDisplay->setAmpName(ampName);
}

void OutputFrame::on_mainOutputSourceDial_valueChanged(int valueIndex)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyMainOutputSource(valueIndex);
}

void OutputFrame::on_monitorOutputSourceDial_valueChanged(int valueIndex)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyMonitorOutputSource(valueIndex);
}

void OutputFrame::on_directOutputSourceDial_valueChanged(int valueIndex)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyDirectOutputSource(valueIndex);
}

void OutputFrame::on_spdifOutputSourceDial_valueChanged(int valueIndex)
{
  if(mpGlobal != nullptr)
    mpGlobal->applySpdifOutputSource(valueIndex);
}

void OutputFrame::OnMainOutputSource(int valueIndex)
{
  ui->mainOutputSourceDial->setValue(valueIndex);
  update();
}

void OutputFrame::OnMonitorOutputSource(int valueIndex)
{
  ui->monitorOutputSourceDial->setValue(valueIndex);
  update();
}

void OutputFrame::OnDirectOutputSource(int valueIndex)
{
  ui->directOutputSourceDial->setValue(valueIndex);
  update();
}

void OutputFrame::OnSpdifOutputSource(int valueIndex)
{
  ui->spdifOutputSourceDial->setValue(valueIndex);
  update();
}
