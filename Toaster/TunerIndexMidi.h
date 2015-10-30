#ifndef TUNERINDEXMIDI_H
#define TUNERINDEXMIDI_H

#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class TunerIndexMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(Index)

  TunerIndexMidi();
  ~TunerIndexMidi();

  // ISysExConsumer
  unsigned char getId();
  void consumeSysExMsg(ByteArray* msg);

  // receive callbacks for derived class
  virtual void midiIndexReceived(unsigned short rawVal) = 0;

  // utility methods
  ByteArray getAddressPage();
};

#endif // TUNERINDEXMIDI_H
