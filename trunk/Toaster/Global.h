#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include "SysExMsgDispatcher.h"
#include "GlobalMidi.h"

class Global : public QObject, public GlobalMidi, public SysExMsgDispatcher::ISysExConsumer
{
  Q_OBJECT
public:
  Global();
  ~Global();

  void consumeSysExMsg(ByteArray* msg);
  unsigned char getId();

  void requestValues();
};

#endif // GLOBAL_H
