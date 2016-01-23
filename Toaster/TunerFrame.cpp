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
