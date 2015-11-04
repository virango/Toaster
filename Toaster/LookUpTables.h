#ifndef LOOKUPTABLES_H
#define LOOKUPTABLES_H
#include <QMultiMap>
#include <QString>
#include <QVector>
#include <QMap>
#include "Commons.h"

class LookUpTables
{
public:
  static double raw2dB(unsigned short rawVal);
  static unsigned short dB2Raw(double dB);
  static QString raw2Note(unsigned short rawVal);
  static QString stompInstanceName(StompInstance instance);
  static QString stompFXName(FXType fxType);

private:
  LookUpTables();
  static LookUpTables singleton;
  static double sRaw2dB[16384];
  static unsigned short sDB2Raw[1080];
  static QMultiMap<int, unsigned short> sDB2RawMap;
  static QVector<QString> sNotes;
  static QMap<StompInstance, QString> sStompInstanceNames;
  static QMap<FXType, QString> sStompFXNames;
};

#endif // VOLUMETABLES_H
