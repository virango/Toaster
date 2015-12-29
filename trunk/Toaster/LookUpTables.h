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
  static QString raw2Note(unsigned short rawVal);
  static QString stompInstanceName(StompInstance instance);
  static QString stompFXName(FXType fxType);
  static QString delayTypeName(DelayType delayType);
  static QString reverbTypeName(ReverbType reverbType);
  static QVector<QPair<int, QString>>* getRotaryDistanceValues() { return &sRotaryDistanceValues; }
  static QVector<QPair<int, QString>>* getRigVolumeValues() { return &sRigVolumeValues; }
  static QVector<QPair<int, QString>>* getMainVolumeValues() { return &sMainVolumeValues; }
  static QVector<QPair<int, QString>>* getMixValues() { return &sMixValues; }

private:
  LookUpTables();
  static LookUpTables singleton;
  static QVector<QString> sNotes;
  static QMap<StompInstance, QString> sStompInstanceNames;
  static QMap<FXType, QString> sStompFXNames;
  static QMap<DelayType, QString> sDelayTypeNames;
  static QMap<ReverbType, QString> sReverbTypeNames;
  static QVector<QPair<int, QString>> sRotaryDistanceValues;
  static QVector<QPair<int, QString>> sRigVolumeValues;
  static QVector<QPair<int, QString>> sMainVolumeValues;
  static QVector<QPair<int, QString>> sMixValues;
};

#endif // VOLUMETABLES_H
