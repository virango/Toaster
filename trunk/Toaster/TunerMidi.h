#ifndef TUNERMIDI_H
#define TUNERMIDI_H

#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class TunerMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(MuteSignal)
  BYTEARRAYDECL(Note)

  TunerMidi();
  ~TunerMidi();

  void midiRequestMuteSignal();
  void midiApplyMuteSignal(unsigned short rawVal);

  // ISysExConsumer
  unsigned char getId();
  void consumeSysExMsg(ByteArray* msg);

  // receive callbacks for derived class
  virtual void midiNoteReceived(unsigned short rawVal) = 0;
  virtual void midiMuteSignalReceived(unsigned short rawVal) = 0;

  // utility methods
  ByteArray getAddressPage();
};

#endif // TUNERMIDI_H
