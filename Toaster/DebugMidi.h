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
#ifndef DEBUGMIDI_H
#define DEBUGMIDI_H
#include <QString>
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class DebugMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer
{
public:
  // ISysExConsumer
  unsigned char getId() { return 0xFF; }
  void consumeSysExMsg(const ByteArray& msg);

  static DebugMidi& get() { return mSingleton; }

  void debugRequestStringParam(unsigned char addressPage, unsigned char parameter, unsigned short val);

  void debugScanRequest(unsigned char adddressPage, unsigned char minParam, unsigned char maxParam);

  void debugRequestExtParam(unsigned int param);

  void debugRequestExtStringParam(unsigned int param);

  void debugSendSingleParam(const ByteArray& addressPage, const ByteArray& param, const ByteArray& value);

  void debugSendStringParam(const ByteArray& addressPage, const ByteArray& param, const ByteArray& value);

  void debugSendExtParam(unsigned int param, unsigned int value);

  void debugSendReserveFct7E(const ByteArray& addressPage, const ByteArray& param, const ByteArray& value);

  void debugSendReserveFct7F(const ByteArray& addressPage, const ByteArray& param, const ByteArray& value);

  void debugWriteStringValues(const ByteArray& msg);

  void debugPrintValues(const ByteArray& msg);

  bool mPrintValues;

  bool mWriteStringValues;

  QString mRaw2ValFileName;
  QString mVal2RawFileName;
protected:
  DebugMidi();
  ~DebugMidi();

  static DebugMidi mSingleton;
};

#endif // DEBUGMIDI_H
