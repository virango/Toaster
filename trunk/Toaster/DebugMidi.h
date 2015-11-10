#ifndef DEBUGMIDI_H
#define DEBUGMIDI_H
#include <QString>
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class DebugMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
public:
  // ISysExConsumer
  unsigned char getId() { return 0xFF; }
  void consumeSysExMsg(ByteArray* msg);

  static DebugMidi& get() { return mSingleton; }

  void debugRequestStringParam(unsigned char addressPage, unsigned char parameter, unsigned short val);

  void debugScanRequest(unsigned char adddressPage, unsigned char minParam, unsigned char maxParam);

  void debugRequestExtParam(unsigned int param);

  void debugRequestExtStringParam(unsigned int param);

  void debugSendSingleParam(ByteArray addressPage, ByteArray param, ByteArray value);

  void debugSendStringParam(ByteArray addressPage, ByteArray param, ByteArray value);

  void debugSendExtParam(unsigned int param, unsigned int value);

  void debugSendReserveFct7E(ByteArray addressPage, ByteArray param, ByteArray value);

  void debugWriteStringValues(ByteArray* msg);

  void debugPrintValues(ByteArray* msg);

  bool mPrintValues;

  bool mWriteStringValues;

  QString mRaw2ValFileName;
  QString mVal2RawFileName;
protected:
  DebugMidi();
  ~DebugMidi();

  static DebugMidi mSingleton;
};

#endif // DEBUGMIDI_H
