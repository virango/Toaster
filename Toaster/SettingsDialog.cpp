#include <QFileDialog>
#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include "Settings.h"
#include "Midi.h"
#include "DebugMidi.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SettingsDialog)
{
  ui->setupUi(this);
  init();
}

SettingsDialog::~SettingsDialog()
{
  delete ui;
}

void SettingsDialog::init()
{
  ui->inputPortComboBox->addItems(Midi::get().getInPorts());
  ui->outputPortComboBox->addItems(Midi::get().getOutPorts());
  ui->inputPortComboBox->setCurrentText(Settings::get().getMidiInPort());
  ui->outputPortComboBox->setCurrentText(Settings::get().getMidiOutPort());
}

void SettingsDialog::on_buttonBox_accepted()
{
  Settings::get().setMidiInPort(ui->inputPortComboBox->currentText());
  Settings::get().setMidiOutPort(ui->outputPortComboBox->currentText());
}

void SettingsDialog::on_printValuesCheckBox_clicked(bool checked)
{
  DebugMidi::get().mPrintValues = checked;
}

void SettingsDialog::on_createValueMapCheckBox_clicked(bool checked)
{
  DebugMidi::get().mWriteStringValues = checked;
}


void SettingsDialog::on_fileEdit_textChanged(const QString& fileName)
{
  DebugMidi::get().mWriteFileName = fileName;
}

void SettingsDialog::on_fileButton_clicked()
{
   QString fileName = QFileDialog::getSaveFileName(this);
   ui->fileEdit->setText(fileName);
}
