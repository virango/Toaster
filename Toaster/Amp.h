#ifndef AMP_H
#define AMP_H

#include <QObject>
#include "AmpMidi.h"

class Amp : public QObject, public AmpMidi
{
  Q_OBJECT
public:
  Amp();
  ~Amp();

  void requestAllValues();
  void requestOnOff() { midiRequestOnOff(); }
  void requestGain() { midiRequestGain(); }
  void requestDefinition() { midiRequestDefinition(); }
  void requestClarity() { midiRequestClarity(); }
  void requestPowerSagging() { midiRequestPowerSagging(); }
  void requestPick() { midiRequestPick(); }
  void requestCompressor() { midiRequestCompressor(); }
  void requestTubeShape() { midiRequestTubeShape(); }
  void requestTubeBias() { midiRequestTubeBias(); }
  void requestDirectMix() { midiRequestDirectMix(); }

signals:
  void onOffReceived(bool onOff);
  void gainReceived(double gain);
  void definitionReceived(double definition);
  void clarityReceived(double clarity);
  void powerSaggingReceived(double powerSagging);
  void pickReceived(double pick);
  void compressorReceived(double compressor);
  void tubeShapeReceived(double tubeShape);
  void tubeBiasReceived(double tubeBias);
  void directMixReceived(double directMix);  
 
public slots:
  void applyOnOff(bool onOff);
  void applyGain(double gain);
  void applyDefinition(double definition);
  void applyClarity(double clarity);
  void applyPowerSagging(double powerSagging);
  void applyPick(double pick);
  void applyCompressor(double compressor);
  void applyTubeShape(double tubeShape);
  void applyTubeBias(double tubeBias);
  void applyDirectMix(double directMix);  
 
protected:
  // AmpMidi
  virtual void midiOnOffReceived(unsigned short rawVal);
  virtual void midiGainReceived(unsigned short rawVal);
  virtual void midiDefinitionReceived(unsigned short rawVal);
  virtual void midiClarityReceived(unsigned short rawVal);
  virtual void midiPowerSaggingReceived(unsigned short rawVal);
  virtual void midiPickReceived(unsigned short rawVal);
  virtual void midiCompressorReceived(unsigned short rawVal);
  virtual void midiTubeShapeReceived(unsigned short rawVal);
  virtual void midiTubeBiasReceived(unsigned short rawVal);
  virtual void midiDirectMixReceived(unsigned short rawVal);
};

#endif // AMP_H
