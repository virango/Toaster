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
  ui->spdifVolumeDial->setLookUpTable(LookUpTables::getMainVolumeValues());
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
    connect(mpGlobal, &Global::monitorOutputSourceReceived, this, &OutputFrame::OnMonitorOutputSource);
    connect(mpGlobal, &Global::directOutputSourceReceived, this, &OutputFrame::OnDirectOutputSource);
    connect(mpGlobal, &Global::spdifOutputSourceReceived, this, &OutputFrame::OnSPDIFOutputSource);
    connect(mpGlobal, &Global::mainOutputVolumeReceived, this, &OutputFrame::OnMainVolume);
    connect(mpGlobal, &Global::monitorOutputVolumeReceived, this, &OutputFrame::OnMonitorVolume);
    connect(mpGlobal, &Global::directOutputVolumeReceived, this, &OutputFrame::OnDirectVolume);
    connect(mpGlobal, &Global::headphoneOutputVolumeReceived, this, &OutputFrame::OnHeadphoneVolume);
    connect(mpGlobal, &Global::monitorOutputEQBassReceived, this, &OutputFrame::OnMonitorOutputEQBass);
    connect(mpGlobal, &Global::monitorOutputEQMiddleReceived, this, &OutputFrame::OnMonitorOutputEQMiddle);
    connect(mpGlobal, &Global::monitorOutputEQTrebleReceived, this, &OutputFrame::OnMonitorOutputEQTreble);
    connect(mpGlobal, &Global::monitorOutputEQPresenceReceived, this, &OutputFrame::OnMonitorOutputEQPresence);
    connect(mpGlobal, &Global::monitorCabOffReceived, this, &OutputFrame::OnMonitorCabOff);
    connect(mpGlobal, &Global::mainOutputEQBassReceived, this, &OutputFrame::OnMainOutputEQBass);
    connect(mpGlobal, &Global::mainOutputEQMiddleReceived, this, &OutputFrame::OnMainOutputEQMiddle);
    connect(mpGlobal, &Global::mainOutputEQTrebleReceived, this, &OutputFrame::OnMainOutputEQTreble);
    connect(mpGlobal, &Global::mainOutputEQPresenceReceived, this, &OutputFrame::OnMainOutputEQPresence);
    connect(mpGlobal, &Global::spdifOutputVolumeReceived, this, &OutputFrame::OnSPDIFVolume);
    connect(mpGlobal, &Global::pureCabReceived, this, &OutputFrame::OnPureCabinet);
    connect(mpGlobal, &Global::spaceReceived, this, &OutputFrame::OnSpace);
    connect(mpGlobal, &Global::pureCabOnOffReceived, this, &OutputFrame::OnPureCabinetOnOff);
    connect(mpGlobal, &Global::headphoneSpaceOnOffReceived, this, &OutputFrame::OnHeadphoneSpace);
    connect(mpGlobal, &Global::auxInToMainReceived, this, &OutputFrame::OnAuxInMain);
    connect(mpGlobal, &Global::auxInToHeadphoneReceived, this, &OutputFrame::OnAuxInHeadphone);
    connect(mpGlobal, &Global::constantLatencyOnOffReceived, this, &OutputFrame::OnConstantLatency);

    mpGlobal->requestMainOutputSource();
    mpGlobal->requestMonitorOutputSource();
    mpGlobal->requestDirectOutputSource();
    mpGlobal->requestSPDIFOutputSource();
    mpGlobal->requestMainOutputVolume();
    mpGlobal->requestMonitorOutputVolume();
    mpGlobal->requestDirectOutputVolume();
    mpGlobal->requestHeadphoneOutputVolume();
    mpGlobal->requestMonitorOutputEQBass();
    mpGlobal->requestMonitorOutputEQMiddle();
    mpGlobal->requestMonitorOutputEQTreble();
    mpGlobal->requestMonitorOutputEQPresence();
    mpGlobal->requestMonitorCabOff();
    mpGlobal->requestMainOutputEQBass();
    mpGlobal->requestMainOutputEQMiddle();
    mpGlobal->requestMainOutputEQTreble();
    mpGlobal->requestMainOutputEQPresence();
    mpGlobal->requestSPDIFOutputVlume();
    mpGlobal->requestPureCab();
    mpGlobal->requestSpace();
    mpGlobal->requestPureCabOnOff();
    mpGlobal->requestHeadphoneSpaceOnOff();
    mpGlobal->requestAuxInToMain();
    mpGlobal->requestAuxInToHeadphone();
    mpGlobal->requestConstantLatencyOnOff();
  }
}

