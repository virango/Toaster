#ifndef EQMIDI_H
#define EQMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class EqMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)

  // parameter
  BYTEARRAYDECL(OnOff)
  BYTEARRAYDECL(Bass)
  BYTEARRAYDECL(Middle)
  BYTEARRAYDECL(Treble)
  BYTEARRAYDECL(Presence)

  EqMidi();
  ~EqMidi();

  // ISysExConsumer
  void consumeSysExMsg(ByteArray* msg);
  unsigned char getId();

  // parameter
  // OnOff
  void midiRequestOnOff();
  void midiApplyOnOff(unsigned short rawVal);
  // Bass
  void midiRequestBass();
  void midiApplyBass(unsigned short rawVal);
  // Middle
  void midiRequestMiddle();
  void midiApplyMiddle(unsigned short rawVal);
  // Treble
  void midiRequestTreble();
  void midiApplyTreble(unsigned short rawVal);
  // Presence
  void midiRequestPresence();
  void midiApplyPresence(unsigned short rawVal);

  // receive callbacks for derived class
  virtual void midiOnOffReceived(unsigned short rawVal) = 0;
  virtual void midiBassReceived(unsigned short rawVal) = 0;
  virtual void midiMiddleReceived(unsigned short rawVal) = 0;
  virtual void midiTrebleReceived(unsigned short rawVal) = 0;
  virtual void midiPresenceReceived(unsigned short rawVal) = 0;

  // utility methods
  ByteArray getAddressPage();
};

#endif // EQMIDI_H
