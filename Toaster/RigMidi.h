#ifndef RIGMIDI_H
#define RIGMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class RigMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(Tempo)
  BYTEARRAYDECL(Volume)
  BYTEARRAYDECL(TempoEnable)

public:
  RigMidi();
  ~RigMidi();

  // ISysExConsumer
  unsigned char getId();
  void consumeSysExMsg(ByteArray* msg);

protected:
  // parameter
  // Tempo
  void midiRequestTempo();
  void midiApplyTempo(unsigned short rawVal);
  // Volume
  void midiRequestVolume();
  void midiApplyVolume(unsigned short rawVal);
  // TempoEnable
  void midiRequestTempoEnable();
  void midiApplyTempoEnable(unsigned short rawVal);

  // receive callbacks for derived class
  virtual void midiTempoReceived(unsigned short rawVal) = 0;
  virtual void midiVolumeReceived(unsigned short rawVal) = 0;
  virtual void midiTempoEnableReceived(unsigned short rawVal) = 0;

  ByteArray getAddressPage();
};

#endif // RIGMIDI_H
