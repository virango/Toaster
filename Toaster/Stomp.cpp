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
  //midiApplyDistortionShaperDrive(phys2Raw(distortionShaperDrive, , ));
}

void Stomp::applyDistortionBoosterTone(double distortionBoosterTone)
{
  //midiApplyDistortionBoosterTone(phys2Raw(distortionBoosterTone, , ));
}

void Stomp::applyCompressorGateIntensity(double compressorGateIntensity)
{
  //midiApplyCompressorGateIntensity(phys2Raw(compressorGateIntensity, , ));
}

void Stomp::applyCompressorAttack(double compressorAttack)
{
  //midiApplyCompressorAttack(phys2Raw(compressorAttack, , ));
}

void Stomp::applyModulationRate(double modulationRate)
{
  //midiApplyModulationRate(phys2Raw(modulationRate, , ));
}

void Stomp::applyModulationDepth(double modulationDepth)
{
  //midiApplyModulationDepth(phys2Raw(modulationDepth, , ));
}

void Stomp::applyModulationFeedback(double modulationFeedback)
{
  //midiApplyModulationFeedback(phys2Raw(modulationFeedback, , ));
}

void Stomp::applyModulationCrossover(double modulationCrossover)
{
  //midiApplyModulationCrossover(phys2Raw(modulationCrossover, , ));
}

void Stomp::applyModulationHyperChorusAmount(double modulationHyperChorusAmount)
{
  //midiApplyModulationHyperChorusAmount(phys2Raw(modulationHyperChorusAmount, , ));
}

void Stomp::applyModulationManual(double modulationManual)
{
  //midiApplyModulationManual(phys2Raw(modulationManual, , ));
}

void Stomp::applyModulationPhaserPeakSpread(double modulationPhaserPeakSpread)
{
  //midiApplyModulationPhaserPeakSpread(phys2Raw(modulationPhaserPeakSpread, , ));
}

void Stomp::applyModulationPhaserStages(double modulationPhaserStages)
{
  //midiApplyModulationPhaserStages(phys2Raw(modulationPhaserStages, , ));
}

void Stomp::applyRotarySpeed(RotarySpeed rotarySpeed)
{
  midiApplyRotarySpeed((unsigned short)rotarySpeed);
}

void Stomp::applyRotaryDistance(double rotaryDistance)
{
  //midiApplyRotaryDistance(phys2Raw(rotaryDistance, , ));
}

void Stomp::applyRotaryBalance(double rotaryBalance)
{
  //midiApplyRotaryBalance(phys2Raw(rotaryBalance, , ));
}

void Stomp::applyCompressorSquash(double compressorSquash)
{
  //midiApplyCompressorSquash(phys2Raw(compressorSquash, , ));
}

void Stomp::applyGraphicEQBand1(double graphicEQBand)
{
  //midiApplyGraphicEQBand1(phys2Raw(graphicEQBand, , ));
}

void Stomp::applyGraphicEQBand2(double graphicEQBand)
{
  //midiApplyGraphicEQBand2(phys2Raw(graphicEQBand, , ));
}

void Stomp::applyGraphicEQBand3(double graphicEQBand)
{
  //midiApplyGraphicEQBand3(phys2Raw(graphicEQBand, , ));
}

void Stomp::applyGraphicEQBand4(double graphicEQBand)
{
  //midiApplyGraphicEQBand4(phys2Raw(graphicEQBand, , ));
}

void Stomp::applyGraphicEQBand5(double graphicEQBand)
{
  //midiApplyGraphicEQBand5(phys2Raw(graphicEQBand, , ));
}

void Stomp::applyGraphicEQBand6(double graphicEQBand)
{
  //midiApplyGraphicEQBand6(phys2Raw(graphicEQBand, , ));
}

void Stomp::applyGraphicEQBand7(double graphicEQBand)
{
  //midiApplyGraphicEQBand7(phys2Raw(graphicEQBand, , ));
}

void Stomp::applyGraphicEQBand8(double graphicEQBand)
{
  //midiApplyGraphicEQBand8(phys2Raw(graphicEQBand, , ));
}

void Stomp::applyParametricEQLowGain(double gain)
{
  //midiApplyParametricEQLowGain(phys2Raw(gain, , ));
}

void Stomp::applyParametricEQLowFrequency(double frequency)
{
  //midiApplyParametricEQLowFrequency(phys2Raw(frequency, , ));
}

