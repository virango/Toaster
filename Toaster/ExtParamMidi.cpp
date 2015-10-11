#include "ExtParamMidi.h"
#include "Midi.h"

const unsigned int ExtParamMidi::sBrowserView = 0x1863c;

ExtParamMidi::ExtParamMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

ExtParamMidi::~ExtParamMidi()
{
  //SysExMsgDispatcher::get().removeConsumer(this);
}

unsigned char ExtParamMidi::getId()
{
  return sExtParamChange[0];
}

void ExtParamMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 19)
  {
    unsigned int param = extractRawVal(ByteArray(msg->begin() + 9, msg->end()));
    unsigned int rawVal = extractRawVal(ByteArray(msg->begin() + 14, msg->end()));
    if(param == sBrowserView)
      midiBrowserViewReceived(rawVal);
  }
}

void ExtParamMidi::midiRequestBrowserView()
{
  Midi::get().sendCmd(createExtParamGetCmd(sBrowserView));
}

void ExtParamMidi::midiApplyBrowserView(unsigned int rawVal)
{
  Midi::get().sendCmd(createExtParamSetCmd(sBrowserView, rawVal));
}
