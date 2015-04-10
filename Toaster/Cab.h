#ifndef CAB_H
#define CAB_H
#include <QObject>
#include "CabMidi.h"

class Cab : public QObject, public CabMidi
{
  Q_OBJECT
public:
  Cab();
  ~Cab();

  void requestValues();
  
signals:
  void onOffReceived(bool onOff);
  void volumeReceived(double volume);
  void highShiftReceived(double highShift);
  void lowShiftReceived(double lowShift);
  void characterReceived(double character);

public slots:
  void applyOnOff(bool onOff);
  void applyVolume(double volume);
  void applyHighShift(double highShift);
  void applyLowShift(double lowShift);
  void applyCharacter(double character);

protected:
  // CabMidi
  void midiOnOffReceived(unsigned short rawVal);
  void midiVolumeReceived(unsigned short rawVal);
  void midiHighShiftReceived(unsigned short rawVal);
  void midiLowShiftReceived(unsigned short rawVal);
  void midiCharacterReceived(unsigned short rawVal);
};

#endif // CAB_H
