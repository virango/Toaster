#include "DelayMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(DelayMidi, AddressPage,      0x4A)
// parameter
BYTEARRAYDECL(DelayMidi, Type             0x00)
BYTEARRAYDECL(DelayMidi, OnOffCutsTail    0x02)
BYTEARRAYDECL(DelayMidi, Mix              0x03)
BYTEARRAYDECL(DelayMidi, Volume           0x04)
BYTEARRAYDECL(DelayMidi, Time             0x05)
BYTEARRAYDECL(DelayMidi, Ratio            0x06)
BYTEARRAYDECL(DelayMidi, ClockLeft        0x07)
BYTEARRAYDECL(DelayMidi, ClockRight       0x08)
BYTEARRAYDECL(DelayMidi, Feedback         0x09)
BYTEARRAYDECL(DelayMidi, Bandwidth        0x0A)
BYTEARRAYDECL(DelayMidi, CenterFrequency  0x0B)
BYTEARRAYDECL(DelayMidi, Modulation       0x0C)
BYTEARRAYDECL(DelayMidi, OnOffKeepsTail   0x0D)
BYTEARRAYDECL(DelayMidi, Ducking          0x0E)

DelayMidi::DelayMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

DelayMidi::~DelayMidi()
{
}

unsigned char Delay::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void Delay::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = extractRawVal(msg->at(10), msg->at(11));
    const char fct = msg->at(9);
    if(fct == sType[0])
      midiTypeReceived(rawVal);
    if(fct == sOnOffCutsTail[0])
      midiOnOffCutsTailReceived(rawVal);
    if(fct == sMix[0])
      midiMixReceived(rawVal);
    if(fct == sVolume[0])
      midiVolumeReceived(rawVal);
    if(fct == sTime[0])
      midiTimeReceived(rawVal);
    if(fct == sRatio[0])
      midiRatioReceived(rawVal);
    if(fct == sClockLeft[0])
      midiClockLeftReceived(rawVal);
    if(fct == sClockRight[0])
      midiClockRightReceived(rawVal);
    if(fct == sFeedback[0])
      midiFeedbackReceived(rawVal);
    if(fct == sBandwidth[0])
      midiBandwidthReceived(rawVal);
    if(fct == sCenterFrequency[0])
      midiCenterFrequencyReceived(rawVal);
    if(fct == sModulation[0])
      midiModulationReceived(rawVal);
    if(fct == sOnOffKeepsTail[0])
      midiOnOffKeepsTailReceived(rawVal);
    if(fct == sDucking[0])
      midiDuckingReceived(rawVal);
  }
}

void DelayMidi::midiRequestType()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sType));
}

void DelayMidi::midiApplyType(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sType, rawVal));
}

void DelayMidi::midiRequestOnOffCutsTail()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sOnOffCutsTail));
}

void DelayMidi::midiApplyOnOffCutsTail(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sOnOffCutsTail, rawVal));
}

void DelayMidi::midiRequestMix()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMix));
}

void DelayMidi::midiApplyMix(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMix, rawVal));
}

void DelayMidi::midiRequestVolume()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sVolume));
}

void DelayMidi::midiApplyVolume(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sVolume, rawVal));
}

void DelayMidi::midiRequestTime()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sTime));
}

void DelayMidi::midiApplyTime(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sTime, rawVal));
}

void DelayMidi::midiRequestRatio()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sRatio));
}

void DelayMidi::midiApplyRatio(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sRatio, rawVal));
}

void DelayMidi::midiRequestClockLeft()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sClockLeft));
}

void DelayMidi::midiApplyClockLeft(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sClockLeft, rawVal));
}

void DelayMidi::midiRequestClockRight()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sClockRight));
}

void DelayMidi::midiApplyClockRight(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sClockRight, rawVal));
}

void DelayMidi::midiRequestFeedback()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sFeedback));
}

void DelayMidi::midiApplyFeedback(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sFeedback, rawVal));
}

void DelayMidi::midiRequestBandwidth()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sBandwidth));
}

void DelayMidi::midiApplyBandwidth(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sBandwidth, rawVal));
}

void DelayMidi::midiRequestCenterFrequency()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sCenterFrequency));
}

void DelayMidi::midiApplyCenterFrequency(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sCenterFrequency, rawVal));
}

void DelayMidi::midiRequestModulation()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sModulation));
}

void DelayMidi::midiApplyModulation(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sModulation, rawVal));
}

void DelayMidi::midiRequestOnOffKeepsTail()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sOnOffKeepsTail));
}

void DelayMidi::midiApplyOnOffKeepsTail(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sOnOffKeepsTail, rawVal));
}

void DelayMidi::midiRequestDucking()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sDucking));
}

void DelayMidi::midiApplyDucking(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sDucking, rawVal));
}

ByteArray DelayMidi::getAddressPage()
{
  return sAddressPage;
}
