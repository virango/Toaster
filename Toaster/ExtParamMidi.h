#ifndef EXTPARAMMIDI_H
#define EXTPARAMMIDI_H

#include "SysExBase.h"
#include "SysExMsgDispatcher.h"


class ExtParamMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
protected:
  static const unsigned int sBrowserView;

  ExtParamMidi();
  ~ExtParamMidi();

  // ISysExConsumer
  void consumeSysExMsg(ByteArray* msg);
  unsigned char getId();

  // parameter
  // browser view
  void midiRequestBrowserView();
  void midiApplyBrowserView(unsigned int rawVal);

  // receive callbacks for derived class
  virtual void midiBrowserViewReceived(unsigned int rawVal) = 0;
};

#endif // EXTPARAMMIDI_H
