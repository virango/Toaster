#ifndef TUNER_H
#define TUNER_H
#include "TunerMidi.h"

class Tuner : public QObject, public TunerMidi
{
  Q_OBJECT
public:
  explicit Tuner(QObject *parent = 0);

  void requestMuteSignal() { midiRequestMuteSignal(); }


signals:
  void noteReceived(QString note, QString octave);
  void muteSignalReceived(bool muteSignal);

public slots:
  void applyMuteSignal(bool muteSignal) { midiApplyMuteSignal(muteSignal ? 1 : 0); }

protected:
  virtual void midiNoteReceived(unsigned short rawVal);
  virtual void midiMuteSignalReceived(unsigned short rawVal);
};

#endif // TUNER_H
