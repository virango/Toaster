#ifndef TUNERNOTEMIDI_H
#define TUNERNOTEMIDI_H

#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class TunerNoteMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(Note)

  TunerNoteMidi();
  ~TunerNoteMidi();

  // ISysExConsumer
  unsigned char getId();
  void consumeSysExMsg(ByteArray* msg);

  // receive callbacks for derived class
  virtual void midiNoteReceived(unsigned short rawVal) = 0;

  // utility methods
  ByteArray getAddressPage();
};

#endif // TUNERNOTEMIDI_H
