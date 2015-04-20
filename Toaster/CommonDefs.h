#ifndef COMMONDEFS_H
#define COMMONDEFS_H

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


#endif // COMMONDEFS_H

