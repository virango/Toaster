#include "Stomp.h"

Stomp::Stomp(StompInstance instance)
  : QObject(0)
  , StompMidi(instance)
  , mFXType(None)
{
}

Stomp::~Stomp()
{
}

void Stomp::requestAllValues()
{
  midiRequestOnOff();
  midiRequestType();
}

// slots
void Stomp::applyOnOff(bool onOff)
{
  midiApplyOnOff(bool2Raw(onOff));
  midiRequestOnOff();
}

void Stomp::applyType(FXType type)
{
  midiApplyType(fxType2Raw(type));
  midiRequestType();
}

void Stomp::applyMix(double mix)
{
  midiApplyMix(phys2Raw(mix, 100, 0));
}

void Stomp::applyVolume(double volume)
{
  midiApplyVolume(phys2Raw(volume, 10, -5));
}

void Stomp::applyStereo(double stereo)
{
  //midiApplyStereo(phys2Raw(stereo, , ));
}

void Stomp::applyWahManual(double wahManual)
{
  midiApplyWahManual(phys2Raw(wahManual, 10, 0));
}

void Stomp::applyWahPeak(double wahPeak)
{
  midiApplyWahPeak(phys2Raw(wahPeak, 10, 0));
}

void Stomp::applyWahRange(double wahRange)
{
  midiApplyWahRange(phys2Raw(wahRange, 200, -100));
}

void Stomp::applyWahPedalMode(::WahPedalMode wahPedalMode)
{
  midiApplyWahPedalMode((unsigned short)wahPedalMode);
}

void Stomp::applyWahTouchAttack(double wahTouchAttack)
{
  midiApplyWahTouchAttack(phys2Raw(wahTouchAttack, 10, 0));
}

void Stomp::applyWahTouchRelease(double wahTouchRelease)
{
  midiApplyWahTouchRelease(phys2Raw(wahTouchRelease, 10, 0));
}

void Stomp::applyWahTouchBoost(double wahTouchBoost)
{
  midiApplyWahTouchBoost(phys2Raw(wahTouchBoost, 10, 0));
}

void Stomp::applyDistortionShaperDrive(double distortionShaperDrive)
{
  midiApplyDistortionShaperDrive(phys2Raw(distortionShaperDrive, 10, 0));
}

void Stomp::applyDistortionBoosterTone(double distortionBoosterTone)
{
  midiApplyDistortionBoosterTone(phys2Raw(distortionBoosterTone, 10, -5));
}

void Stomp::applyCompressorGateIntensity(double compressorGateIntensity)
{
  midiApplyCompressorGateIntensity(phys2Raw(compressorGateIntensity, 10, 0));
}

void Stomp::applyCompressorAttack(double compressorAttack)
{
  midiApplyCompressorAttack(phys2Raw(compressorAttack, 10 , 0));
}

void Stomp::applyModulationRate(double modulationRate)
{
  midiApplyModulationRate(phys2Raw(modulationRate, 10, 0));
}

void Stomp::applyModulationRate(unsigned short modulationRate)
{
  midiApplyModulationRate(modulationRate);
}

void Stomp::applyModulationDepth(double modulationDepth)
{
  midiApplyModulationDepth(phys2Raw(modulationDepth, 10, 0));
}

void Stomp::applyModulationFeedback(double modulationFeedback)
{
  midiApplyModulationFeedback(phys2Raw(modulationFeedback, 100, 0));
}

void Stomp::applyModulationCrossover(double modulationCrossover)
{
  midiApplyModulationCrossover((unsigned short)modulationCrossover);
}

void Stomp::applyModulationHyperChorusAmount(double modulationHyperChorusAmount)
{
  midiApplyModulationHyperChorusAmount(phys2Raw(modulationHyperChorusAmount, 2, 1));
}

void Stomp::applyModulationManual(double modulationManual)
{
  midiApplyModulationManual(phys2Raw(modulationManual, 10, 0));
}

void Stomp::applyModulationPhaserPeakSpread(double modulationPhaserPeakSpread)
{
  midiApplyModulationPhaserPeakSpread(phys2Raw(modulationPhaserPeakSpread, 10, -5));
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
  midiApplyRotaryBalance(phys2Raw(rotaryBalance, 200, -100));
}

