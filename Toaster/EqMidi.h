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

protected:
  EqMidi();
  ~EqMidi();

  // ISysExConsumer
  void consumeSysExMsg(ByteArray* msg);
  unsigned char getId();

  // parameter
  // OnOff
  void midiRequestOnOff();
  void midiApplyOnOff(bool onOff);
  // Bass
  void midiRequestBass();
  void midiApplyBass(double bass);
  // Middle
  void midiRequestMiddle();
  void midiApplyMiddle(double middle);
  // Treble
  void midiRequestTreble();
  void midiApplyTreble(double treble);
  // Presence
  void midiRequestPresence();
  void midiApplyPresence(double presence);

  // utility methods
  ByteArray getAddressPage();
};

#endif // EQMIDI_H
