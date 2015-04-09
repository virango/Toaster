#ifndef DELAY_H
#define DELAY_H

#include <QObject>
#include "SysExMsgDispatcher.h"
#include "DelayMidi.h"

class Delay : public QObject, public DelayMidi, public SysExMsgDispatcher::ISysExConsumer
{
  Q_OBJECT
public:
  Delay();
  ~Delay();

  void consumeSysExMsg(ByteArray* msg);
  unsigned char getId();

  void requestValues();
};

#endif // DELAY_H
