#ifndef VOLUMETABLES_H
#define VOLUMETABLES_H
#include <QMultiMap>

class VolumeTables
{
public:
  static double raw2dB(unsigned short rawVal);
  static unsigned short dB2Raw(double dB);

private:
  VolumeTables();
  static VolumeTables singleton;
  static double sRaw2dB[16384];
  static unsigned short sDB2Raw[1080];
  static QMultiMap<int, unsigned short> sDB2RawMap;

};

#endif // VOLUMETABLES_H
