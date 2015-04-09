#ifndef RIG_H
#define RIG_H

#include <QObject>
#include "SysExMsgDispatcher.h"
#include "RigMidi.h"

class Rig : public QObject, public RigMidi, public SysExMsgDispatcher::ISysExConsumer
{
  Q_OBJECT
public:
  Rig();
  ~Rig();

  void consumeSysExMsg(ByteArray* msg);
  unsigned char getId();

  void requestValues();
};

#endif // RIG_H
