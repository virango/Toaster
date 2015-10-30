#ifndef TUNERFRAME_H
#define TUNERFRAME_H

#include <QWidget>
#include "TunerNote.h"
#include "TunerIndex.h"

namespace Ui {
  class TunerFrame;
}

class TunerFrame : public QWidget
{
  Q_OBJECT

public:
  explicit TunerFrame(QWidget *parent = 0);
  ~TunerFrame();

private slots:
  void onTunerNote(QString note, QString octave);
  void onTunerIndex(int index);

private:
  Ui::TunerFrame *ui;

  TunerNote mTunerNote;
  TunerIndex mTunerIndex;
};

#endif // TUNERFRAME_H
