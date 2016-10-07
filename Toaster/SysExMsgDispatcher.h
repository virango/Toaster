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
#ifndef SYSEXMSGDISPATCHER_H
#define SYSEXMSGDISPATCHER_H
#include <list>
#include "Midi.h"
#include "SysExBase.h"

class SysExMsgDispatcher : public IMidiConsumer, public SysExBase
{
private:
  SysExMsgDispatcher();
  ~SysExMsgDispatcher();

public:
  class ISysExConsumer
  {
  public:
    virtual void consumeSysExMsg(const ByteArray& msg) = 0;
    virtual unsigned char getId() = 0;
  };

  static SysExMsgDispatcher& get();

  void consume(const ByteArray& msg) override;
  unsigned char getStatusByte() override { return 0xF0; }

  void addConsumer(ISysExConsumer* consumer);
  void removeConsumer(ISysExConsumer* consumer);

private:
  QList<ISysExConsumer*> mConsumer;
};

#endif // SYSEXMSGDISPATSCHER_H
