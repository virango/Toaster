#ifndef CABMIDI_H
#define CABMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class CabMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(OnOff)
  BYTEARRAYDECL(Volume)
  BYTEARRAYDECL(HighShift)
  BYTEARRAYDECL(LowShift)
  BYTEARRAYDECL(Character)

public:
  CabMidi();
  ~CabMidi();
  
  // ISysExConsumer
  unsigned char getId();
  void consumeSysExMsg(ByteArray* msg);

protected:
  // parameter
  // OnOff 
  void midiRequestOnOff();
  void midiApplyOnOff(unsigned short rawVal);
  // Volume 
  void midiRequestVolume();
  void midiApplyVolume(unsigned short rawVal);
  // HighShift 
  void midiRequestHighShift();
  void midiApplyHighShift(unsigned short rawVal);
  // LowShift 
  void midiRequestLowShift();
  void midiApplyLowShift(unsigned short rawVal);
  // Character 
  void midiRequestCharacter();
  void midiApplyCharacter(unsigned short rawVal);
  
  // receive callbacks for derived class
  virtual void midiOnOffReceived(unsigned short rawVal) = 0;
  virtual void midiVolumeReceived(unsigned short rawVal) = 0;
  virtual void midiHighShiftReceived(unsigned short rawVal) = 0;
  virtual void midiLowShiftReceived(unsigned short rawVal) = 0;
  virtual void midiCharacterReceived(unsigned short rawVal) = 0;
  
  // utility methods
  ByteArray getAddressPage();
};

#endif // CABMIDI_H
