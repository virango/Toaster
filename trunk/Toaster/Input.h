#ifndef INPUT_H
#define INPUT_H

#include <QObject>
#include "InputMidi.h"

class Input : public QObject, public InputMidi
{
  Q_OBJECT
public:
  Input();
  ~Input();


  void requestAllValues();

signals:
  void noiseGateReceived(double noiseGate);
  void cleanSenseReceived(double cleanSense);
  void distortionSenseReceived(double distortionSense);

public slots:
  void applyNoiseGate(double noiseGate);
  void applyCleanSense(double cleanSense);
  void applyDistortionSense(double cleanSense);

protected:
  // InputMidi
  virtual void midiNoiseGateReceived(unsigned short rawVal);
  virtual void midiCleanSenseReceived(unsigned short rawVal);
  virtual void midiDistortionSenseReceived(unsigned short rawVal);
};

#endif // INPUT_H