void OutputFrame::deactivate()
{
  if(mpGlobal != nullptr)
  {
    disconnect(mpGlobal, &Global::mainOutputSourceReceived, this, &OutputFrame::OnMainOutputSource);
    disconnect(mpGlobal, &Global::monitorOutputSourceReceived, this, &OutputFrame::OnMonitorOutputSource);
    disconnect(mpGlobal, &Global::directOutputSourceReceived, this, &OutputFrame::OnDirectOutputSource);
    disconnect(mpGlobal, &Global::spdifOutputSourceReceived, this, &OutputFrame::OnSPDIFOutputSource);
    disconnect(mpGlobal, &Global::mainOutputVolumeReceived, this, &OutputFrame::OnMainVolume);
    disconnect(mpGlobal, &Global::monitorOutputVolumeReceived, this, &OutputFrame::OnMonitorVolume);
    disconnect(mpGlobal, &Global::directOutputVolumeReceived, this, &OutputFrame::OnDirectVolume);
    disconnect(mpGlobal, &Global::headphoneOutputVolumeReceived, this, &OutputFrame::OnHeadphoneVolume);
    disconnect(mpGlobal, &Global::monitorOutputEQBassReceived, this, &OutputFrame::OnMonitorOutputEQBass);
    disconnect(mpGlobal, &Global::monitorOutputEQMiddleReceived, this, &OutputFrame::OnMonitorOutputEQMiddle);
    disconnect(mpGlobal, &Global::monitorOutputEQTrebleReceived, this, &OutputFrame::OnMonitorOutputEQTreble);
    disconnect(mpGlobal, &Global::monitorOutputEQPresenceReceived, this, &OutputFrame::OnMonitorOutputEQPresence);
    disconnect(mpGlobal, &Global::monitorCabOffReceived, this, &OutputFrame::OnMonitorCabOff);
    disconnect(mpGlobal, &Global::mainOutputEQBassReceived, this, &OutputFrame::OnMainOutputEQBass);
    disconnect(mpGlobal, &Global::mainOutputEQMiddleReceived, this, &OutputFrame::OnMainOutputEQMiddle);
    disconnect(mpGlobal, &Global::mainOutputEQTrebleReceived, this, &OutputFrame::OnMainOutputEQTreble);
    disconnect(mpGlobal, &Global::mainOutputEQPresenceReceived, this, &OutputFrame::OnMainOutputEQPresence);
    disconnect(mpGlobal, &Global::spdifOutputVolumeReceived, this, &OutputFrame::OnSPDIFVolume);
    disconnect(mpGlobal, &Global::pureCabReceived, this, &OutputFrame::OnPureCabinet);
    disconnect(mpGlobal, &Global::spaceReceived, this, &OutputFrame::OnSpace);
    disconnect(mpGlobal, &Global::pureCabOnOffReceived, this, &OutputFrame::OnPureCabinetOnOff);
    disconnect(mpGlobal, &Global::headphoneSpaceOnOffReceived, this, &OutputFrame::OnHeadphoneSpace);
    disconnect(mpGlobal, &Global::auxInToMainReceived, this, &OutputFrame::OnAuxInMain);
    disconnect(mpGlobal, &Global::auxInToHeadphoneReceived, this, &OutputFrame::OnAuxInHeadphone);
    disconnect(mpGlobal, &Global::constantLatencyOnOffReceived, this, &OutputFrame::OnConstantLatency);
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
  if(page <= ui->lcdDisplay->maxPage() && page >= QToasterLCD::Page1)
  {
    ui->lcdDisplay->setCurrentPage(page);
    ui->bigDials->setCurrentIndex((int) page);
    ui->smallDials->setCurrentIndex((int) page);
    ui->lcdDisplay->setStompName(mPageTitles[page]);
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
    mpGlobal->applySPDIFOutputSource(valueIndex);
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

void OutputFrame::on_monitorOutputEQBassDial_valueChanged(double value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyMonitorOutputEQBass(value);
}

void OutputFrame::on_monitorOutputEQMiddleDial_valueChanged(double value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyMonitorOutputEQMiddle(value);
}

void OutputFrame::on_monitorOutputEQTrebleDial_valueChanged(double value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyMonitorOutputEQTreble(value);
}

void OutputFrame::on_monitorOutputEQPresenceDial_valueChanged(double value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyMonitorOutputEQPresence(value);
}

void OutputFrame::on_monitorCabOffDial_valueChanged(int valueIndex)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyMonitorCabOff(valueIndex != 0);
}

void OutputFrame::on_mainOutputEQBassDial_valueChanged(double value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyMainOutputEQBass(value);
}

void OutputFrame::on_mainOutputEQMiddleDial_valueChanged(double value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyMainOutputEQMiddle(value);
}

void OutputFrame::on_mainOutputEQTrebleDial_valueChanged(double value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyMainOutputEQTreble(value);
}

void OutputFrame::on_mainOutputEQPresenceDial_valueChanged(double value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyMainOutputEQPresence(value);
}

void OutputFrame::on_spdifVolumeDial_valueChanged(int value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applySPDIFOutputVolue(value);
}

void OutputFrame::on_pureCabinetDial_valueChanged(double value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyPureCab(value);
}

void OutputFrame::on_spaceDial_valueChanged(double value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applySpace(value);
}

void OutputFrame::on_spdifOutLinkDial_valueChanged(int valueIndex)
{
}

void OutputFrame::on_pureCabinetOnOffDial_valueChanged(int valueIndex)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyPureCabOnOff(valueIndex != 0);
}

void OutputFrame::on_headphoneSpaceDial_valueChanged(int valueIndex)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyHeadphoneSpaceOnOff(valueIndex != 0);
}

