#include "TunerNote.h"

TunerNote::TunerNote(QObject *parent) : QObject(parent)
{

}

void TunerNote::midiNoteReceived(unsigned short rawVal)
{
  emit noteReceived(raw2Note(rawVal), raw2Octave(rawVal));
}

