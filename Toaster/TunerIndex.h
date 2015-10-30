#ifndef TUNERINDEX_H
#define TUNERINDEX_H
#include "TunerIndexMidi.h"

class TunerIndex : public QObject, public TunerIndexMidi
{
  Q_OBJECT
public:
  explicit TunerIndex(QObject *parent = 0);

signals:
  void indexReceived(int index);

protected:
  virtual void midiIndexReceived(unsigned short rawVal);
};

#endif // TUNERINDEX_H
