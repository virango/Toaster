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
#include <QString>
#include "TunerFrame.h"
#include "ui_TunerFrame.h"

TunerFrame::TunerFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TunerFrame)
{
  ui->setupUi(this);
  connect(&mTuner, SIGNAL(noteReceived(QString, QString)), this, SLOT(onTunerNote(QString, QString)));
  connect(&mTunerIndex, SIGNAL(indexReceived(int)), this, SLOT(onTunerIndex(int)));
  connect(&mGlobal, &Global::masterTuneReceived, this, &TunerFrame::onMasterTune);
  connect(&mTuner, &Tuner::muteSignalReceived, this, &TunerFrame::onMute);
}

TunerFrame::~TunerFrame()
{
  delete ui;
}

void TunerFrame::on_masterTuneDial_valueChanged(double value)
{
  mGlobal.applyMasterTune(value);
}

void TunerFrame::on_muteDial_valueChanged(int valueIndex)
{
  ui->toasterTunerLCD->setMuted(valueIndex != 0);
  mTuner.applyMuteSignal(valueIndex != 0);
}

void TunerFrame::onTunerNote(QString note, QString octave)
{
  ui->toasterTunerLCD->setNote(note);
  ui->toasterTunerLCD->setOctave(octave);
}

void TunerFrame::onTunerIndex(int index)
{
  ui->toasterTunerLCD->setIndexPosition(index);
}

void TunerFrame::onMasterTune(double value)
{
  ui->masterTuneDial->setValue(value);
}

void TunerFrame::onMute(bool muted)
{
  ui->muteDial->setValue(muted ? 1 : 0);
}

void TunerFrame::on_toasterTunerLCD_signalMuted(bool muted)
{
  ui->muteDial->setValue(muted ? 1 : 0);
}
