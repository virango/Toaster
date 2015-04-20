#ifndef SYSEXBASE_H
#define SYSEXBASE_H
#include "CommonDefs.h"

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
  BYTEARRAYDECL(ReqExtStringParam)

  ByteArray createSingleParamGetCmd(const ByteArray& addressPage, const ByteArray& param);
  ByteArray createStringParamGetCmd(const ByteArray& addressPage, const ByteArray& param);
  ByteArray createSingleParamSetCmd(const ByteArray& addressPage, const ByteArray& param, const ByteArray& val);
  ByteArray createStringParamSetCmd(const ByteArray& addressPage, const ByteArray& param, const ByteArray& val);
  
  ByteArray createSingleParamSetCmd(const ByteArray& addressPage, const ByteArray& param, unsigned short rawVal);
  
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
  
  unsigned short phys2Raw(double physVal, double deltaMinMax, double min)
  {
    unsigned short rawVal = ((physVal - min) * 0x3FFF) / deltaMinMax;
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
  
  ByteArray packRawVal(unsigned short rawVal)
  {
    unsigned char msb = (rawVal >> 7) & 0x7F;
    unsigned char lsb = rawVal & 0x7F;
    ByteArray val;
    val.push_back(msb);
    val.push_back(lsb);
    return val;
  }
};

#endif // SYSEXBASE_H
