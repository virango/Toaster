#ifndef SYSEXBASE_H
#define SYSEXBASE_H
#include <vector>

using namespace std;

typedef vector<unsigned char> ByteArray;
#define INIT_FROM(x) x, x + sizeof(x)
#define VEC_INSERT(x, y) x.insert(x.end(), y.begin(), y.end())

#define BYTEARRAYDECL(Name) \
  static const unsigned char c##Name[];\
  static const ByteArray s##Name;

#define BYTEARRAYDEF(Class, Name, ...) \
  const unsigned char Class::c##Name[] = {__VA_ARGS__}; \
  const ByteArray Class::s##Name(INIT_FROM(c##Name));
  
  

class SysExBase
{
public:
  SysExBase();
  ~SysExBase();

private:
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

protected:
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
  
  ByteArray packRawVal(unsigned short rawVal)
  {
    unsigned char msb = (rawVal >> 7) & 0x7F;
    unsigned char lsb = rawVal & 0x7F;
    ByteArray val;
    val.push_back(msb);
    val.psuh_back(lsb);
    return val;
  }
};

#endif // SYSEXBASE_H
