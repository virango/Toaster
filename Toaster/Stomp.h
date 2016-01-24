/*  This file is part of Toaster, the editor and remote control for Kemper profiling amplifier.
*
*   Copyright (C) 2016  Thomas Langer
*
*   Toaster is free software: you can redistribute it and/or modify it under the terms of the
*   GNU General Public License as published by the Free Software Foundation, either version 3
*   of the License, or (at your option) any later version.
*
*   Toaster is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
*   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*   See the GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along with Toaster.
*   If not, see <http://www.gnu.org/licenses/>.
*/
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
  void requestIntensity() { midiRequestIntensity(); }
  void requestVoiceMix() { midiRequestVoiceMix(); }
  void requestVoice1Pitch() { midiRequestVoice1Pitch(); }
  void requestVoice2Pitch() { midiRequestVoice2Pitch(); }
  void requestDetune() { midiRequestDetune(); }
  void requestSmoothChords() { midiRequestSmoothChords(); }
  void requestPureTuning() { midiRequestPureTuning(); }
  void requestVoice1Interval() { midiRequestVoice1Interval(); }
  void requestVoice2Interval() { midiRequestVoice2Interval(); }
  void requestKey() { midiRequestKey(); }
  void requestFormantShiftOnOff() { midiRequestFormantShiftOnOff(); }
  void requestFormantShift() { midiRequestFormantShift(); }
  void requestLowCut() { midiRequestLowCut(); }
  void requestHighCut() { midiRequestHighCut(); }

  ::FXType getFXType() const { return mFXType; }

