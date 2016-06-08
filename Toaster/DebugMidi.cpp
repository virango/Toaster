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
#include <QDebug>
#include <QFile>
#include "DebugMidi.h"
#include "Settings.h"

DebugMidi DebugMidi::mSingleton;

DebugMidi::DebugMidi()
  :mPrintValues(Settings::get().getDebuggerActive())
{
  SysExMsgDispatcher::get().addConsumer(this);
}

DebugMidi::~DebugMidi()
{

}

void DebugMidi::consumeSysExMsg(ByteArray* msg)
{
  if(msg && msg->size() >= 10)  // set to 10 to receive ack msgs (fct==0x7e, ap==0x7f)
  {
    if(mPrintValues)
      debugPrintValues(msg);

    if(mWriteStringValues)
      debugWriteStringValues(msg);
  }
}

void DebugMidi::debugWriteStringValues(ByteArray* msg)
{
#if 0
  QString strVal;
  static unsigned short val1 = 0;
  static unsigned short val2 = 0;
  static QString lastVal("");

  for(int i = 12; (i < msg->size() && msg->at(i) != 0); ++i)
    strVal.append(msg->at(i));
  qDebug() << QString::number(val2) << strVal;

  QFile outFile1(mRaw2ValFileName);
  QFile outFile2(mVal2RawFileName);
  outFile1.open(QIODevice::WriteOnly | QIODevice::Append);
  outFile2.open(QIODevice::WriteOnly | QIODevice::Append);

  QTextStream textStream1(&outFile1);
  QTextStream textStream2(&outFile2);
  textStream1 << strVal  << ",";

  if(lastVal != strVal)
  {
    static unsigned short cnt = 0;
    lastVal = strVal;
    textStream2 << val2  << ",";
    cnt++;
    if(cnt == 100)
    {
      textStream2 << endl;
      cnt = 0;
    }
  }
  val2++;

  val1++;
  if(val1 == 100)
  {
    textStream1 << endl;
    val1 = 0;
  }
#else
  QString strVal;
  unsigned short rawVal = extractRawVal(msg->at(10), msg->at(11));

  for(unsigned int i = 12; (i < msg->size() && msg->at(i) != 0); ++i)
    strVal.append(msg->at(i));
  qDebug() << QString::number(rawVal) << strVal;

  QFile outFile1(mRaw2ValFileName);
  QFile outFile2(mVal2RawFileName);
  outFile1.open(QIODevice::WriteOnly | QIODevice::Append);
  outFile2.open(QIODevice::WriteOnly | QIODevice::Append);

  QTextStream textStream1(&outFile1);
  QTextStream textStream2(&outFile2);
  textStream1 << "\"" << strVal  << "\",";

  static unsigned long long cnt2 = 0;
  static QString lastVal = "";

  if(lastVal != strVal)
  {
    textStream2 << "{" << rawVal << ",\"" << strVal << "\"},";
    cnt2++;
    lastVal = strVal;
    if(cnt2%100 == 0)
      textStream2 << endl;
  }

  static unsigned long long cnt1 = 0;

  cnt1++;

  if(cnt1%100 == 0)
    textStream1 << endl;

#endif
}

void DebugMidi::debugPrintValues(ByteArray* msg)
{
  unsigned int rawVal = -1;
  const char fct = msg->at(6);

  //if(fct == 0x7e)
  //  return;

  unsigned short ap = msg->at(8);
  unsigned short param = msg->at(9);

  QString strVal("");

  if(fct == sSingleParamChange[0])
  {
    rawVal = extractRawVal(msg->at(10), msg->at(11));
    strVal = QString::number(rawVal, 16);
  }

  else if(fct == sStringParam[0])
  {
    strVal = extractString(ByteArray(msg->begin() + 10, msg->end()));
  }
  else if(fct == sExtParamChange[0])
  {
    rawVal = extractRawVal(ByteArray(msg->begin() + 8, msg->end()));
    ap = (rawVal >> 16) & 0xFFFF;
    param = rawVal & 0xFFFF;
    rawVal = extractRawVal(ByteArray(msg->begin() + 13, msg->end()));
    strVal = QString::number(rawVal, 16);
  }
  else if(fct == sExtStringParamChange[0])
  {
    rawVal = extractRawVal(ByteArray(msg->begin() + 8, msg->end()));
    ap = (rawVal >> 16) & 0xFFFF;
    param = rawVal & 0xFFFF;
    strVal = extractString(ByteArray(msg->begin() + 13, msg->end()));
  }
  else
  {
    for(unsigned int i=10; i < msg->size(); ++i)
    {
      strVal += "0x";
      strVal += QString::number(msg->at(i), 16);
      strVal += " ";
      //rawValArray.push_back(msg->at(i));
    }
  }

  //if(ap != 0x34)
  //    return;

  //if(mod == 0x00)

    qDebug() << "Message size "     <<  QString::number(msg->size())
             << ", function: "      <<  QString::number(fct, 16)
             << ", address page: "  <<  QString::number(ap, 16)
             << ", parameter: "     <<  QString::number(param, 16)
             << ", value: "         << strVal;
}

void DebugMidi::debugRequestStringParam(unsigned char addressPage, unsigned char parameter, unsigned short val)
{
  ByteArray ap;
  ByteArray param;
  ap.push_back(addressPage);
  param.push_back(parameter);
  Midi::get().sendCmd(createValueAsStringGetCmd(ap, param, val));
}

void DebugMidi::debugScanRequest(unsigned char adddressPage, unsigned char minParam, unsigned char maxParam)
{
  ByteArray ap;
  ByteArray param;
  ap.push_back(adddressPage);
  param.push_back(minParam);

  for(unsigned int i = minParam; i <= maxParam; i++)
  {
    param[0] = i;
    Midi::get().sendCmd(createStringParamGetCmd(ap, param));
    Midi::get().sendCmd(createSingleParamGetCmd(ap, param));
  }
}

void DebugMidi::debugRequestExtParam(unsigned int param)
{
  Midi::get().sendCmd(createExtParamGetCmd(param));
}

void DebugMidi::debugRequestExtStringParam(unsigned int param)
{
  Midi::get().sendCmd(createExtStringParamGetCmd(param));
}

void DebugMidi::debugSendSingleParam(ByteArray addressPage, ByteArray param, ByteArray value)
{
  Midi::get().sendCmd(createSingleParamSetCmd(addressPage, param, value));
}

void DebugMidi::debugSendStringParam(ByteArray addressPage, ByteArray param, ByteArray value)
{
  Midi::get().sendCmd(createStringParamSetCmd(addressPage, param, value));
}

void DebugMidi::debugSendExtParam(unsigned int param, unsigned int value)
{
  Midi::get().sendCmd(createExtParamSetCmd(param, value));
}

void DebugMidi::debugSendReserveFct7E(ByteArray addressPage, ByteArray param, ByteArray value)
{
  Midi::get().sendCmd(createReservedFct7E(addressPage, param, value));
}
