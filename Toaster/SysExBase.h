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
#ifndef SYSEXBASE_H
#define SYSEXBASE_H
#include "Commons.h"
#include "LookUpTables.h"
#include <QString>

class SysExBase
{
protected:
  SysExBase();
  ~SysExBase();

  // sysex header & base struct
  BYTEARRAYDECL(Header)
  BYTEARRAYDECL(Eox)
  // function codes (with instance)
  BYTEARRAYDECL(SingleParamChange)
  BYTEARRAYDECL(MultiParamChange)
  BYTEARRAYDECL(StringParam)
  BYTEARRAYDECL(BLOB)
  BYTEARRAYDECL(ExtParamChange)
  BYTEARRAYDECL(ExtStringParamChange)
  BYTEARRAYDECL(ReqSingleParamVal)
  BYTEARRAYDECL(ReqMultiParamVals)
  BYTEARRAYDECL(ReqStringParam)
  BYTEARRAYDECL(ReqExtParam)
  BYTEARRAYDECL(ReqExtStringParam)
  BYTEARRAYDECL(ReqParamAsString)

  BYTEARRAYDECL(ReservedFct7E)
  BYTEARRAYDECL(ReservedFct7F)

  ByteArray createSingleParamGetCmd(const ByteArray& addressPage, const ByteArray& param);
  ByteArray createSingleParamSetCmd(const ByteArray& addressPage, const ByteArray& param, const ByteArray& val);
  ByteArray createSingleParamSetCmd(const ByteArray& addressPage, const ByteArray& param, unsigned short rawVal);

  ByteArray createStringParamGetCmd(const ByteArray& addressPage, const ByteArray& param);
  ByteArray createStringParamSetCmd(const ByteArray& addressPage, const ByteArray& param, const ByteArray& val);
  ByteArray createStringParamSetCmd(const ByteArray& addressPage, const ByteArray& param, const QString& strVal);

  ByteArray createExtParamGetCmd(const ByteArray& param);
  ByteArray createExtParamSetCmd(const ByteArray& param, const ByteArray& val);
  ByteArray createExtParamGetCmd(unsigned int param);
  ByteArray createExtParamSetCmd(unsigned int, unsigned int val);

  ByteArray createValueAsStringGetCmd(const ByteArray& addressPage, const ByteArray& param, const ByteArray& val);
  ByteArray createValueAsStringGetCmd(const ByteArray& addressPage, const ByteArray& param, unsigned short rawVal);

  ByteArray createExtStringParamGetCmd(const ByteArray& param);
  ByteArray createExtStringParamGetCmd(unsigned int param);

  ByteArray createReservedFct7E(const ByteArray& addressPage, const ByteArray& param, const ByteArray& val);
  ByteArray createReservedFct7F(const ByteArray& addressPage, const ByteArray& param, const ByteArray& val);
  
  // utilities
  double raw2Phys(unsigned short rawVal, double deltaMinMax, double min)
  {
    double physVal = ((rawVal * deltaMinMax) / 0x3FFF) + min;
    return physVal;
  }
  
  bool raw2Bool(unsigned short rawVal)
  {
    return rawVal != 0;
  }
  
  unsigned short phys2Raw(double physVal, double deltaMinMax, double min, unsigned short maxRawVal = 0x3FFF)
  {
    unsigned short rawVal = ((physVal - min) * maxRawVal) / deltaMinMax;
    return rawVal;
  }
  
  unsigned short bool2Raw(bool val)
  {
    return val ? 1 : 0;
  }
  
  unsigned short extractRawVal(unsigned char msb, unsigned char lsb)
  {
    unsigned short rawVal = (((unsigned short)msb & 0x7F) << 7) | ((unsigned short)lsb & 0x7F);
    return rawVal;
  }

  unsigned int extractRawVal(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4)
  {
    unsigned char t0 = (b4 & 0x7F) | (b3 << 7);
    unsigned char t1 = ((b3 >> 1) & 0x3F) | (b2 << 6);
    unsigned char t2 = ((b2 >> 2) & 0x1F) | (b1 << 5);
    unsigned char t3 = ((b1 >> 3) & 0x0F) | (b0 << 4);
    unsigned int rawVal = ((unsigned int)t0 << 24)
                        | ((unsigned int)t1 << 16)
                        | ((unsigned int)t2 <<  8)
                        | ((unsigned int)t3);
    return rawVal;
  }

  unsigned int extractRawVal(ByteArray b)
  {
    unsigned char t0 = (b[4] & 0x7F) | (b[3] << 7);
    unsigned char t1 = ((b[3] >> 1) & 0x3F) | (b[2] << 6);
    unsigned char t2 = ((b[2] >> 2) & 0x1F) | (b[1] << 5);
    unsigned char t3 = ((b[1] >> 3) & 0x0F) | (b[0] << 4);
    unsigned int rawVal = ((unsigned int)t0)
                        | ((unsigned int)t1 << 8)
                        | ((unsigned int)t2 << 16)
                        | ((unsigned int)t3 << 24);
    return rawVal;
  }

  QString extractString(ByteArray byteArray)
  {
    QString strVal;
    for(unsigned int i = 0; (i < byteArray.size() && byteArray.at(i) != 0); ++i)
      strVal.append(byteArray.at(i));

    return strVal;
  }
  
  ByteArray packRawVal(unsigned short rawVal)
  {
    unsigned char msb = (rawVal >> 7) & 0x7F;
    unsigned char lsb = rawVal & 0x7F;
    ByteArray val;
    val.push_back(msb);
    val.push_back(lsb);
    return val;
  }

  ByteArray packRawVal(unsigned int rawVal)
  {
    ByteArray val;
    val.push_back((rawVal >> 28) & 0x7f);
    val.push_back((rawVal >> 21) & 0x7f);
    val.push_back((rawVal >> 14) & 0x7f);
    val.push_back((rawVal >> 7) & 0x7f);
    val.push_back(rawVal & 0x7f);

    return val;
  }

  ByteArray packString(const QString& strVal)
  {
    ByteArray val;
    for(int i = 0; i < strVal.length(); ++i)
      val.push_back(strVal.at(i).toLatin1());

    val.push_back(0);
    return val;
  }

  QString raw2Note(unsigned short rawVal)
  {
    if(rawVal >= 12 )
      return LookUpTables::raw2Note(rawVal%12);
    return "_";
  }

  QString raw2Octave(unsigned short rawVal)
  {
    if(rawVal > 12)
      return QString::number((rawVal/12) - 1);
    return "";
  }

  int raw2SPDIFSource(unsigned short rawVal)
  {
    static vector<int> values = { 0, 1, 1, 2, 3, 4, 6, 7, 8, 7, 2, 2, 8, 9, 5, 8};
    if(rawVal < values.size())
      return values[rawVal];
    else return 8;
  }

  unsigned short spdifSource2Raw(int source)
  {
    static vector<unsigned short> values = {0, 2, 3, 4, 5, 14, 6, 9, 12, 13};
    if((size_t)source < values.size())
      return values[source];
    return 13;
  }
};

#endif // SYSEXBASE_H
