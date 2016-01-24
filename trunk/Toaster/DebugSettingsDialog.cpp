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
#include "DebugSettingsDialog.h"
#include "ui_DebugSettingsDialog.h"
#include "DebugMidi.h"

DebugSettingsDialog::DebugSettingsDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DebugSettingsDialog)
{
  ui->setupUi(this);
}

DebugSettingsDialog::~DebugSettingsDialog()
{
  delete ui;
}

void DebugSettingsDialog::on_printValuesCheckBox_clicked(bool checked)
{
  DebugMidi::get().mPrintValues = checked;
}
