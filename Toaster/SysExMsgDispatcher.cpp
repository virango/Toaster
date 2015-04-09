#include "SysExMsgDispatcher.h"

SysExMsgDispatcher::SysExMsgDispatcher()
{
  Midi::get().addConsumer(this);
}

SysExMsgDispatcher::~SysExMsgDispatcher()
{
  Midi::get().removeConsumer(this);
}

SysExMsgDispatcher& SysExMsgDispatcher::get()
{
  static SysExMsgDispatcher singleton;
  return singleton;
}

void SysExMsgDispatcher::consume(ByteArray* msg)
{
  if(!msg || msg->size() < 8)
    return;

  for(list<ISysExConsumer*>::iterator it = mConsumer.begin(); it != mConsumer.end(); ++it)
  {
    ISysExConsumer* consumer = (*it);
    if(consumer && consumer->getId() == (*msg)[8])
      consumer->consumeSysExMsg(msg);
  }
}

void SysExMsgDispatcher::addConsumer(ISysExConsumer* consumer)
{
  if(consumer)
    mConsumer.push_back(consumer);
}

void SysExMsgDispatcher::removeConsumer(ISysExConsumer* consumer)
{
  if(consumer)
    mConsumer.remove(consumer);
}

