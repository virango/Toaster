#include "ExtParam.h"

ExtParam::ExtParam(QObject *parent)
  : QObject(parent)
{

}

ExtParam::~ExtParam()
{

}

void ExtParam::requestAllValues()
{
  midiRequestBrowserView();
}

void ExtParam::applyBrowserView(unsigned int view)
{
  midiApplyBrowserView(view);
}

// EqMidi
void ExtParam::midiBrowserViewReceived(unsigned int rawVal)
{
  emit browserViewReceived(rawVal);
}

