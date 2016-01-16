#include <QVector>
#include <QPair>
#include "LookUpTables.h"
#include "FlangerRateValues.h"

QVector<QPair<int, QString>> LookUpTables::sFlangerRateValues = {FLANGER_RATE_VALUES};
