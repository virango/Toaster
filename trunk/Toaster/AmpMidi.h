#ifndef AMPMIDI_H
#define AMPMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class AmpMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(OnOff)
  BYTEARRAYDECL(Gain)
  BYTEARRAYDECL(Definition)
  BYTEARRAYDECL(Clarity)
  BYTEARRAYDECL(PowerSagging)
  BYTEARRAYDECL(Pick)
  BYTEARRAYDECL(Compressor)
  BYTEARRAYDECL(TubeShape)
  BYTEARRAYDECL(TubeBias)
  BYTEARRAYDECL(DirectMix)

public:
  AmpMidi();
  ~AmpMidi();
  
  // ISysExConsumer
  unsigned char getId();
  void consumeSysExMsg(ByteArray* msg);
  
protected:
  // parameter
  // OnOff
  void midiRequestOnOff();
  void midiApplyOnOff(unsigned short rawVal);
  // Gain
  void midiRequestGain();
  void midiApplyGain(unsigned short rawVal);
  // Definition
  void midiRequestDefinition();
  void midiApplyDefinition(unsigned short rawVal);
  // Clarity
  void midiRequestClarity();
  void midiApplyClarity(unsigned short rawVal);
  // PowerSagging
  void midiRequestPowerSagging();
  void midiApplyPowerSagging(unsigned short rawVal);
  // Pick
  void midiRequestPick();
  void midiApplyPick(unsigned short rawVal);
  // Compressor
  void midiRequestCompressor();
  void midiApplyCompressor(unsigned short rawVal);
  // TubeShape
  void midiRequestTubeShape();
  void midiApplyTubeShape(unsigned short rawVal);
  // TubeBias
  void midiRequestTubeBias();
  void midiApplyTubeBias(unsigned short rawVal);
  // DirectMix
  void midiRequestDirectMix();
  void midiApplyDirectMix(unsigned short rawVal);
  
  // receive callbacks for derived class
  virtual void midiOnOffReceived(unsigned short rawVal) = 0;
  virtual void midiGainReceived(unsigned short rawVal) = 0;
  virtual void midiDefinitionReceived(unsigned short rawVal) = 0;
  virtual void midiClarityReceived(unsigned short rawVal) = 0;
  virtual void midiPowerSaggingReceived(unsigned short rawVal) = 0;
  virtual void midiPickReceived(unsigned short rawVal) = 0;
  virtual void midiCompressorReceived(unsigned short rawVal) = 0;
  virtual void midiTubeShapeReceived(unsigned short rawVal) = 0;
  virtual void midiTubeBiasReceived(unsigned short rawVal) = 0;
  virtual void midiDirectMixReceived(unsigned short rawVal) = 0;
  
  // utility methods
  ByteArray getAddressPage();
};

#endif // AMPMIDI_H
