#ifndef DELAYMIDI_H
#define DELAYMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class DelayMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(Type)
  BYTEARRAYDECL(OnOffCutsTail)
  BYTEARRAYDECL(Mix)
  BYTEARRAYDECL(Volume)
  BYTEARRAYDECL(Time)
  BYTEARRAYDECL(Ratio)
  BYTEARRAYDECL(ClockLeft)
  BYTEARRAYDECL(ClockRight)
  BYTEARRAYDECL(Feedback)
  BYTEARRAYDECL(Bandwidth)
  BYTEARRAYDECL(CenterFrequency)
  BYTEARRAYDECL(Modulation)
  BYTEARRAYDECL(OnOffKeepsTail)
  BYTEARRAYDECL(Ducking)

public:
  DelayMidi();
  ~DelayMidi();

  unsigned char getId();
  void consumeSysExMsg(ByteArray* msg);

protected:
  // parameter
  // Type
  void midiRequestType();
  void midiApplyType(unsigned short rawVal);
  // OnOffCutsTail
  void midiRequestOnOffCutsTail();
  void midiApplyOnOffCutsTail(unsigned short rawVal);
  // Mix
  void midiRequestMix();
  void midiApplyMix(unsigned short rawVal);
  // Volume
  void midiRequestVolume();
  void midiApplyVolume(unsigned short rawVal);
  // Time
  void midiRequestTime();
  void midiApplyTime(unsigned short rawVal);
  // Ratio
  void midiRequestRatio();
  void midiApplyRatio(unsigned short rawVal);
  // ClockLeft
  void midiRequestClockLeft();
  void midiApplyClockLeft(unsigned short rawVal);
  // ClockRight
  void midiRequestClockRight();
  void midiApplyClockRight(unsigned short rawVal);
  // Feedback
  void midiRequestFeedback();
  void midiApplyFeedback(unsigned short rawVal);
  // Bandwidth
  void midiRequestBandwidth();
  void midiApplyBandwidth(unsigned short rawVal);
  // CenterFrequency
  void midiRequestCenterFrequency();
  void midiApplyCenterFrequency(unsigned short rawVal);
  // Modulation
  void midiRequestModulation();
  void midiApplyModulation(unsigned short rawVal);
  // OnOffKeepsTail
  void midiRequestOnOffKeepsTail();
  void midiApplyOnOffKeepsTail(unsigned short rawVal);
  // Ducking
  void midiRequestDucking();
  void midiApplyDucking(unsigned short rawVal);

  // receive callbacks for derived class
  virtual void midiTypeReceived(unsigned short rawVal) = 0;
  virtual void midiOnOffCutsTailReceived(unsigned short rawVal) = 0;
  virtual void midiMixReceived(unsigned short rawVal) = 0;
  virtual void midiVolumeReceived(unsigned short rawVal) = 0;
  virtual void midiTimeReceived(unsigned short rawVal) = 0;
  virtual void midiRatioReceived(unsigned short rawVal) = 0;
  virtual void midiClockLeftReceived(unsigned short rawVal) = 0;
  virtual void midiClockRightReceived(unsigned short rawVal) = 0;
  virtual void midiFeedbackReceived(unsigned short rawVal) = 0;
  virtual void midiBandwidthReceived(unsigned short rawVal) = 0;
  virtual void midiCenterFrequencyReceived(unsigned short rawVal) = 0;
  virtual void midiModulationReceived(unsigned short rawVal) = 0;
  virtual void midiOnOffKeepsTailReceived(unsigned short rawVal) = 0;
  virtual void midiDuckingReceived(unsigned short rawVal) = 0;

  // utility
  ByteArray getAddressPage();
};

#endif // DELAYMIDI_H
