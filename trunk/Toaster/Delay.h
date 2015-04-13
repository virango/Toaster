#ifndef DELAY_H
#define DELAY_H
#include <QObject>
#include "DelayMidi.h"

class Delay : public QObject, public DelayMidi
{
  Q_OBJECT
public:
  Delay();
  ~Delay();

  void requestAllValues();
  
  enum DelayType
  {
    TapDelay,
    FreeDelay,
    AnalogDelay
  };

  enum DelayRatio
  {
    One2Four,
    Two2Four,
    Three2Four,
    FourFour,
    Four2Three,
    Four2Two,
    Four2One
  };

signals:
  void typeReceived(DelayType type);
  void onOffCutsTailReceived(bool onOffCutsTail);
  void mixReceived(double mix);
  void volumeReceived(double volume);
  void timeReceived(double time);
  void ratioReceived(DelayRatio ratio);
  void clockLeftReceived(double clockLeft);
  void clockRightReceived(double clockRight);
  void feedbackReceived(double feedback);
  void bandwidthReceived(double bandwidth);
  void centerFrequencyReceived(double centerFrequency);
  void modulationReceived(double modulation);
  void onOffKeepsTailReceived(bool onOffKeepsTail);
  void duckingReceived(double ducking);

public slots:
  void applyType(DelayType type);
  void applyOnOffCutsTail(bool onOffCutsTail);
  void applyMix(double mix);
  void applyVolume(double volume);
  void applyTime(double time);
  void applyRatio(DelayRatio ratio);
  void applyClockLeft(double clockLeft);
  void applyClockRight(double clockRight);
  void applyFeedback(double feedback);
  void applyBandwidth(double bandwidth);
  void applyCenterFrequency(double centerFrequency);
  void applyModulation(double modulation);
  void applyOnOffKeepsTail(bool onOffKeepsTail);
  void applyDucking(double ducking);

protected:
  // DelayMidi
  virtual void midiTypeReceived(unsigned short rawVal);
  virtual void midiOnOffCutsTailReceived(unsigned short rawVal);
  virtual void midiMixReceived(unsigned short rawVal);
  virtual void midiVolumeReceived(unsigned short rawVal);
  virtual void midiTimeReceived(unsigned short rawVal);
  virtual void midiRatioReceived(unsigned short rawVal);
  virtual void midiClockLeftReceived(unsigned short rawVal);
  virtual void midiClockRightReceived(unsigned short rawVal);
  virtual void midiFeedbackReceived(unsigned short rawVal);
  virtual void midiBandwidthReceived(unsigned short rawVal);
  virtual void midiCenterFrequencyReceived(unsigned short rawVal);
  virtual void midiModulationReceived(unsigned short rawVal);
  virtual void midiOnOffKeepsTailReceived(unsigned short rawVal);
  virtual void midiDuckingReceived(unsigned short rawVal);
};

#endif // DELAY_H