void Stomp::applyCompressorSquash(double compressorSquash)
{
  midiApplyCompressorSquash(phys2Raw(compressorSquash, 10, -5));
}

void Stomp::applyGraphicEQBand1(double graphicEQBand)
{
  midiApplyGraphicEQBand1(phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyGraphicEQBand2(double graphicEQBand)
{
  midiApplyGraphicEQBand2(phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyGraphicEQBand3(double graphicEQBand)
{
  midiApplyGraphicEQBand3(phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyGraphicEQBand4(double graphicEQBand)
{
  midiApplyGraphicEQBand4(phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyGraphicEQBand5(double graphicEQBand)
{
  midiApplyGraphicEQBand5(phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyGraphicEQBand6(double graphicEQBand)
{
  midiApplyGraphicEQBand6(phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyGraphicEQBand7(double graphicEQBand)
{
  midiApplyGraphicEQBand7(phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyGraphicEQBand8(double graphicEQBand)
{
  midiApplyGraphicEQBand8(phys2Raw(graphicEQBand, 24, -12));
}

void Stomp::applyParametricEQLowGain(double gain)
{
  midiApplyParametricEQLowGain(phys2Raw(gain, 24, -12));
}

void Stomp::applyParametricEQLowFrequency(double frequency)
{
  midiApplyParametricEQLowFrequency((unsigned short)frequency);
}

void Stomp::applyParametricEQHighGain(double gain)
{
  midiApplyParametricEQHighGain(phys2Raw(gain, 24, -12));
}

void Stomp::applyParametricEQHighFrequency(double frequency)
{
  midiApplyParametricEQHighFrequency((unsigned short)frequency);
}

void Stomp::applyParametricEQPeakGain(double gain)
{
  midiApplyParametricEQPeakGain(phys2Raw(gain, 24, -12));
}

void Stomp::applyParametricEQPeakFrequency(double frequency)
{
  midiApplyParametricEQPeakFrequency((unsigned short)frequency);
}

void Stomp::applyParametricEQPeakQFactor(double factor)
{
  midiApplyParametricEQPeakQFactor((unsigned short)factor);
}

void Stomp::applyParametricEQPeakGain2(double gain)
{
  midiApplyParametricEQPeakGain2(phys2Raw(gain, 24, -12));
}

void Stomp::applyParametricEQPeakFrequency2(double frequency)
{
  midiApplyParametricEQPeakFrequency2((unsigned short)frequency);
}

void Stomp::applyParametricEQPeakQFactor2(double factor)
{
  midiApplyParametricEQPeakQFactor2((unsigned short)factor);
}

void Stomp::applyWahPeakRange(double wahPeakRange)
{
  midiApplyWahPeakRange(phys2Raw(wahPeakRange, 200, -100));
}

void Stomp::applyDucking(double ducking)
{
  midiApplyDucking(phys2Raw(ducking, 10, -5));
}

void Stomp::applyIntensity(double mix)
{
  midiApplyIntensity(phys2Raw(mix, 100, 0));
}

void Stomp::applyVoiceMix(double voiceMix)
{
  midiApplyVoiceMix(phys2Raw(voiceMix, 10, -5));
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
  midiApplyDetune(phys2Raw(detune, 10, 0));
}

void Stomp::applySmoothChords(bool onOff)
{
  midiApplySmoothChords(bool2Raw(onOff));
}

void Stomp::applyPureTuning(bool onOff)
{
  midiApplyPureTuning(bool2Raw(onOff));
}

void Stomp::applyKey(double key)
{
  //midiApplyKey(phys2Raw(key, , ));
}

void Stomp::applyFormantShiftOnOff(bool onOff)
{
  midiApplyFormantShiftOnOff(bool2Raw(onOff));
}

void Stomp::applyFormantShift(double shift)
{
  midiApplyFormantShift(phys2Raw(shift, 10, -5));
}

void Stomp::applyLowCut(double lowCut)
{
  midiApplyLowCut((unsigned int)lowCut);
}

void Stomp::applyHighCut(double highCut)
{
  midiApplyHighCut((unsigned short)highCut);
}

// StompMidi callbacks
void Stomp::midiTypeReceived(unsigned short rawVal)
{
  mFXType = raw2FXType(rawVal);
  emit typeReceived(mFXType);
}

void Stomp::midiOnOffReceived(unsigned short rawVal)
{
  emit onOffReceived(raw2Bool(rawVal));
}

void Stomp::midiMixReceived(unsigned short rawVal)
{
  emit mixReceived(raw2Phys(rawVal, 100, 0));
}

void Stomp::midiVolumeReceived(unsigned short rawVal)
{
  emit volumeReceived(raw2Phys(rawVal, 10, -5));
}

void Stomp::midiStereoReceived(unsigned short rawVal)
{
  //emit stereoReceived(raw2Phys(rawVal, , ));
}

void Stomp::midiWahManualReceived(unsigned short rawVal)
{
  emit wahManualReceived(raw2Phys(rawVal, 10, 0));
}

void Stomp::midiWahPeakReceived(unsigned short rawVal)
{
  emit wahPeakReceived(raw2Phys(rawVal, 10, 0));
}

void Stomp::midiWahRangeReceived(unsigned short rawVal)
{
  emit wahRangeReceived(raw2Phys(rawVal, 200, -100));
}

void Stomp::midiWahPedalModeReceived(unsigned short rawVal)
{
  emit wahPedalModeReceived((WahPedalMode)rawVal);
}

void Stomp::midiWahTouchAttackReceived(unsigned short rawVal)
{
  emit wahTouchAttackReceived(raw2Phys(rawVal, 10, 0));
}

void Stomp::midiWahTouchReleaseReceived(unsigned short rawVal)
{
  emit wahTouchReleaseReceived(raw2Phys(rawVal, 10, 0));
}

void Stomp::midiWahTouchBoostReceived(unsigned short rawVal)
{
  emit wahTouchBoostReceived(raw2Phys(rawVal, 10, 0));
}

void Stomp::midiDistortionShaperDriveReceived(unsigned short rawVal)
{
  emit distortionShaperDriveReceived(raw2Phys(rawVal, 10, 0));
}

void Stomp::midiDistortionBoosterToneReceived(unsigned short rawVal)
{
  emit distortionBoosterToneReceived(raw2Phys(rawVal, 10, -5));
}

void Stomp::midiCompressorGateIntensityReceived(unsigned short rawVal)
{
  emit compressorGateIntensityReceived(raw2Phys(rawVal, 10, 0));
}

void Stomp::midiCompressorAttackReceived(unsigned short rawVal)
{
  emit compressorAttackReceived(raw2Phys(rawVal, 10, 0));
}

void Stomp::midiModulationRateReceived(unsigned short rawVal)
{
  // there seems to be a bug in the kpa: it sends values between 0..127
  double physVal = ((rawVal * 10.0) / 127.0);
  emit modulationRateReceived(physVal, rawVal);
}

void Stomp::midiModulationDepthReceived(unsigned short rawVal)
{
  emit modulationDepthReceived(raw2Phys(rawVal, 10, 0));
}

void Stomp::midiModulationFeedbackReceived(unsigned short rawVal)
{
  emit modulationFeedbackReceived(raw2Phys(rawVal, 100, 0));
}

void Stomp::midiModulationCrossoverReceived(unsigned short rawVal)
{
  emit modulationCrossoverReceived((double)rawVal);
}

void Stomp::midiModulationHyperChorusAmountReceived(unsigned short rawVal)
{
  emit modulationHyperChorusAmountReceived(raw2Phys(rawVal, 2, 1));
}

void Stomp::midiModulationManualReceived(unsigned short rawVal)
{
  emit modulationManualReceived(raw2Phys(rawVal, 10, 0));
}

void Stomp::midiModulationPhaserPeakSpreadReceived(unsigned short rawVal)
{
  emit modulationPhaserPeakSpreadReceived(raw2Phys(rawVal, 10, -5));
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
  emit rotaryBalanceReceived(raw2Phys(rawVal, 200, -100));
}

void Stomp::midiCompressorSquashReceived(unsigned short rawVal)
{
  emit compressorSquashReceived(raw2Phys(rawVal, 10, -5));
}

void Stomp::midiGraphicEQBand1Received(unsigned short rawVal)
{
  emit graphicEQBand1Received(raw2Phys(rawVal, 24, -12));
}

void Stomp::midiGraphicEQBand2Received(unsigned short rawVal)
{
  emit graphicEQBand2Received(raw2Phys(rawVal, 24, -12));
}

void Stomp::midiGraphicEQBand3Received(unsigned short rawVal)
{
  emit graphicEQBand3Received(raw2Phys(rawVal, 24, -12));
}

void Stomp::midiGraphicEQBand4Received(unsigned short rawVal)
{
  emit graphicEQBand4Received(raw2Phys(rawVal, 24, -12));
}

void Stomp::midiGraphicEQBand5Received(unsigned short rawVal)
{
  emit graphicEQBand5Received(raw2Phys(rawVal, 24, -12));
}

void Stomp::midiGraphicEQBand6Received(unsigned short rawVal)
{
  emit graphicEQBand6Received(raw2Phys(rawVal, 24, -12));
}

void Stomp::midiGraphicEQBand7Received(unsigned short rawVal)
{
  emit graphicEQBand7Received(raw2Phys(rawVal, 24, -12));
}

void Stomp::midiGraphicEQBand8Received(unsigned short rawVal)
{
  emit graphicEQBand8Received(raw2Phys(rawVal, 24, -12));
}

void Stomp::midiParametricEQLowGainReceived(unsigned short rawVal)
{
  emit parametricEQLowGainReceived(raw2Phys(rawVal, 24, -12));
}

void Stomp::midiParametricEQLowFrequencyReceived(unsigned short rawVal)
{
  emit parametricEQLowFrequencyReceived((double)rawVal);
}

void Stomp::midiParametricEQHighGainReceived(unsigned short rawVal)
{
  emit parametricEQHighGainReceived(raw2Phys(rawVal, 24, -12));
}

void Stomp::midiParametricEQHighFrequencyReceived(unsigned short rawVal)
{
  emit parametricEQHighFrequencyReceived((double)rawVal);
}

void Stomp::midiParametricEQPeakGainReceived(unsigned short rawVal)
{
  emit parametricEQPeakGainReceived(raw2Phys(rawVal, 24, -12));
}

void Stomp::midiParametricEQPeakFrequencyReceived(unsigned short rawVal)
{
  emit parametricEQPeakFrequencyReceived((double)rawVal);
}

void Stomp::midiParametricEQPeakQFactorReceived(unsigned short rawVal)
{
  emit parametricEQPeakQFactorReceived((double)rawVal);
}

void Stomp::midiParametricEQPeakGain2Received(unsigned short rawVal)
{
  emit parametricEQPeakGain2Received(raw2Phys(rawVal, 24, -12));
}

void Stomp::midiParametricEQPeakFrequency2Received(unsigned short rawVal)
{
  emit parametricEQPeakFrequency2Received((double)rawVal);
}

void Stomp::midiParametricEQPeakQFactor2Received(unsigned short rawVal)
{
  emit parametricEQPeakQFactor2Received((double)rawVal);
}

void Stomp::midiWahPeakRangeReceived(unsigned short rawVal)
{
  emit wahPeakRangeReceived(raw2Phys(rawVal, 200, -100));
}

void Stomp::midiDuckingReceived(unsigned short rawVal)
{
  emit duckingReceived(raw2Phys(rawVal, 10, -5));
}

void Stomp::midiIntensityReceived(unsigned short rawVal)
{
  emit intensityReceived(raw2Phys(rawVal, 100, 0));
}

void Stomp::midiVoiceMixReceived(unsigned short rawVal)
{
  emit voiceMixReceived(raw2Phys(rawVal, 10, -5));
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
  emit detuneReceived(raw2Phys(rawVal, 10, 0));
}

void Stomp::midiSmoothChordsReceived(unsigned short rawVal)
{
  emit smoothChordsReceived(raw2Bool(rawVal));
}

void Stomp::midiPureTuningReceived(unsigned short rawVal)
{
  emit pureTuningReceived(raw2Bool(rawVal));
}

void Stomp::midiKeyReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiFormantShiftOnOffReceived(unsigned short rawVal)
{
  emit formantShiftOnOffReceived(raw2Bool(rawVal));
}

void Stomp::midiFormantShiftReceived(unsigned short rawVal)
{
  emit formantShiftReceived(raw2Phys(rawVal, 10, -5));
}

void Stomp::midiLowCutReceived(unsigned short rawVal)
{
  emit lowCutReceived((double)rawVal);
}

void Stomp::midiHighCutReceived(unsigned short rawVal)
{
  emit highCutReceived((double)rawVal);
}


