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
#include "DebugCreateStringValuesDialog.h"
#include "ui_DebugCreateStringValuesDialog.h"
#include "DebugMidi.h"

DebugCreateStringValuesDialog::DebugCreateStringValuesDialog(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::DebugCreateStringValuesDialog)
  , mAdressPage(0)
  , mParameter(0)
  , mLowerRange(0)
  , mUpperRange(0x3FFF)
  , mCurrValue(0)
  , mTimer(NULL)
{
  ui->setupUi(this);

  ui->lowerRangeEdit->setValidator(new QIntValidator(0, 0x3FFF, this));
  ui->upperRangeEdit->setValidator(new QIntValidator(0, 0x3FFF, this));

  ui->apEdit->setText(QString::number(mAdressPage, 16));
  ui->paramEdit->setText(QString::number(mParameter, 16));
  ui->lowerRangeEdit->setText(QString::number(mLowerRange));
  ui->upperRangeEdit->setText(QString::number(mUpperRange));

  ui->raw2valFileEdit->setText("raw2val.log");
  ui->val2rawFileEdit->setText("val2raw.log");
}

DebugCreateStringValuesDialog::~DebugCreateStringValuesDialog()
{
  delete ui;
}

void DebugCreateStringValuesDialog::on_raw2ValFileButton_clicked()
{
  QString fileName = QFileDialog::getSaveFileName(this);
  ui->raw2valFileEdit->setText(fileName);
}

void DebugCreateStringValuesDialog::on_val2rawFileButton_clicked()
{
  QString fileName = QFileDialog::getSaveFileName(this);
  ui->val2rawFileEdit->setText(fileName);
}

void DebugCreateStringValuesDialog::on_startButton_clicked()
{
  if(!ui->apEdit->text().isEmpty() && !ui->paramEdit->text().isEmpty())
  {
    bool ok;
    mAdressPage = ui->apEdit->text().toUShort(&ok, 16);
    mParameter = ui->paramEdit->text().toUShort(&ok, 16);

    if(!ui->lowerRangeEdit->text().isEmpty())
      mLowerRange = ui->lowerRangeEdit->text().toInt();

    if(!ui->upperRangeEdit->text().isEmpty())
      mUpperRange = ui->upperRangeEdit->text().toInt();

    if(mLowerRange <= mUpperRange && !ui->raw2valFileEdit->text().isEmpty() && !ui->val2rawFileEdit->text().isEmpty())
    {
      DebugMidi::get().mRaw2ValFileName = ui->raw2valFileEdit->text();
      DebugMidi::get().mVal2RawFileName = ui->val2rawFileEdit->text();
      DebugMidi::get().mWriteStringValues = true;
      mCurrValue = mLowerRange;
      ui->progressBar->setMinimum(mLowerRange);
      ui->progressBar->setMaximum(mUpperRange);
      ui->progressBar->setValue(mCurrValue);

      mTimer = new QTimer(this);
      mTimer->setSingleShot(false);
      connect(mTimer, SIGNAL(timeout()), this, SLOT(onTimer()));
      mTimer->start(25);
    }
  }
}

void DebugCreateStringValuesDialog::on_closeButton_clicked()
{
  if(mTimer)
    mTimer->stop();

  DebugMidi::get().mWriteStringValues = false;
  close();
}

void DebugCreateStringValuesDialog::onTimer()
{
  if(mCurrValue <= mUpperRange)
  {
    DebugMidi::get().debugRequestStringParam(mAdressPage, mParameter, mCurrValue);
    ui->progressBar->setValue(mCurrValue);
    mCurrValue++;
  }
  else if(mTimer)
  {
    mTimer->stop();
    DebugMidi::get().mWriteStringValues = false;
  }

}


