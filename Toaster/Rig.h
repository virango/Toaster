#ifndef RIG_H
#define RIG_H
#include <QObject>
#include "RigMidi.h"

class Rig : public QObject, public RigMidi
{
  Q_OBJECT
public:
  Rig();
  ~Rig();

  void requestAllValues();

signals:
  void tempoReceived(double tempo);
  void volumeReceived(double volume);
  void tempoEnableReceived(bool tempoEnable);

public slots:
  void applyTempo(double tempo);
  void applyVolume(double volume);
  void applyTempoEnable(bool tempoEnable);

protected:
  // RigMidi
  virtual void midiTempoReceived(unsigned short rawVal);
  virtual void midiVolumeReceived(unsigned short rawVal);
  virtual void midiTempoEnableReceived(unsigned short rawVal);
};

#endif // RIG_H
