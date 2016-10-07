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
#include "Stomp.h"
#include "Settings.h"

Stomp::Stomp(StompInstance instance)
  : QObject(0)
  , StompMidi(instance)
  , mFXType(None)
{
}

Stomp::~Stomp()
{
}

Stomp& Stomp::getA()
{
  static Stomp stomp(StompA);
  return stomp;
}

Stomp& Stomp::getB()
{
  static Stomp stomp(StompB);
  return stomp;
}

Stomp& Stomp::getC()
{
  static Stomp stomp(StompC);
  return stomp;
}

Stomp& Stomp::getD()
{
  static Stomp stomp(StompD);
  return stomp;
}

Stomp& Stomp::getX()
{
  static Stomp stomp(StompX);
  return stomp;
}

Stomp& Stomp::getMod()
{
  static Stomp stomp(StompMod);
  return stomp;
}

Stomp& Stomp::getDelay()
{
  static Stomp stomp(StompDelay);
  return stomp;
}

void Stomp::requestAllValues()
{
  midiRequestOnOff();
  midiRequestType();
}

// slots
void Stomp::applyOnOff(bool onOff)
{
  midiApplyOnOff(Utils::bool2Raw(onOff));
  midiRequestOnOff();
}

void Stomp::applyType(FXType type)
{
  midiApplyType(fxType2Raw(type));
  midiRequestType();
}

void Stomp::applyMix(double mix)
{
  midiApplyMix(Utils::phys2Raw(mix, 100, 0));
}

void Stomp::applyVolume(double volume)
{
  midiApplyVolume(Utils::phys2Raw(volume, 10, -5));
}

void Stomp::applyStereo(double stereo)
{
  midiApplyStereo(Utils::phys2Raw(stereo, 360, -180));
}

void Stomp::applyWahManual(double wahManual)
{
  midiApplyWahManual(Utils::phys2Raw(wahManual, 10, 0));
}

void Stomp::applyWahPeak(double wahPeak)
{
  midiApplyWahPeak(Utils::phys2Raw(wahPeak, 10, 0));
}

void Stomp::applyWahRange(double wahRange)
{
  midiApplyWahRange(Utils::phys2Raw(wahRange, 200, -100));
}

void Stomp::applyWahPedalMode(::WahPedalMode wahPedalMode)
{
  midiApplyWahPedalMode((unsigned short)wahPedalMode);
}

void Stomp::applyWahTouchAttack(double wahTouchAttack)
{
  midiApplyWahTouchAttack(Utils::phys2Raw(wahTouchAttack, 10, 0));
}

void Stomp::applyWahTouchRelease(double wahTouchRelease)
{
  midiApplyWahTouchRelease(Utils::phys2Raw(wahTouchRelease, 10, 0));
}

void Stomp::applyWahTouchBoost(double wahTouchBoost)
{
  midiApplyWahTouchBoost(Utils::phys2Raw(wahTouchBoost, 10, 0));
}

void Stomp::applyDistortionShaperDrive(double distortionShaperDrive)
{
  midiApplyDistortionShaperDrive(Utils::phys2Raw(distortionShaperDrive, 10, 0));
}

void Stomp::applyDistortionBoosterTone(double distortionBoosterTone)
{
  if(Settings::get().getKPAOSVersion() < 0x04000000)
    midiApplyDistortionBoosterTone(Utils::phys2Raw(distortionBoosterTone, 10, -5));
  else
    midiApplyDistortionBoosterTone(Utils::phys2Raw(distortionBoosterTone, 10, 0));
}

void Stomp::applyCompressorGateIntensity(double compressorGateIntensity)
{
  midiApplyCompressorGateIntensity(Utils::phys2Raw(compressorGateIntensity, 10, 0));
}

void Stomp::applyCompressorAttack(double compressorAttack)
{
  midiApplyCompressorAttack(Utils::phys2Raw(compressorAttack, 10 , 0));
}

void Stomp::applyModulationRate(double modulationRate)
{
  midiApplyModulationRate(Utils::phys2Raw(modulationRate, 10, 0));
}

