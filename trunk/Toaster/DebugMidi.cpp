#include <QDebug>
#include "DebugMidi.h"

DebugMidi DebugMidi::mSingleton;

DebugMidi::DebugMidi()
{
  SysExMsgDispatcher::get().addConsumer(this);
}

DebugMidi::~DebugMidi()
{

}

void DebugMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 12)
  {
    unsigned int rawVal = -1;

    const char mod = msg->at(8);
    const char param = msg->at(9);
    const char fct = msg->at(6);
    if(fct == sSingleParamChange[0])
      rawVal = extractRawVal(msg->at(10), msg->at(11));
    else if(fct == sExtParamChange[0])
      rawVal = extractRawVal(msg->at(10), msg->at(11), msg->at(12), msg->at(13), msg->at(14));

    if(mod != 0x7c)
    {
      qDebug() << "Message size "  <<  QString::number(msg->size())
               << ", function: "   <<  QString::number(fct, 16)
               << ", module: "     <<  QString::number(mod, 16)
               << ", parameter: "  <<  QString::number(param, 16)
               << ", value: "      <<  QString::number(rawVal);
    }
  }
}

