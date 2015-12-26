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
  static QString delayTypeName(DelayType delayType);
  static QString reverbTypeName(ReverbType reverbType);

private:
  LookUpTables();
  static LookUpTables singleton;
  static double sRaw2dB[16384];
  static unsigned short sDB2Raw[1080];
  static QMultiMap<int, unsigned short> sDB2RawMap;
  static QVector<QString> sNotes;
  static QMap<StompInstance, QString> sStompInstanceNames;
  static QMap<FXType, QString> sStompFXNames;
  static QMap<DelayType, QString> sDelayTypeNames;
  static QMap<ReverbType, QString> sReverbTypeNames;
};

#endif // VOLUMETABLES_H
