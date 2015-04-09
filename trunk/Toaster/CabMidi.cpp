#include "CabMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(CabMidi, AddressPage,     0x0C)
// parameter
BYTEARRAYDEF(CabMidi, OnOff            0x02)
BYTEARRAYDEF(CabMidi, Volume           0x03)
BYTEARRAYDEF(CabMidi, HighShift        0x04)
BYTEARRAYDEF(CabMidi, LowShift         0x05)
BYTEARRAYDEF(CabMidi, Character        0x06)

CabMidi::CabMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

CabMidi::~CabMidi()
{
}

unsigned char CabMidi::getId()
{
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if(addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void CabMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned short rawVal = msg->at(10) << 8 | msg->at(11);
    const char fct = msg->at(9);
    if(fct == sOnOff[0])
      midiOnOffReceived(rawVal);
    else if(fct == sVolume[0])
      midiVolumeReceived(rawVal);
    else if(fct == sHighShift[0])
      midiHighShiftReceived(rawVal);
    else if(fct == sLowShift[0])
      midiLowShiftReceived(rawVal);
    else if(fct == sCharacter[0])
      midiCharacterReceived(rawVal);  
  }
}

void CabMidi::midiRequestOnOff()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sOnOff));
}

void CabMidi::midiApplyOnOff(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sOnOff, rawVal));
}

void CabMidi::midiRequestVolume()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sVolume));
}

void CabMidi::midiApplyVolume(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sVolume, rawVal));
}

void CabMidi::midiRequestHighShift()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sHighShift));
}

void CabMidi::midiApplyHighShift(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sHighShift, rawVal));
}

void CabMidi::midiRequestLowShift()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sLowShift));
}

void CabMidi::midiApplyLowShift(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sLowShift, rawVal));
}

void CabMidi::midiRequestCharacter()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sCharacter));
}

void CabMidi::midiApplyCharacter(unsigned short rawVal)
{
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sCharacter, rawVal));
}

ByteArray CabMidi::getAddressPage()
{
  return sAddressPage;
}
