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

ByteArray EqMidi::getAddressPage()
{
  return sAddressPage;
}


void EqMidi::getOnOff()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sOnOff));
}

void EqMidi::setOnOff(bool onOff)
{
  ByteArray val = onOff ? sOn : sOff;
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sOnOff, val));
}

void EqMidi::getBass()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sBass));
}

void EqMidi::setBass(double bass)
{
  unsigned short rawVal = ((bass + 5.0) * 0x8000) / 10;
  ByteArray val;
  val.push_back(rawVal >> 8);
  val.push_back(rawVal & 0xFF);
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sBass, val));
}

void EqMidi::getMiddle()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sMiddle));
}

void EqMidi::setMiddle(double middle)
{
  unsigned short rawVal = ((middle + 5.0) * 0x8000) / 10;
  ByteArray val;
  val.push_back(rawVal >> 8);
  val.push_back(rawVal & 0xFF);
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMiddle, val));
}

void EqMidi::getTreble()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sTreble));
}

void EqMidi::setTreble(double treble)
{
  unsigned short rawVal = ((treble + 5.0) * 0x8000) / 10;
  ByteArray val;
  val.push_back(rawVal >> 8);
  val.push_back(rawVal & 0xFF);
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sTreble, val));
}

void EqMidi::getPresence()
{
  Midi::get().sendCmd(createSingleParamGetCmd(getAddressPage(), sPresence));
}

void EqMidi::setPresence(double presence)
{
  unsigned short rawVal = ((presence + 5.0) * 0x8000) / 10;
  ByteArray val;
  val.push_back(rawVal >> 8);
  val.push_back(rawVal & 0xFF);
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sPresence, val));
}
