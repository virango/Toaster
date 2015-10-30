#include <QString>
#include "TunerFrame.h"
#include "ui_TunerFrame.h"

TunerFrame::TunerFrame(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TunerFrame)
{
  ui->setupUi(this);
  connect(&mTunerNote, SIGNAL(noteReceived(QString, QString)), this, SLOT(onTunerNote(QString, QString)));
  connect(&mTunerIndex, SIGNAL(indexReceived(int)), this, SLOT(onTunerIndex(int)));
}

TunerFrame::~TunerFrame()
{
  delete ui;
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