void Stomp::applyModulationRate(int modulationRate)
{
  midiApplyModulationRate((unsigned short)modulationRate);
}

void Stomp::applyModulationDepth(double modulationDepth)
{
  midiApplyModulationDepth(Utils::phys2Raw(modulationDepth, 10, 0));
}

void Stomp::applyModulationFeedback(double modulationFeedback)
{
  midiApplyModulationFeedback(Utils::phys2Raw(modulationFeedback, 100, 0));
}

void Stomp::applyModulationCrossover(double modulationCrossover)
{
  midiApplyModulationCrossover(Utils::phys2Raw(modulationCrossover, 10, 0));
}

void Stomp::applyModulationCrossover(int modulationCrossover)
{
  midiApplyModulationCrossover((unsigned short)modulationCrossover);
}

void Stomp::applyModulationHyperChorusAmount(double modulationHyperChorusAmount)
{
  midiApplyModulationHyperChorusAmount(Utils::phys2Raw(modulationHyperChorusAmount, 2, 1));
}

void Stomp::applyModulationManual(double modulationManual)
{
  midiApplyModulationManual(Utils::phys2Raw(modulationManual, 10, 0));
}

void Stomp::applyModulationPhaserPeakSpread(double modulationPhaserPeakSpread)
{
  midiApplyModulationPhaserPeakSpread(Utils::phys2Raw(modulationPhaserPeakSpread, 10, -5));
}

void Stomp::applyModulationPhaserStages(double modulationPhaserStages)
{
  midiApplyModulationPhaserStages((unsigned short)(modulationPhaserStages-2)/2);
}

void Stomp::applyRotarySpeed(::RotarySpeed rotarySpeed)
{
  midiApplyRotarySpeed((unsigned short)rotarySpeed);
}

void Stomp::applyRotaryDistance(int rotaryDistance)
{
  midiApplyRotaryDistance((unsigned short)rotaryDistance);
}

void Stomp::applyRotaryBalance(double rotaryBalance)
{
  midiApplyRotaryBalance(Utils::phys2Raw(rotaryBalance, 200, -100));
}

void Stomp::applyCompressorSquash(double compressorSquash)
{
  midiApplyCompressorSquash(Utils::phys2Raw(compressorSquash, 10, -5));
}