void Stomp::applyParametricEQHighGain(double gain)
{
  //midiApplyParametricEQHighGain(phys2Raw(gain, , ));
}

void Stomp::applyParametricEQHighFrequency(double frequency)
{
  //midiApplyParametricEQHighFrequency(phys2Raw(frequency, , ));
}

void Stomp::applyParametricEQPeakGain(double gain)
{
  //midiApplyParametricEQPeakGain(phys2Raw(gain, , ));
}

void Stomp::applyParametricEQPeakFrequency(double frequency)
{
  //midiApplyParametricEQPeakFrequency(phys2Raw(frequency, , ));
}

void Stomp::applyParametricEQPeakQFactor(double factor)
{
  //midiApplyParametricEQPeakQFactor(phys2Raw(factor, , ));
}

void Stomp::applyParametricEQPeakGain2(double gain)
{
  //midiApplyParametricEQPeakGain2(phys2Raw(gain, , ));
}

void Stomp::applyParametricEQPeakFrequency2(double frequency)
{
  //midiApplyParametricEQPeakFrequency2(phys2Raw(frequency, , ));
}

void Stomp::applyParametricEQPeakQFactor2(double factor)
{
  //midiApplyParametricEQPeakQFactor2(phys2Raw(factor, , ));
}

void Stomp::applyWahPeakRange(double wahPeakRange)
{
  midiApplyWahPeakRange(phys2Raw(wahPeakRange, 200, -100));
}

void Stomp::applyDucking(double ducking)
{
  midiApplyDucking(phys2Raw(ducking, 10, -5));
}

void Stomp::applyVoiceMix(double voiceMix)
{
  //midiApplyVoiceMix(phys2Raw(voiceMix, , ));
}

void Stomp::applyVoice1Pitch(double voice1Pitch)
{
  //midiApplyVoice1Pitch(phys2Raw(voice1Pitch, , ));
}

void Stomp::applyVoice2Pitch(double voice2Pitch)
{
  //midiApplyVoice2Pitch(phys2Raw(voice2Pitch, , ));
}

void Stomp::applyDetune(double detune)
{
  //midiApplyDetune(phys2Raw(detune, , ));
}

void Stomp::applySmoothChords(double smoothChords)
{
  //midiApplySmoothChords(phys2Raw(smoothChords, , ));
}

void Stomp::applyPureTuning(double pureTuning)
{
  //midiApplyPureTuning(phys2Raw(pureTuning, , ));
}

void Stomp::applyKey(double key)
{
  //midiApplyKey(phys2Raw(key, , ));
}


// StompMidi callbacks
void Stomp::midiTypeReceived(unsigned short rawVal)
{
  emit typeReceived(raw2FXType(rawVal));
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
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiDistortionBoosterToneReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiCompressorGateIntensityReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiCompressorAttackReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiModulationRateReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiModulationDepthReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiModulationFeedbackReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiModulationCrossoverReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiModulationHyperChorusAmountReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiModulationManualReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiModulationPhaserPeakSpreadReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiModulationPhaserStagesReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiRotarySpeedReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiRotaryDistanceReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiRotaryBalanceReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiCompressorSquashReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiGraphicEQBand1Received(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiGraphicEQBand2Received(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiGraphicEQBand3Received(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiGraphicEQBand4Received(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiGraphicEQBand5Received(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiGraphicEQBand6Received(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiGraphicEQBand7Received(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiGraphicEQBand8Received(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiParametricEQLowGainReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiParametricEQLowFrequencyReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiParametricEQHighGainReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiParametricEQHighFrequencyReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiParametricEQPeakGainReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiParametricEQPeakFrequencyReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiParametricEQPeakQFactorReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiParametricEQPeakGain2Received(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiParametricEQPeakFrequency2Received(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiParametricEQPeakQFactor2Received(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiWahPeakRangeReceived(unsigned short rawVal)
{
  emit wahPeakRangeReceived(raw2Phys(rawVal, 200, -100));
}

void Stomp::midiDuckingReceived(unsigned short rawVal)
{
  emit duckingReceived(raw2Phys(rawVal, 10, -5));
}

void Stomp::midiVoiceMixReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiVoice1PitchReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiVoice2PitchReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiDetuneReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiSmoothChordsReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiPureTuningReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

void Stomp::midiKeyReceived(unsigned short rawVal)
{
  //emit Received(raw2Phys(rawVal, , ));
}

