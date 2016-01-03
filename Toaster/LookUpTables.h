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
  static QVector<QPair<int, QString>>* getFrequencyValues() { return &sFrequencyValues; }
  static QVector<QPair<int, QString>>* getTremoloRateValues() { return &sTremoloRateValues; }
  static QVector<QPair<int, QString>>* getQFactorValues() { return &sQFactorValues; }
  static QVector<QPair<int, QString>>* getFlangerRateValues() { return &sFlangerRateValues; }
  static QVector<QPair<int, QString>>* getVoiceIntervalValues() { return &sVoiceIntervalValues; }

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
  static QVector<QPair<int, QString>> sFrequencyValues;
  static QVector<QPair<int, QString>> sTremoloRateValues;
  static QVector<QPair<int, QString>> sQFactorValues;
  static QVector<QPair<int, QString>> sFlangerRateValues;
  static QVector<QPair<int, QString>> sVoiceIntervalValues;
};

#endif // VOLUMETABLES_H