void OutputFrame::on_auxInMainDial_valueChanged(double value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyAuxInToMain(value);
}

void OutputFrame::on_auxInHeadphoneDial_valueChanged(double value)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyAuxInToHeadphone(value);
}

void OutputFrame::on_constantLatencyDial_valueChanged(int valueIndex)
{
  if(mpGlobal != nullptr)
    mpGlobal->applyConstantLatencyOnOff(valueIndex != 0);
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

void OutputFrame::OnSPDIFOutputSource(int valueIndex)
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

void OutputFrame::OnMonitorOutputEQBass(double value)
{
  ui->monitorOutputEQBassDial->setValue(value);
  update();
}

void OutputFrame::OnMonitorOutputEQMiddle(double value)
{
  ui->monitorOutputEQMiddleDial->setValue(value);
  update();
}

void OutputFrame::OnMonitorOutputEQTreble(double value)
{
  ui->monitorOutputEQTrebleDial->setValue(value);
  update();
}

void OutputFrame::OnMonitorOutputEQPresence(double value)
{
  ui->monitorOutputEQPresenceDial->setValue(value);
  update();
}

void OutputFrame::OnMonitorCabOff(int valueIndex)
{
  ui->monitorCabOffDial->setValue(valueIndex);
  update();
}

void OutputFrame::OnMainOutputEQBass(double value)
{
  ui->mainOutputEQBassDial->setValue(value);
  update();
}

void OutputFrame::OnMainOutputEQMiddle(double value)
{
  ui->mainOutputEQMiddleDial->setValue(value);
  update();
}

void OutputFrame::OnMainOutputEQTreble(double value)
{
  ui->mainOutputEQTrebleDial->setValue(value);
  update();
}

void OutputFrame::OnMainOutputEQPresence(double value)
{
  ui->mainOutputEQPresenceDial->setValue(value);
  update();
}

void OutputFrame::OnSPDIFVolume(int value)
{
  ui->spdifVolumeDial->setValue(value);
  update();
}

void OutputFrame::OnPureCabinet(double value)
{
  ui->pureCabinetDial->setValue(value);
  update();
}

void OutputFrame::OnSpace(double value)
{
  ui->spaceDial->setValue(value);
  update();
}

void OutputFrame::OnSPDIFOutLink(int valueIndex)
{
  ui->spdifOutLinkDial->setValue(valueIndex);
  update();
}

void OutputFrame::OnPureCabinetOnOff(int valueIndex)
{
  ui->pureCabinetOnOffDial->setValue(valueIndex);
  update();
}

void OutputFrame::OnHeadphoneSpace(int valueIndex)
{
  ui->headphoneSpaceDial->setValue(valueIndex);
  update();
}

void OutputFrame::OnAuxInMain(double value)
{
  ui->auxInMainDial->setValue(value);
  update();
}

void OutputFrame::OnAuxInHeadphone(double value)
{
  ui->auxInHeadphoneDial->setValue(value);
  update();
}

void OutputFrame::OnConstantLatency(int valueIndex)
{
  ui->constantLatencyDial->setValue(valueIndex);
  update();
}
