#ifndef DEBUGMIDI_H
#define DEBUGMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class DebugMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
public:
  // ISysExConsumer
  unsigned char getId() { return 0xFF; }
  void consumeSysExMsg(ByteArray* msg);

  static DebugMidi& get() { return mSingleton; }
protected:
  DebugMidi();
  ~DebugMidi();

  static DebugMidi mSingleton;
};

#endif // DEBUGMIDI_H
