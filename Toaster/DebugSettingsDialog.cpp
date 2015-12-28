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
