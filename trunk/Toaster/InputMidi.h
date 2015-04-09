#ifndef INPUTMIDI_H
#define INPUTMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class InputMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(NoiseGate)
  BYTEARRAYDECL(CleanSense)
  BYTEARRAYDECL(DistortionSense)

public:
  InputMidi();
  ~InputMidi();

  // ISysExConsumer
  void consumeSysExMsg(ByteArray* msg);
  unsigned char getId();


protected:
  // parameter
  // Noise Gate
  void midiRequestNoiseGate();
  void midiApplyNoiseGate(unsigned short rawVal);
  // Clean Sense
  void midiRequestCleanSense();
  void midiApplyCleanSense(unsigned short rawVal);
  // Distortion Sense
  void midiRequestDistortionSense();
  void midiApplyDistortionSense(unsigned short rawVal);


  // receive callbacks for derived class
  virtual void midiNoiseGateReceived(unsigned short rawVal) = 0;
  virtual void midiCleanSenseReceived(unsigned short rawVal) = 0;
  virtual void midiDistortionSenseReceived(unsigned short rawVal) = 0;

  // utility methods
  ByteArray getAddressPage();
};

#endif // INPUTMIDI_H
