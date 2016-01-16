#include <QVector>
#include <QPair>
#include "LookUpTables.h"
#include "TremoloRateValues.h"

QVector<QPair<int, QString>> LookUpTables::sTremoloRateValues = {TREMOLO_RATE_VALUES};
