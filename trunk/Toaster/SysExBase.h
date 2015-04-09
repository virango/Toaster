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
  // header & sysex base struct
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
  // shared values
  BYTEARRAYDECL(On)
  BYTEARRAYDECL(Off)

protected:
  ByteArray createSingleParamGetCmd(ByteArray addressPage, ByteArray param);
  ByteArray createStringParamGetCmd(ByteArray addressPage, ByteArray param);
  ByteArray createSingleParamSetCmd(ByteArray addressPage, ByteArray param, ByteArray val);
  ByteArray createStringParamSetCmd(ByteArray addressPage, ByteArray param, ByteArray val);
  
  ByteArray createSingleParamSetCmd(ByteArray addressPage, ByteArray param, unsigned short rawVal);
};

#endif // SYSEXBASE_H
