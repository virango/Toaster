#ifndef REVERB_H
#define REVERB_H

#include <QObject>
#include "SysExMsgDispatcher.h"
#include "ReverbMidi.h"

class Reverb : public QObject, public ReverbMidi, public SysExMsgDispatcher::ISysExConsumer
{
  Q_OBJECT
public:
  Reverb();
  ~Reverb();

  void consumeSysExMsg(ByteArray* msg);
  unsigned char getId();

  void requestValues();
};

#endif // REVERB_H
