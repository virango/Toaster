#ifndef TUNERFRAME_H
#define TUNERFRAME_H

#include <QWidget>
#include "Tuner.h"
#include "TunerIndex.h"
#include "Global.h"

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
  void on_masterTuneDial_valueChanged(double value);
  void on_muteDial_valueChanged(int valueIndex);

  void onTunerNote(QString note, QString octave);
  void onTunerIndex(int index);
  void onMasterTune(double value);
  void onMute(bool muted);

  void on_toasterTunerLCD_signalMuted(bool muted);

private:
  Ui::TunerFrame *ui;

  Tuner mTuner;
  TunerIndex mTunerIndex;
  Global mGlobal;
};

#endif // TUNERFRAME_H
