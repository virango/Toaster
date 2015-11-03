#ifndef STOMP_H
#define STOMP_H

#include <QObject>
#include "StompMidi.h"
#include "Commons.h"

class Stomp : public QObject, public StompMidi
{
  Q_OBJECT
public:
  Stomp(StompInstance instance);
  ~Stomp();


  void requestAllValues();

  void requestType() { midiRequestType(); }
  void requestOnOff() { midiRequestOnOff(); }
  void requestMix() { midiRequestMix(); }
  void requestVolume() { midiRequestVolume(); }
  void requestStereo() { midiRequestStereo(); }
  void requestWahManual() { midiRequestWahManual(); }
  void requestWahPeak() { midiRequestWahPeak(); }
  void requestWahRange() { midiRequestWahRange(); }
  void requestWahPedalMode() { midiRequestWahPedalMode(); }
  void requestWahTouchAttack() { midiRequestWahTouchAttack(); }
  void requestWahTouchRelease() { midiRequestWahTouchRelease(); }
  void requestWahTouchBoost() { midiRequestWahTouchBoost(); }
  void requestDistortionShaperDrive() { midiRequestDistortionShaperDrive(); }
  void requestDistortionBoosterTone() { midiRequestDistortionBoosterTone(); }
  void requestCompressorGateIntensity() { midiRequestCompressorGateIntensity(); }
  void requestCompressorAttack() { midiRequestCompressorAttack(); }
  void requestModulationRate() { midiRequestModulationRate(); }
  void requestModulationDepth() { midiRequestModulationDepth(); }
  void requestModulationFeedback() { midiRequestModulationFeedback(); }
  void requestModulationCrossover() { midiRequestModulationCrossover(); }
  void requestModulationHyperChorusAmount() { midiRequestModulationHyperChorusAmount(); }
  void requestModulationManual() { midiRequestModulationManual(); }
  void requestModulationPhaserPeakSpread() { midiRequestModulationPhaserPeakSpread(); }
  void requestModulationPhaserStages() { midiRequestModulationPhaserStages(); }
  void requestRotarySpeed() { midiRequestRotarySpeed(); }
  void requestRotaryDistance() { midiRequestRotaryDistance(); }
  void requestRotaryBalance() { midiRequestRotaryBalance(); }
  void requestCompressorSquash() { midiRequestCompressorSquash(); }
  void requestGraphicEQBand1() { midiRequestGraphicEQBand1(); }
  void requestGraphicEQBand2() { midiRequestGraphicEQBand2(); }
  void requestGraphicEQBand3() { midiRequestGraphicEQBand3(); }
  void requestGraphicEQBand4() { midiRequestGraphicEQBand4(); }
  void requestGraphicEQBand5() { midiRequestGraphicEQBand5(); }
  void requestGraphicEQBand6() { midiRequestGraphicEQBand6(); }
  void requestGraphicEQBand7() { midiRequestGraphicEQBand7(); }
  void requestGraphicEQBand8() { midiRequestGraphicEQBand8(); }
  void requestParametricEQLowGain() { midiRequestParametricEQLowGain(); }
  void requestParametricEQLowFrequency() { midiRequestParametricEQLowFrequency(); }
  void requestParametricEQHighGain() { midiRequestParametricEQHighGain(); }
  void requestParametricEQHighFrequency() { midiRequestParametricEQHighFrequency(); }
  void requestParametricEQPeakGain() { midiRequestParametricEQPeakGain(); }
  void requestParametricEQPeakFrequency() { midiRequestParametricEQPeakFrequency(); }
  void requestParametricEQPeakQFactor() { midiRequestParametricEQPeakQFactor(); }
  void requestParametricEQPeakGain2() { midiRequestParametricEQPeakGain2(); }
  void requestParametricEQPeakFrequency2() { midiRequestParametricEQPeakFrequency2(); }
  void requestParametricEQPeakQFactor2() { midiRequestParametricEQPeakQFactor2(); }
  void requestWahPeakRange() { midiRequestWahPeakRange(); }
  void requestDucking() { midiRequestDucking(); }
  void requestVoiceMix() { midiRequestVoiceMix(); }
  void requestVoice1Pitch() { midiRequestVoice1Pitch(); }
  void requestVoice2Pitch() { midiRequestVoice2Pitch(); }
  void requestDetune() { midiRequestDetune(); }
  void requestSmoothChords() { midiRequestSmoothChords(); }
  void requestPureTuning() { midiRequestPureTuning(); }
  void requestKey() { midiRequestKey(); }

signals:
  void onOffReceived(bool onOff);
  void typeReceived(::FXType type);
  void mixReceived(double mix);
  void volumeReceived(double volume);
  void stereoReceived(unsigned short rawVal);
  void wahManualReceived(double wahManual);
  void wahPeakReceived(double wahPeak);
  void wahRangeReceived(double wahRange);
  void wahPedalModeReceived(::WahPedalMode wahPedalMode);
  void wahTouchAttackReceived(double wahTouchAttack);
  void wahTouchReleaseReceived(double wahTouchRelease);
  void wahTouchBoostReceived(double wahTouchBoost);
  void distortionShaperDriveReceived(double drive);
  void distortionBoosterToneReceived(double tone);
  void compressorGateIntensityReceived(unsigned short rawVal);
  void compressorAttackReceived(unsigned short rawVal);
  void modulationRateReceived(unsigned short rawVal);
  void modulationDepthReceived(unsigned short rawVal);
  void modulationFeedbackReceived(unsigned short rawVal);
  void modulationCrossoverReceived(unsigned short rawVal);
  void modulationHyperChorusAmountReceived(unsigned short rawVal);
  void modulationManualReceived(unsigned short rawVal);
  void modulationPhaserPeakSpreadReceived(unsigned short rawVal);
  void modulationPhaserStagesReceived(unsigned short rawVal);
  void rotarySpeedReceived(unsigned short rawVal);
  void rotaryDistanceReceived(unsigned short rawVal);
  void rotaryBalanceReceived(unsigned short rawVal);
  void compressorSquashReceived(unsigned short rawVal);
  void graphicEQBand1Received(unsigned short rawVal);
  void graphicEQBand2Received(unsigned short rawVal);
  void graphicEQBand3Received(unsigned short rawVal);
  void graphicEQBand4Received(unsigned short rawVal);
  void graphicEQBand5Received(unsigned short rawVal);
  void graphicEQBand6Received(unsigned short rawVal);
  void graphicEQBand7Received(unsigned short rawVal);
  void graphicEQBand8Received(unsigned short rawVal);
  void parametricEQLowGainReceived(unsigned short rawVal);
  void parametricEQLowFrequencyReceived(unsigned short rawVal);
  void parametricEQHighGainReceived(unsigned short rawVal);
  void parametricEQHighFrequencyReceived(unsigned short rawVal);
  void parametricEQPeakGainReceived(unsigned short rawVal);
  void parametricEQPeakFrequencyReceived(unsigned short rawVal);
  void parametricEQPeakQFactorReceived(unsigned short rawVal);
  void parametricEQPeakGain2Received(unsigned short rawVal);
  void parametricEQPeakFrequency2Received(unsigned short rawVal);
  void parametricEQPeakQFactor2Received(unsigned short rawVal);
  void wahPeakRangeReceived(double wahPeakRange);
  void duckingReceived(double ducking);
  void voiceMixReceived(unsigned short rawVal);
  void voice1PitchReceived(unsigned short rawVal);
  void voice2PitchReceived(unsigned short rawVal);
  void detuneReceived(unsigned short rawVal);
  void smoothChordsReceived(unsigned short rawVal);
  void pureTuningReceived(unsigned short rawVal);
  void keyReceived(unsigned short rawVal);

  
public slots:
  void applyOnOff(bool onOff);
  void applyType(::FXType type);
  void applyMix(double mix);
  void applyVolume(double volume);
  void applyStereo(double stereo);
  void applyWahManual(double wahManual);
  void applyWahPeak(double wahPeak);
  void applyWahRange(double wahRange);
  void applyWahPedalMode(::WahPedalMode wahPedalMode);
  void applyWahTouchAttack(double wahTouchAttack);
  void applyWahTouchRelease(double wahTouchRelease);
  void applyWahTouchBoost(double wahTouchBoost);
  void applyDistortionShaperDrive(double distortionShaperDrive);
  void applyDistortionBoosterTone(double distortionBoosterTone);
  void applyCompressorGateIntensity(double compressorGateIntensity);
  void applyCompressorAttack(double compressorAttack);
  void applyModulationRate(double modulationRate);
  void applyModulationDepth(double modulationDepth);
  void applyModulationFeedback(double modulationFeedback);
  void applyModulationCrossover(double modulationCrossover);
  void applyModulationHyperChorusAmount(double modulationHyperChorusAmount);
  void applyModulationManual(double modulationManual);
  void applyModulationPhaserPeakSpread(double modulationPhaserPeakSpread);
  void applyModulationPhaserStages(double modulationPhaserStages);
  void applyRotarySpeed(RotarySpeed rotarySpeed);
  void applyRotaryDistance(double rotaryDistance);
  void applyRotaryBalance(double rotaryBalance);
  void applyCompressorSquash(double compressorSquash);
  void applyGraphicEQBand1(double graphicEQBand1);
  void applyGraphicEQBand2(double graphicEQBand2);
  void applyGraphicEQBand3(double graphicEQBand3);
  void applyGraphicEQBand4(double graphicEQBand4);
  void applyGraphicEQBand5(double graphicEQBand5);
  void applyGraphicEQBand6(double graphicEQBand6);
  void applyGraphicEQBand7(double graphicEQBand7);
  void applyGraphicEQBand8(double graphicEQBand8);
  void applyParametricEQLowGain(double parametricEQLowGain);
  void applyParametricEQLowFrequency(double parametricEQLowFrequency);
  void applyParametricEQHighGain(double parametricEQHighGain);
  void applyParametricEQHighFrequency(double parametricEQHighFrequency);
  void applyParametricEQPeakGain(double parametricEQPeakGain);
  void applyParametricEQPeakFrequency(double parametricEQPeakFrequency);
  void applyParametricEQPeakQFactor(double parametricEQPeakQFactor);
  void applyParametricEQPeakGain2(double parametricEQPeakGain2);
  void applyParametricEQPeakFrequency2(double parametricEQPeakFrequency2);
  void applyParametricEQPeakQFactor2(double parametricEQPeakQFactor2);
  void applyWahPeakRange(double wahPeakRange);
  void applyDucking(double ducking);
  void applyVoiceMix(double voiceMix);
  void applyVoice1Pitch(double voice1Pitch);
  void applyVoice2Pitch(double voice2Pitch);
  void applyDetune(double detune);
  void applySmoothChords(double smoothChords);
  void applyPureTuning(double pureTuning);
  void applyKey(double key);
  
protected:
  // StompMidi
  virtual void midiOnOffReceived(unsigned short rawVal); 
  virtual void midiTypeReceived(unsigned short rawVal);
  virtual void midiMixReceived(unsigned short rawVal);
  virtual void midiVolumeReceived(unsigned short rawVal);
  virtual void midiStereoReceived(unsigned short rawVal);
  virtual void midiWahManualReceived(unsigned short rawVal);
  virtual void midiWahPeakReceived(unsigned short rawVal);
  virtual void midiWahRangeReceived(unsigned short rawVal);
  virtual void midiWahPedalModeReceived(unsigned short rawVal);
  virtual void midiWahTouchAttackReceived(unsigned short rawVal);
  virtual void midiWahTouchReleaseReceived(unsigned short rawVal);
  virtual void midiWahTouchBoostReceived(unsigned short rawVal);
  virtual void midiDistortionShaperDriveReceived(unsigned short rawVal);
  virtual void midiDistortionBoosterToneReceived(unsigned short rawVal);
  virtual void midiCompressorGateIntensityReceived(unsigned short rawVal);
  virtual void midiCompressorAttackReceived(unsigned short rawVal);
  virtual void midiModulationRateReceived(unsigned short rawVal);
  virtual void midiModulationDepthReceived(unsigned short rawVal);
  virtual void midiModulationFeedbackReceived(unsigned short rawVal);
  virtual void midiModulationCrossoverReceived(unsigned short rawVal);
  virtual void midiModulationHyperChorusAmountReceived(unsigned short rawVal);
  virtual void midiModulationManualReceived(unsigned short rawVal);
  virtual void midiModulationPhaserPeakSpreadReceived(unsigned short rawVal);
  virtual void midiModulationPhaserStagesReceived(unsigned short rawVal);
  virtual void midiRotarySpeedReceived(unsigned short rawVal);
  virtual void midiRotaryDistanceReceived(unsigned short rawVal);
  virtual void midiRotaryBalanceReceived(unsigned short rawVal);
  virtual void midiCompressorSquashReceived(unsigned short rawVal);
  virtual void midiGraphicEQBand1Received(unsigned short rawVal);
  virtual void midiGraphicEQBand2Received(unsigned short rawVal);
  virtual void midiGraphicEQBand3Received(unsigned short rawVal);
  virtual void midiGraphicEQBand4Received(unsigned short rawVal);
  virtual void midiGraphicEQBand5Received(unsigned short rawVal);
  virtual void midiGraphicEQBand6Received(unsigned short rawVal);
  virtual void midiGraphicEQBand7Received(unsigned short rawVal);
  virtual void midiGraphicEQBand8Received(unsigned short rawVal);
  virtual void midiParametricEQLowGainReceived(unsigned short rawVal);
  virtual void midiParametricEQLowFrequencyReceived(unsigned short rawVal);
  virtual void midiParametricEQHighGainReceived(unsigned short rawVal);
  virtual void midiParametricEQHighFrequencyReceived(unsigned short rawVal);
  virtual void midiParametricEQPeakGainReceived(unsigned short rawVal);
  virtual void midiParametricEQPeakFrequencyReceived(unsigned short rawVal);
  virtual void midiParametricEQPeakQFactorReceived(unsigned short rawVal);
  virtual void midiParametricEQPeakGain2Received(unsigned short rawVal);
  virtual void midiParametricEQPeakFrequency2Received(unsigned short rawVal);
  virtual void midiParametricEQPeakQFactor2Received(unsigned short rawVal);
  virtual void midiWahPeakRangeReceived(unsigned short rawVal);
  virtual void midiDuckingReceived(unsigned short rawVal);
  virtual void midiVoiceMixReceived(unsigned short rawVal);
  virtual void midiVoice1PitchReceived(unsigned short rawVal);
  virtual void midiVoice2PitchReceived(unsigned short rawVal);
  virtual void midiDetuneReceived(unsigned short rawVal);
  virtual void midiSmoothChordsReceived(unsigned short rawVal);
  virtual void midiPureTuningReceived(unsigned short rawVal);
  virtual void midiKeyReceived(unsigned short rawVal);

  FXType mFXType;

  static FXDefinition sFXDefinitions[];

};

#endif // STOMP_H
