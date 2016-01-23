#include "Tuner.h"

Tuner::Tuner(QObject *parent) : QObject(parent)
{

}

void Tuner::midiNoteReceived(unsigned short rawVal)
{
  emit noteReceived(raw2Note(rawVal), raw2Octave(rawVal));
}

void Tuner::midiMuteSignalReceived(unsigned short rawVal)
{
  emit muteSignalReceived(rawVal != 0);
}

