#include "LookUpTables.h"
#include "RotaryDistanceValues.h"
#include "RigVolumeValues.h"
#include "MainVolumeValues.h"
#include "MixValues.h"
#include "FrequencyValues.h"
#include "TremoloRateValues.h"
#include "QFactorValues.h"
#include "FlangerRateValues.h"
#include "VoiceIntervalValues.h"

QMap<StompInstance, QString> LookUpTables::sStompInstanceNames = {{StompA, "Stomp A"},
                                                                  {StompB, "Stomp B"},
                                                                  {StompC, "Stomp C"},
                                                                  {StompD, "Stomp D"},
                                                                  {StompX, "Effect x"},
                                                                  {StompMOD, "Modulation Effect"}};

QMap<DelayType, QString> LookUpTables::sDelayTypeNames = {{TapDelay, "Tap Delay"},
                                                          {FreeDelay, "Free Delay"},
                                                          {AnalogDelay, "Analog Delay"}};

QMap<ReverbType, QString> LookUpTables::sReverbTypeNames = {{Hall, "Hall"},
                                                            {LargeRoom, "Large Room"},
                                                            {SmallRoom, "Small Room"},
                                                            {Ambience, "Ambience"},
                                                            {Matchbox, "Matchbox"}};

QMap<FXType, QString> LookUpTables::sStompFXNames = {{None, "None"},
                                                     {WahWah, "Wah Wah"},
                                                     {WahLowPass, "Wah Low Pass"},
                                                     {WahHighPass, "Wah High Pass"},
                                                     {WahVowelFilter, "Wah Vowel Filter"},
                                                     {WahPhaser, "Wah Phaser"},
                                                     {WahFlanger, "Wah Flanger"},
                                                     {WahRateReducer, "Wah Rate Reducer"},
                                                     {WahRingModulator, "Wah Ring Modulator"},
                                                     {WahFrequencyShifter, "Wah Freq Shifter"},
                                                     {WahFormantShifter, "Wah Formant Shifter"},
                                                     {BitShaper, "Bit Shaper"},
                                                     {RectiShaper, "Recti Shaper"},
                                                     {SoftShaper, "Soft Shaper"},
                                                     {HardShaper, "Hard Shaper"},
                                                     {WaveShaper, "Wave Shaper"},
                                                     {GreenScream, "Green Scream"},
                                                     {PlusDS, "Plus DS"},
                                                     {OneDS, "One DS"},
                                                     {Muffin, "Muffin"},
                                                     {MouseDS, "Mouse DS"},
                                                     {FuzzDS, "Fuzz DS"},
                                                     {MetalDS, "Metal DS"},
                                                     {TrebleBooster, "Treble Booster"},
                                                     {LeadBooster, "Lead Booster"},
                                                     {PureBooster, "Pure Booster"},
                                                     {WahPedalBooster, "Wah Pedal Booster"},
                                                     {GraphicEqualizer, "Graphic Equalizer"},
                                                     {StudioEqualizer, "Studio Equalizer"},
                                                     {MetalEqualizer, "Metal Equalizer"},
                                                     {StereoWeidener, "Stereo Weidener"},
                                                     {Compressor, "Compressor"},
                                                     {NoiseGate21, "Noise Gate 2:1"},
                                                     {NoiseGate41, "Noise Gate 4:1"},
                                                     {VintageChorus, "Vintage Chorus"},
                                                     {HyperChorus, "Hyper Chorus"},
                                                     {AirChorus, "Air Chorus"},
                                                     {MicroPitch, "Micro Pitch"},
                                                     {Vibrato, "Vibrato"},
                                                     {RotarySpeaker, "Rotary Speaker"},
                                                     {Tremolo, "Tremolo"},
                                                     {Phaser, "Phaser"},
                                                     {PhaserVibe, "Phaser Vibe"},
                                                     {PhaserOneway, "Phaser Oneway"},
                                                     {Flanger, "Flanger"},
                                                     {FlangerOneway, "Flanger Oneway"},
                                                     {Space, "Space"},
                                                     {Transpose, "Transpose"},
                                                     {PedalPitch, "Pedal Pitch"},
                                                     {PedalVinylStop, "Pedal Vinyl Stop"},
                                                     {ChromaticPitch, "Chromatic Pitch"},
                                                     {HarmonicPitch, "Harmonic Pitch"},
                                                     {AnalogOctaver, "Analog Octaver"},
                                                     {LoopMono, "Loop Mono"},
                                                     {LoopStereo, "Loop Stereo"},
                                                     {LoopDistortion, "Loop Distortion"}};

QVector<QPair<int, QString>> LookUpTables::sRotaryDistanceValues = {ROTARY_DISTANCE_VALUES};
QVector<QPair<int, QString>> LookUpTables::sRigVolumeValues = {RIG_VOLUME_VALUES};
QVector<QPair<int, QString>> LookUpTables::sMainVolumeValues = {MAIN_VOLUME_VALUES};
QVector<QPair<int, QString>> LookUpTables::sMixValues = {MIX_VALUES};
QVector<QPair<int, QString>> LookUpTables::sFrequencyValues = {FREQUENCY_VALUES};
QVector<QPair<int, QString>> LookUpTables::sTremoloRateValues = {TREMOLO_RATE_VALUES};
QVector<QPair<int, QString>> LookUpTables::sQFactorValues = {QFACTOR_VALUES};
QVector<QPair<int, QString>> LookUpTables::sFlangerRateValues = {FLANGER_RATE_VALUES};
QVector<QPair<int, QString>> LookUpTables::sVoiceIntervalValues = {VOICE_INTERVAL_VALUES};

LookUpTables LookUpTables::singleton;

LookUpTables::LookUpTables()
{
}

QVector<QString> LookUpTables::sNotes =
{
  "C",
  "C#",
  "D",
  "D#",
  "E",
  "F",
  "F#",
  "G",
  "G#",
  "A",
  "A#",
  "B"
};

QString LookUpTables::raw2Note(unsigned short rawVal)
{
  if(rawVal <= 12)
  {
    return sNotes[rawVal];
  }
  return "_";
}

QString LookUpTables::stompInstanceName(StompInstance instance)
{
  return sStompInstanceNames[instance];
}

QString LookUpTables::stompFXName(FXType fxType)
{
  return sStompFXNames[fxType];
}

QString LookUpTables::delayTypeName(DelayType delayType)
{
  return sDelayTypeNames[delayType];
}

QString LookUpTables::reverbTypeName(ReverbType reverbType)
{
  return sReverbTypeNames[reverbType];
}
