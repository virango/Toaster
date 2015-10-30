#ifndef TUNERNOTE_H
#define TUNERNOTE_H
#include "TunerNoteMidi.h"

class TunerNote : public QObject, public TunerNoteMidi
{
  Q_OBJECT
public:
  explicit TunerNote(QObject *parent = 0);

signals:
  void noteReceived(QString note, QString octave);

protected:
  virtual void midiNoteReceived(unsigned short rawVal);
};

#endif // TUNERNOTE_H
