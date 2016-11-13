/*  This file is part of Toaster, the editor and remote control for Kemper profiling amplifier.
*
*   Copyright (C) 2016  Thomas Langer
*
*   Toaster is free software: you can redistribute it and/or modify it under the terms of the
*   GNU General Public License as published by the Free Software Foundation, either version 3
*   of the License, or (at your option) any later version.
*
*   Toaster is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
*   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*   See the GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along with Toaster.
*   If not, see <http://www.gnu.org/licenses/>.
*/
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
  if(ui != nullptr)
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