void Stomp::applyGraphicEQBand1(double graphicEQBand)
{
  midiApplyGraphicEQBand1(Utils::phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyGraphicEQBand2(double graphicEQBand)
{
  midiApplyGraphicEQBand2(Utils::phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyGraphicEQBand3(double graphicEQBand)
{
  midiApplyGraphicEQBand3(Utils::phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyGraphicEQBand4(double graphicEQBand)
{
  midiApplyGraphicEQBand4(Utils::phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyGraphicEQBand5(double graphicEQBand)
{
  midiApplyGraphicEQBand5(Utils::phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyGraphicEQBand6(double graphicEQBand)
{
  midiApplyGraphicEQBand6(Utils::phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyGraphicEQBand7(double graphicEQBand)
{
  midiApplyGraphicEQBand7(Utils::phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyGraphicEQBand8(double graphicEQBand)
{
  midiApplyGraphicEQBand8(Utils::phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyParametricEQLowGain(double gain)
{
  midiApplyParametricEQLowGain(Utils::phys2Raw(gain, 24, -12));
}

void Stomp::applyParametricEQLowFrequency(int frequency)
{
  midiApplyParametricEQLowFrequency((unsigned short)frequency);
}

void Stomp::applyParametricEQHighGain(double gain)
{
  midiApplyParametricEQHighGain(Utils::phys2Raw(gain, 24, -12));
}

void Stomp::applyParametricEQHighFrequency(int frequency)
{
  midiApplyParametricEQHighFrequency((unsigned short)frequency);
}

void Stomp::applyParametricEQPeakGain(double gain)
{
  midiApplyParametricEQPeakGain(Utils::phys2Raw(gain, 24, -12));
}

void Stomp::applyParametricEQPeakFrequency(int frequency)
{
  midiApplyParametricEQPeakFrequency((unsigned short)frequency);
}

void Stomp::applyParametricEQPeakQFactor(int factor)
{
  midiApplyParametricEQPeakQFactor((unsigned short)factor);
}

void Stomp::applyParametricEQPeakGain2(double gain)
{
  midiApplyParametricEQPeakGain2(Utils::phys2Raw(gain, 24, -12));
}

void Stomp::applyParametricEQPeakFrequency2(int frequency)
{
  midiApplyParametricEQPeakFrequency2((unsigned short)frequency);
}

void Stomp::applyParametricEQPeakQFactor2(int factor)
{
  midiApplyParametricEQPeakQFactor2((unsigned short)factor);
}

void Stomp::applyWahPeakRange(double wahPeakRange)
{
  midiApplyWahPeakRange(Utils::phys2Raw(wahPeakRange, 200, -100));
}

void Stomp::applyDucking(double ducking)
{
  midiApplyDucking(Utils::phys2Raw(ducking, 10, -5));
}

void Stomp::applyIntensity(double mix)
{
  midiApplyIntensity(Utils::phys2Raw(mix, 100, 0));
}

void Stomp::applyVoiceMix(double voiceMix)
{
  midiApplyVoiceMix(Utils::phys2Raw(voiceMix, 10, -5));
}

void Stomp::applyVoice1Pitch(double voice1Pitch)
{
  midiApplyVoice1Pitch(64 + (unsigned short)voice1Pitch);
}

void Stomp::applyVoice2Pitch(double voice2Pitch)
{
  midiApplyVoice2Pitch(64 + (unsigned short)voice2Pitch);
}

void Stomp::applyDetune(double detune)
{
  midiApplyDetune(Utils::phys2Raw(detune, 10, 0));
}

void Stomp::applySmoothChords(bool onOff)
{
  midiApplySmoothChords(Utils::bool2Raw(onOff));
}

void Stomp::applyPureTuning(bool onOff)
{
  midiApplyPureTuning(Utils::bool2Raw(onOff));
}

void Stomp::applyVoice1Interval(int voice1Interval)
{
  midiApplyVoice1Interval((unsigned short)voice1Interval);
}

void Stomp::applyVoice2Interval(int voice2Interval)
{
  midiApplyVoice2Interval((unsigned short)voice2Interval);
}

void Stomp::applyKey(int key)
{
  midiApplyKey((unsigned short) key);
}

void Stomp::applyFormantShiftOnOff(bool onOff)
{
  midiApplyFormantShiftOnOff(Utils::bool2Raw(onOff));
}

void Stomp::applyFormantShift(double shift)
{
  midiApplyFormantShift(Utils::phys2Raw(shift, 10, -5));
}

void Stomp::applyLowCut(int lowCut)
{
  midiApplyLowCut((unsigned short)lowCut);
}

void Stomp::applyHighCut(int highCut)
{
  midiApplyHighCut((unsigned short)highCut);
}

void Stomp::applyDelayMix(int mix)
{
  midiApplyDelayMix((unsigned short)mix);
}

void Stomp::applyDelay1Time(double time)
{
  midiApplyDelay1Time(Utils::phys2Raw(time, 2000, 0));
}

void Stomp::applyDelay2Ratio(double ratio)
{
  midiApplyDelay2Ratio(Utils::phys2Raw(ratio, 100, 0));
}

void Stomp::applyDelayNoteValue1(int noteValue)
{
  midiApplyDelayNoteValue1((unsigned short)noteValue);
}

void Stomp::applyDelayNoteValue2(int noteValue)
{
  midiApplyDelayNoteValue2((unsigned short)noteValue);
}

void Stomp::applyDelayFeedback(double feedback)
{
  midiApplyDelayFeedback(Utils::phys2Raw(feedback, 100, 0));
}

void Stomp::applyDelayToTempo(int toTempo)
{
  midiApplyDelayToTempo((unsigned short)toTempo);
}

void Stomp::applyDelayModulation(double modulation)
{
  midiApplyDelayModulation(Utils::phys2Raw(modulation, 10, 0));
}

// StompMidi callbacks
void Stomp::midiTypeReceived(unsigned short rawVal)
{
  mFXType = raw2FXType(rawVal);
  emit typeReceived(mFXType);
}

void Stomp::midiOnOffReceived(unsigned short rawVal)
{
  emit onOffReceived(Utils::raw2Bool(rawVal));
}

void Stomp::midiMixReceived(unsigned short rawVal)
{
  emit mixReceived(Utils::raw2Phys(rawVal, 100, 0));
}

void Stomp::midiVolumeReceived(unsigned short rawVal)
{
  emit volumeReceived(Utils::raw2Phys(rawVal, 10, -5));
}

void Stomp::midiStereoReceived(unsigned short rawVal)
{
  emit stereoReceived(Utils::raw2Phys(rawVal, 360, -180));
}

void Stomp::midiWahManualReceived(unsigned short rawVal)
{
  emit wahManualReceived(Utils::raw2Phys(rawVal, 10, 0));
}

void Stomp::midiWahPeakReceived(unsigned short rawVal)
{
  emit wahPeakReceived(Utils::raw2Phys(rawVal, 10, 0));
}

void Stomp::midiWahRangeReceived(unsigned short rawVal)
{
  emit wahRangeReceived(Utils::raw2Phys(rawVal, 200, -100));
}

void Stomp::midiWahPedalModeReceived(unsigned short rawVal)
{
  emit wahPedalModeReceived((WahPedalMode)rawVal);
}

void Stomp::midiWahTouchAttackReceived(unsigned short rawVal)
{
  emit wahTouchAttackReceived(Utils::raw2Phys(rawVal, 10, 0));
}

void Stomp::midiWahTouchReleaseReceived(unsigned short rawVal)
{
  emit wahTouchReleaseReceived(Utils::raw2Phys(rawVal, 10, 0));
}

void Stomp::midiWahTouchBoostReceived(unsigned short rawVal)
{
  emit wahTouchBoostReceived(Utils::raw2Phys(rawVal, 10, 0));
}

void Stomp::midiDistortionShaperDriveReceived(unsigned short rawVal)
{
  emit distortionShaperDriveReceived(Utils::raw2Phys(rawVal, 10, 0));
}

void Stomp::midiDistortionBoosterToneReceived(unsigned short rawVal)
{
  if(Settings::get().getKPAOSVersion() < 0x04000000)
    emit distortionBoosterToneReceived(Utils::raw2Phys(rawVal, 10, -5));
  else
    emit distortionBoosterToneReceived(Utils::raw2Phys(rawVal, 10, 0));
}

void Stomp::midiCompressorGateIntensityReceived(unsigned short rawVal)
{
  emit compressorGateIntensityReceived(Utils::raw2Phys(rawVal, 10, 0));
}

void Stomp::midiCompressorAttackReceived(unsigned short rawVal)
{
  emit compressorAttackReceived(Utils::raw2Phys(rawVal, 10, 0));
}

void Stomp::midiModulationRateReceived(unsigned short rawVal)
{
  // there seems to be a bug in the kpa: it sends values between 0..127
  double physVal = ((rawVal * 10.0) / 127.0);
  emit modulationRateReceived(physVal);
  emit modulationRateReceived(rawVal);
}

void Stomp::midiModulationDepthReceived(unsigned short rawVal)
{
  emit modulationDepthReceived(Utils::raw2Phys(rawVal, 10, 0));
}

void Stomp::midiModulationFeedbackReceived(unsigned short rawVal)
{
  emit modulationFeedbackReceived(Utils::raw2Phys(rawVal, 100, 0));
}

void Stomp::midiModulationCrossoverReceived(unsigned short rawVal)
{
  emit modulationCrossoverReceived(Utils::raw2Phys(rawVal, 10, 0));
  emit modulationCrossoverReceived((int)rawVal);
}

void Stomp::midiModulationHyperChorusAmountReceived(unsigned short rawVal)
{
  emit modulationHyperChorusAmountReceived(Utils::raw2Phys(rawVal, 2, 1));
}

void Stomp::midiModulationManualReceived(unsigned short rawVal)
{
  emit modulationManualReceived(Utils::raw2Phys(rawVal, 10, 0));
}

void Stomp::midiModulationPhaserPeakSpreadReceived(unsigned short rawVal)
{
  emit modulationPhaserPeakSpreadReceived(Utils::raw2Phys(rawVal, 10, -5));
}

void Stomp::midiModulationPhaserStagesReceived(unsigned short rawVal)
{
  emit modulationPhaserStagesReceived((double)(2 * rawVal) + 2);
}

void Stomp::midiRotarySpeedReceived(unsigned short rawVal)
{
  emit rotarySpeedReceived((::RotarySpeed)rawVal);
}

void Stomp::midiRotaryDistanceReceived(unsigned short rawVal)
{
  emit rotaryDistanceReceived((int)rawVal);
}

void Stomp::midiRotaryBalanceReceived(unsigned short rawVal)
{
  emit rotaryBalanceReceived(Utils::raw2Phys(rawVal, 200, -100));
}

void Stomp::midiCompressorSquashReceived(unsigned short rawVal)
{
  emit compressorSquashReceived(Utils::raw2Phys(rawVal, 10, -5));
}

void Stomp::midiGraphicEQBand1Received(unsigned short rawVal)
{
  emit graphicEQBand1Received(Utils::raw2Phys(rawVal, 24, -12));
}

void Stomp::midiGraphicEQBand2Received(unsigned short rawVal)
{
  emit graphicEQBand2Received(Utils::raw2Phys(rawVal, 24, -12));
}

void Stomp::midiGraphicEQBand3Received(unsigned short rawVal)
{
  emit graphicEQBand3Received(Utils::raw2Phys(rawVal, 24, -12));
}

void Stomp::midiGraphicEQBand4Received(unsigned short rawVal)
{
  emit graphicEQBand4Received(Utils::raw2Phys(rawVal, 24, -12));
}

void Stomp::midiGraphicEQBand5Received(unsigned short rawVal)
{
  emit graphicEQBand5Received(Utils::raw2Phys(rawVal, 24, -12));
}

void Stomp::midiGraphicEQBand6Received(unsigned short rawVal)
{
  emit graphicEQBand6Received(Utils::raw2Phys(rawVal, 24, -12));
}

void Stomp::midiGraphicEQBand7Received(unsigned short rawVal)
{
  emit graphicEQBand7Received(Utils::raw2Phys(rawVal, 24, -12));
}

void Stomp::midiGraphicEQBand8Received(unsigned short rawVal)
{
  emit graphicEQBand8Received(Utils::raw2Phys(rawVal, 24, -12));
}

void Stomp::midiParametricEQLowGainReceived(unsigned short rawVal)
{
  emit parametricEQLowGainReceived(Utils::raw2Phys(rawVal, 24, -12));
}

void Stomp::midiParametricEQLowFrequencyReceived(unsigned short rawVal)
{
  emit parametricEQLowFrequencyReceived((int)rawVal);
}

void Stomp::midiParametricEQHighGainReceived(unsigned short rawVal)
{
  emit parametricEQHighGainReceived(Utils::raw2Phys(rawVal, 24, -12));
}

void Stomp::midiParametricEQHighFrequencyReceived(unsigned short rawVal)
{
  emit parametricEQHighFrequencyReceived((int)rawVal);
}

void Stomp::midiParametricEQPeakGainReceived(unsigned short rawVal)
{
  emit parametricEQPeakGainReceived(Utils::raw2Phys(rawVal, 24, -12));
}

void Stomp::midiParametricEQPeakFrequencyReceived(unsigned short rawVal)
{
  emit parametricEQPeakFrequencyReceived((int)rawVal);
}

void Stomp::midiParametricEQPeakQFactorReceived(unsigned short rawVal)
{
  emit parametricEQPeakQFactorReceived((int)rawVal);
}

void Stomp::midiParametricEQPeakGain2Received(unsigned short rawVal)
{
  emit parametricEQPeakGain2Received(Utils::raw2Phys(rawVal, 24, -12));
}

void Stomp::midiParametricEQPeakFrequency2Received(unsigned short rawVal)
{
  emit parametricEQPeakFrequency2Received((int)rawVal);
}

void Stomp::midiParametricEQPeakQFactor2Received(unsigned short rawVal)
{
  emit parametricEQPeakQFactor2Received((int)rawVal);
}

void Stomp::midiWahPeakRangeReceived(unsigned short rawVal)
{
  emit wahPeakRangeReceived(Utils::raw2Phys(rawVal, 200, -100));
}

void Stomp::midiDuckingReceived(unsigned short rawVal)
{
  emit duckingReceived(Utils::raw2Phys(rawVal, 10, -5));
}

void Stomp::midiIntensityReceived(unsigned short rawVal)
{
  emit intensityReceived(Utils::raw2Phys(rawVal, 100, 0));
}

void Stomp::midiVoiceMixReceived(unsigned short rawVal)
{
  emit voiceMixReceived(Utils::raw2Phys(rawVal, 10, -5));
}

void Stomp::midiVoice1PitchReceived(unsigned short rawVal)
{
  emit voice1PitchReceived(rawVal - 64);
}

void Stomp::midiVoice2PitchReceived(unsigned short rawVal)
{
  emit voice2PitchReceived(rawVal - 64);
}

void Stomp::midiDetuneReceived(unsigned short rawVal)
{
  emit detuneReceived(Utils::raw2Phys(rawVal, 10, 0));void applyModulationCrossover(int modulationCrossover);
}

void Stomp::midiSmoothChordsReceived(unsigned short rawVal)
{
  emit smoothChordsReceived(Utils::raw2Bool(rawVal));
}

void Stomp::midiPureTuningReceived(unsigned short rawVal)
{
  emit pureTuningReceived(Utils::raw2Bool(rawVal));
}

void Stomp::midiVoice1IntervalReceived(unsigned short rawVal)
{
  emit voice1IntervalReceived((int)rawVal);
}

void Stomp::midiVoice2IntervalReceived(unsigned short rawVal)
{
  emit voice2IntervalReceived((int)rawVal);
}

void Stomp::midiKeyReceived(unsigned short rawVal)
{
  emit keyReceived((int)rawVal);
}

void Stomp::midiFormantShiftOnOffReceived(unsigned short rawVal)
{
  emit formantShiftOnOffReceived(Utils::raw2Bool(rawVal));
}

void Stomp::midiFormantShiftReceived(unsigned short rawVal)
{
  emit formantShiftReceived(Utils::raw2Phys(rawVal, 10, -5));
}

void Stomp::midiLowCutReceived(unsigned short rawVal)
{
  emit lowCutReceived((int)rawVal);
}

void Stomp::midiHighCutReceived(unsigned short rawVal)
{
  emit highCutReceived((int)rawVal);
}

void Stomp::midiDelayMixReceived(unsigned short rawVal)
{
  emit delayMixReceived((int)rawVal);
}

void Stomp::midiDelay1TimeReceived(unsigned short rawVal)
{
  emit delay1TimeReceived(Utils::raw2Phys(rawVal, 2000, 0));
}

void Stomp::midiDelay2RatioReceived(unsigned short rawVal)
{
  emit delay2RatioReceived(Utils::raw2Phys(rawVal, 100, 0));
}

void Stomp::midiDelayNoteValue1Received(unsigned short rawVal)
{
  emit delayNoteValue1Received((int)rawVal);
}

void Stomp::midiDelayNoteValue2Received(unsigned short rawVal)
{
  emit delayNoteValue2Received((int)rawVal);
}

void Stomp::midiDelayFeedbackReceived(unsigned short rawVal)
{
  emit delayFeedbackReceived(Utils::raw2Phys(rawVal, 100, 0));
}

void Stomp::midiDelayToTempoReceived(unsigned short rawVal)
{
  emit delayToTempoReceived((int)rawVal);
}

void Stomp::midiDelayModulationReceived(unsigned short rawVal)
{
  emit delayModulationReceived(Utils::raw2Phys(rawVal, 10, 0));
}
