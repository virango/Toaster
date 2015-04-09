#ifndef STOMPMIDI_H
#define STOMPMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class StompMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPageA)
  BYTEARRAYDECL(AddressPageB)
  BYTEARRAYDECL(AddressPageC)
  BYTEARRAYDECL(AddressPageD)
  BYTEARRAYDECL(AddressPageX)
  BYTEARRAYDECL(AddressPageMOD)
  // parameter
  BYTEARRAYDECL(Type)
  BYTEARRAYDECL(OnOff)

public:
  enum Instance
  {
    A,
    B,
    C,
    D,
    X,
    MOD
  };

protected:
  StompMidi(Instance instance);
  ~StompMidi();

  // ISysExConsumer
  void consumeSysExMsg(ByteArray* msg);
  unsigned char getId();

  // parameter
  // Type
  void midiRequestType();
  void midiApplyType(unsigned short rawVal);
  // OnOff
  void midiRequestOnOff();
  void midiApplyOnOff(unsigned short rawVal);
  
  // receive callbacks for derived class
  virtual void midiOnOffReceived(unsigned short rawVal) = 0;
  virtual void midiTypeReceived(unsigned short rawVal) = 0;
  
  // utility methods
  ByteArray getAddressPage();
protected:
  Instance mInstance;
};

#endif // STOMPMIDI_H