signals:
  void onOffReceived(bool onOff);
  void typeReceived(::FXType type);
  void mixReceived(double mix);
  void volumeReceived(double volume);
  void stereoReceived(double stereo);
  void wahManualReceived(double wahManual);
  void wahPeakReceived(double wahPeak);
  void wahRangeReceived(double wahRange);
  void wahPedalModeReceived(::WahPedalMode wahPedalMode);
  void wahTouchAttackReceived(double wahTouchAttack);
  void wahTouchReleaseReceived(double wahTouchRelease);
  void wahTouchBoostReceived(double wahTouchBoost);
  void distortionShaperDriveReceived(double drive);
  void distortionBoosterToneReceived(double tone);
  void compressorGateIntensityReceived(double intensity);
  void compressorAttackReceived(double attack);
  void modulationRateReceived(double modulationRate);
  void modulationRateReceived(int modulationRate);
  void modulationDepthReceived(double modulationDepth);
  void modulationFeedbackReceived(double feedback);
  void modulationCrossoverReceived(double crossover);
  void modulationCrossoverReceived(int crossover);
  void modulationHyperChorusAmountReceived(double amount);
  void modulationManualReceived(double manual);
  void modulationPhaserPeakSpreadReceived(double peakSpread);
  void modulationPhaserStagesReceived(double stages);
  void rotarySpeedReceived(::RotarySpeed speed);
  void rotaryDistanceReceived(int distance);
  void rotaryBalanceReceived(double balance);
  void compressorSquashReceived(double squash);
  void graphicEQBand1Received(double graphicEQBand1);
  void graphicEQBand2Received(double graphicEQBand2);
  void graphicEQBand3Received(double graphicEQBand3);
  void graphicEQBand4Received(double graphicEQBand4);
  void graphicEQBand5Received(double graphicEQBand5);
  void graphicEQBand6Received(double graphicEQBand6);
  void graphicEQBand7Received(double graphicEQBand7);
  void graphicEQBand8Received(double graphicEQBand8);
  void parametricEQLowGainReceived(double lowGain);
  void parametricEQLowFrequencyReceived(int lowFreq);
  void parametricEQHighGainReceived(double highGain);
  void parametricEQHighFrequencyReceived(int highFreq);
  void parametricEQPeakGainReceived(double peakGain);
  void parametricEQPeakFrequencyReceived(int peakFreq);
  void parametricEQPeakQFactorReceived(int peakQFactor);
  void parametricEQPeakGain2Received(double peakGain);
  void parametricEQPeakFrequency2Received(int peakFreq);
  void parametricEQPeakQFactor2Received(int peakQFactor);
  void wahPeakRangeReceived(double wahPeakRange);
  void duckingReceived(double ducking);
  void intensityReceived(double mix);
  void voiceMixReceived(double voiceMix);
  void voice1PitchReceived(double voice1Pitch);
  void voice2PitchReceived(double voice2Pitch);
  void detuneReceived(double detune);
  void smoothChordsReceived(bool onOff);
  void pureTuningReceived(bool onOff);
  void voice1IntervalReceived(int voice1Interval);
  void voice2IntervalReceived(int voice2Interval);
  void keyReceived(int rawVal);
  void formantShiftOnOffReceived(bool onOff);
  void formantShiftReceived(double shift);
  void lowCutReceived(int lowCut);
  void highCutReceived(int highCut);
  
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
  void applyModulationRate(int modulationRate);
  void applyModulationDepth(double modulationDepth);
  void applyModulationFeedback(double modulationFeedback);
  void applyModulationCrossover(double modulationCrossover);
  void applyModulationCrossover(int modulationCrossover);
  void applyModulationHyperChorusAmount(double modulationHyperChorusAmount);
  void applyModulationManual(double modulationManual);
  void applyModulationPhaserPeakSpread(double modulationPhaserPeakSpread);
  void applyModulationPhaserStages(double modulationPhaserStages);
  void applyRotarySpeed(RotarySpeed rotarySpeed);
  void applyRotaryDistance(int rotaryDistance);
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
  void applyParametricEQLowFrequency(int parametricEQLowFrequency);
  void applyParametricEQHighGain(double parametricEQHighGain);
  void applyParametricEQHighFrequency(int parametricEQHighFrequency);
  void applyParametricEQPeakGain(double parametricEQPeakGain);
  void applyParametricEQPeakFrequency(int parametricEQPeakFrequency);
  void applyParametricEQPeakQFactor(int parametricEQPeakQFactor);
  void applyParametricEQPeakGain2(double parametricEQPeakGain2);
  void applyParametricEQPeakFrequency2(int parametricEQPeakFrequency2);
  void applyParametricEQPeakQFactor2(int parametricEQPeakQFactor2);
  void applyWahPeakRange(double wahPeakRange);
  void applyDucking(double ducking);
  void applyIntensity(double mix);
  void applyVoiceMix(double voiceMix);
  void applyVoice1Pitch(double voice1Pitch);
  void applyVoice2Pitch(double voice2Pitch);
  void applyDetune(double detune);
  void applySmoothChords(bool onOff);
  void applyPureTuning(bool onOff);
  void applyVoice1Interval(int voice1Interval);
  void applyVoice2Interval(int voice2Interval);
  void applyKey(int key);
  void applyFormantShiftOnOff(bool onOff);
  void applyFormantShift(double shift);
  void applyLowCut(int lowCut);
  void applyHighCut(int highCut);
  
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
  virtual void midiIntensityReceived(unsigned short rawVal);
  virtual void midiVoiceMixReceived(unsigned short rawVal);
  virtual void midiVoice1PitchReceived(unsigned short rawVal);
  virtual void midiVoice2PitchReceived(unsigned short rawVal);
  virtual void midiDetuneReceived(unsigned short rawVal);
  virtual void midiSmoothChordsReceived(unsigned short rawVal);
  virtual void midiPureTuningReceived(unsigned short rawVal);
  virtual void midiVoice1IntervalReceived(unsigned short rawVal);
  virtual void midiVoice2IntervalReceived(unsigned short rawVal);
  virtual void midiKeyReceived(unsigned short rawVal);
  virtual void midiFormantShiftOnOffReceived(unsigned short rawVal);
  virtual void midiFormantShiftReceived(unsigned short rawVal);
  virtual void midiLowCutReceived(unsigned short rawVal);
  virtual void midiHighCutReceived(unsigned short rawVal);

  FXType mFXType;

  static FXDefinition sFXDefinitions[];

};

#endif // STOMP_H
