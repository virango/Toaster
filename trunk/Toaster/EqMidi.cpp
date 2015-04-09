#include "EqMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(EqMidi, AddressPage,     0x0B)

// parameter
BYTEARRAYDEF(EqMidi, OnOff,          0x02)
BYTEARRAYDEF(EqMidi, Bass,           0x04)
BYTEARRAYDEF(EqMidi, Middle,         0x05)
BYTEARRAYDEF(EqMidi, Treble,         0x06)
BYTEARRAYDEF(EqMidi, Presence,       0x07)

EqMidi::EqMidi()
{

}

EqMidi::~EqMidi()
{

}

unsigned char EqMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void EqMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = extractRawVal(msg->at(10), msg->at(11));
    const char fct = msg->at(9);
    if(fct == sOnOff[0])
      midiOnOffReceived(rawVal);
    else if(fct == sBass[0])
      midiBassReceived(rawVal);
    else if(fct == sMiddle[0])
      midiMiddleReceived(rawVal);
    else if(fct == sTreble[0])
      midiTrebleReceived(rawVal);
    else if(fct == sPresence[0])
      midiPresenceReceived(rawVal);
  }
}

void EqMidi::midiRequestOnOff()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sOnOff));
}

void EqMidi::midiApplyOnOff(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sOnOff, rawVal));
}

void EqMidi::midiRequestBass()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sBass));
}

void EqMidi::midiApplyBass(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sBass, rawVal));
}

void EqMidi::midiRequestMiddle()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMiddle));
}

void EqMidi::midiApplyMiddle(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMiddle, rawVal));
}

void EqMidi::midiRequestTreble()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sTreble));
}

void EqMidi::midiApplyTreble(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sTreble, rawVal));
}

void EqMidi::midiRequestPresence()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sPresence));
}

void EqMidi::midiApplyPresence(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sPresence, rawVal));
}

ByteArray EqMidi::getAddressPage()
{
  return sAddressPage;
}

