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
#include "LookUpTables.h"

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
