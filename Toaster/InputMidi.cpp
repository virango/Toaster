#include "InputMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(InputMidi, AddressPage,     0x09)
// parameter
BYTEARRAYDEF(InputMidi, NoiseGate,       0x03)
BYTEARRAYDEF(InputMidi, CleanSense,      0x04)
BYTEARRAYDEF(InputMidi, DistortionSense, 0x05)

InputMidi::InputMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

InputMidi::~InputMidi()
{
}

ByteArray InputMidi::getAddressPage()
{
  return sAddressPage;
}

void InputMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = msg->at(10) << 8 | msg->at(11);
    const char fct = msg->at(9);
    if(fct == sNoiseGate[0])
      midiNoiseGateReceived(rawVal);
    else if(fct == sCleanSense[0])
      midiCleanSenseReceived(rawVal);
    else if(fct == sDistortionSense[0])
      midiDistortionSenseReceived(rawVal);
  }
}

unsigned char InputMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void InputMidi::midiRequestNoiseGate()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sNoiseGate));
}

void InputMidi::midiApplyNoiseGate(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sNoiseGate, rawVal));
}

void InputMidi::midiRequestCleanSense()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sCleanSense));
}

void InputMidi::midiApplyCleanSense(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sCleanSense, rawVal));
}

void InputMidi::midiRequestDistortionSense()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sDistortionSense));
}

void InputMidi::midiApplyDistortionSense(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sDistortionSense, rawVal));
}
