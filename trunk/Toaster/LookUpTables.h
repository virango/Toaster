#ifndef LOOKUPTABLES_H
#define LOOKUPTABLES_H
#include <QMultiMap>
#include <QString>
#include <QVector>

class LookUpTables
{
public:
  static double raw2dB(unsigned short rawVal);
  static unsigned short dB2Raw(double dB);
  static QString raw2Note(unsigned short rawVal);

private:
  LookUpTables();
  static LookUpTables singleton;
  static double sRaw2dB[16384];
  static unsigned short sDB2Raw[1080];
  static QMultiMap<int, unsigned short> sDB2RawMap;
  static QVector<QString> sNotes;
};

#endif // VOLUMETABLES_H
