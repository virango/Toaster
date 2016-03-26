#include "OutputFrame.h"
#include "ui_OutputFrame.h"
#include "LookUpTables.h"

OutputFrame::OutputFrame(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::OutputFrame)
  , mpGlobal(nullptr)
{
  ui->setupUi(this);
  ui->mainVolumeDial->setLookUpTable(LookUpTables::getMainVolumeValues());
  ui->monitorVolumeDial->setLookUpTable(LookUpTables::getMainVolumeValues());
  ui->directVolumeDial->setLookUpTable(LookUpTables::getMainVolumeValues());
  ui->headphoneVolumeDial->setLookUpTable(LookUpTables::getMainVolumeValues());
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
    connect(mpGlobal, &Global::mainOutputVolumeReceived, this, &OutputFrame::OnMainVolume);
    connect(mpGlobal, &Global::monitorOutputVolumeReceived, this, &OutputFrame::OnMonitorVolume);
    connect(mpGlobal, &Global::directOutputVolumeReceived, this, &OutputFrame::OnDirectVolume);
    connect(mpGlobal, &Global::headphoneOutputVolumeReceived, this, &OutputFrame::OnHeadphoneVolume);

    mpGlobal->requestMainOutputSource();
    mpGlobal->requestMonitorOutputSource();
    mpGlobal->requestDirectOutputSource();
    mpGlobal->requestSPDIFOutputSource();
    mpGlobal->requestMainOutputVolume();
    mpGlobal->requestMonitorOutputVolume();
    mpGlobal->requestDirectOutputVolume();
    mpGlobal->requestHeadphoneOutputVolume();
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
    disconnect(mpGlobal, &Global::mainOutputVolumeReceived, this, &OutputFrame::OnMainVolume);
    disconnect(mpGlobal, &Global::monitorOutputVolumeReceived, this, &OutputFrame::OnMonitorVolume);
    disconnect(mpGlobal, &Global::directOutputVolumeReceived, this, &OutputFrame::OnDirectVolume);
    disconnect(mpGlobal, &Global::headphoneOutputVolumeReceived, this, &OutputFrame::OnHeadphoneVolume);
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

void OutputFrame::on_mainVolumeDial_valueChanged(int value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyMainOutputVolume(value);
}

void OutputFrame::on_monitorVolumeDial_valueChanged(int value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyMonitorOutputVolume(value);
}

void OutputFrame::on_directVolumeDial_valueChanged(int value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyDirectOutputVolume(value);
}

void OutputFrame::on_headphoneVolumeDial_valueChanged(int value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyHeadphoneOutputVolume(value);
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

void OutputFrame::OnMainVolume(int value)
{
  ui->mainVolumeDial->setValue(value);
  update();
}

void OutputFrame::OnMonitorVolume(int value)
{
  ui->monitorVolumeDial->setValue(value);
  update();
}

void OutputFrame::OnDirectVolume(int value)
{
  ui->directVolumeDial->setValue(value);
  update();
}

void OutputFrame::OnHeadphoneVolume(int value)
{
  ui->headphoneVolumeDial->setValue(value);
  update();
}
