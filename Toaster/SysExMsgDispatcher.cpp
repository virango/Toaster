/*  This file is part of Toaster, the editor and remote control for Kemper profiling amplifier.
*
*   Copyright (C) 2016  Thomas Langer
*
*   Toaster is free software: you can redistribute it and/or modify it under the terms of the
*   GNU General Public License as published by the Free Software Foundation, either version 3
*   of the License, or (at your option) any later version.
*
*   Toaster is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
*   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*   See the GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along with Toaster.
*   If not, see <http://www.gnu.org/licenses/>.
*/
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
  if(msg && msg->size() >= 8)
  {
    if(sHeader[0] == (*msg)[0]  && sHeader[1] == (*msg)[1] && sHeader[2] == (*msg)[2] && sHeader[3] == (*msg)[3])
    {
      for(list<ISysExConsumer*>::iterator it = mConsumer.begin(); it != mConsumer.end(); ++it)
      {
        ISysExConsumer* consumer = (*it);
        if((sExtParamChange[0] == (*msg)[6] && consumer->getId() == (*msg)[6]))   // special handling for extended parameter function
          consumer->consumeSysExMsg(msg);
        else if(consumer && (consumer->getId() == (*msg)[8] || consumer->getId() == 0xFF))
          consumer->consumeSysExMsg(msg);
      }
    }
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

