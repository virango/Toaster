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
  void stompsEnableReceived(bool stompsEnable);
  void stackEnableReceived(bool stackEnable);
  void effectsEnableReceived(bool effectsEnable);

public slots:
  void applyTempo(double tempo);
  void applyVolume(double volume);
  void applyTempoEnable(bool tempoEnable);
  void applyStompsEnable(bool stompsEnable);
  void applyStackEnable(bool stackEnable);
  void applyEffectsEnable(bool effectsEnable);

protected:
  // RigMidi
  virtual void midiTempoReceived(unsigned short rawVal);
  virtual void midiVolumeReceived(unsigned short rawVal);
  virtual void midiTempoEnableReceived(unsigned short rawVal);
  virtual void midiStompsEnableReceived(unsigned short rawVal);
  virtual void midiStackEnableReceived(unsigned short rawVal);
  virtual void midiEffectsEnableReceived(unsigned short rawVal);
};

#endif // RIG_H
