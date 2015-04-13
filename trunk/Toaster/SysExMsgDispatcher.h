#ifndef SYSEXMSGDISPATCHER_H
#define SYSEXMSGDISPATCHER_H
#include <list>
#include "Midi.h"
#include "SysExBase.h"

class SysExMsgDispatcher : public Midi::IMidiConsumer, public SysExBase
{
private:
  SysExMsgDispatcher();
  ~SysExMsgDispatcher();

public:
  class ISysExConsumer
  {
  public:
    virtual void consumeSysExMsg(ByteArray* msg) = 0;
    virtual unsigned char getId() = 0;
  };

  static SysExMsgDispatcher& get();

  virtual void consume(ByteArray* msg);
  virtual unsigned char getStatusByte() { return 0xF0; }

  void addConsumer(ISysExConsumer* consumer);
  void removeConsumer(ISysExConsumer* consumer);

private:
  list<ISysExConsumer*> mConsumer;
};

#endif // SYSEXMSGDISPATSCHER_H
