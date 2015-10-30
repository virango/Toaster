#include "TunerIndex.h"

TunerIndex::TunerIndex(QObject *parent) : QObject(parent)
{
}

void TunerIndex::midiIndexReceived(unsigned short rawVal)
{
  emit indexReceived((int)raw2Phys(rawVal, 200, 0));
}

