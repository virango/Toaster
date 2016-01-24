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
#ifndef COMMONDEFS_H
#define COMMONDEFS_H

#include <vector>
#include <QString>
#include <QtCore>

using namespace std;

typedef vector<unsigned char> ByteArray;
#define INIT_FROM(x) x, x + sizeof(x)
#define VEC_INSERT(x, y) x.insert(x.end(), y.begin(), y.end())

#define BYTEARRAYDECL(Name) \
  static const ByteArray s##Name;

#define BYTEARRAYDEF(Class, Name, ...) \
  const ByteArray Class::s##Name = {__VA_ARGS__};

enum FXType
{
  None,                   // -        0x00
//-----orange---------------------
  WahWah,                 // WWAH     0x01
  WahLowPass,             // WLPF     0x02
  WahHighPass,            // WHPF     0x03
  WahVowelFilter,         // WVOW     0x04
  WahPhaser,              // WPHA     0x06
  WahFlanger,             // WFLA     0x07
  WahRateReducer,         // WRR      0x08
  WahRingModulator,       // WRM      0x09
  WahFrequencyShifter,    // W FS     0x0A
  WahFormantShifter,      // WFORM    0x0C
//-----red------------------------
  BitShaper,              // BIT      0x11
  RectiShaper,            // RECT     0x12
  SoftShaper,             // SHAPR    0x13
  HardShaper,             // SHAPR    0x14
  WaveShaper,             // SHAPR    0x15
  GreenScream,            // DIST     0x21
  PlusDS,                 // DIST     0x22
  OneDS,                  // DIST     0x23
  Muffin,                 // DIST     0x24
  MouseDS,                // DIST     0x25
  FuzzDS,                 // DIST     0x26
  MetalDS,                // DIST     0x27
  TrebleBooster,          // BOOST    0x71
  LeadBooster,            // BOOST    0x72
  PureBooster,            // BOOST    0x73
  WahPedalBooster,        // BOOST    0x74
//-----yellow---------------------
  GraphicEqualizer,       // EQ       0x61
  StudioEqualizer,        // EQ       0x62
  MetalEqualizer,         // EQ       0x63
  StereoWeidener,         // WIDE     0x65
//-----cyan-----------------------
  Compressor,             // COMP     0x31
  NoiseGate21,            // GATE     0x39
  NoiseGate41,            // GATE     0x3A
//-----blue-----------------------
  VintageChorus,          // CHO      0x41
  HyperChorus,            // CHO      0x42
  AirChorus,              // CHO      0x43
  MicroPitch,             // µPTC     0x47
  Vibrato,                // VIB      0x44
  RotarySpeaker,          // ROT      0x45
  Tremolo,                // TREM     0x46
//-----purple---------------------
  Phaser,                 // PHA      0x51
  PhaserVibe,             // PHA      0x52
  PhaserOneway,           // PHA      0x53
  Flanger,                // FLA      0x59
  FlangerOneway,          // FLA      0x5B
//-----green----------------------
  Space,                  // SPCE     0x40
//-----white----------------------
  Transpose,              // TRP      0x81
  PedalPitch,             // PPTC     0x0B
  PedalVinylStop,         // PVSP     0x0D
  ChromaticPitch,         // CHROM    0x82
  HarmonicPitch,          // HARM     0x83
  AnalogOctaver,          // OCT      0x84
  LoopMono,               // LOOP     0x79
  LoopStereo,             // LOOP     0x7A
  LoopDistortion          // LOOP     0x7B
};

enum DelayType
{
  TapDelay = 1,
  FreeDelay = 2,
  AnalogDelay = 3
};

enum ReverbType
{
  Hall = 1,
  LargeRoom = 2,
  SmallRoom = 3,
  Ambience = 4,
  Matchbox = 5
};

enum DelayRatio
{
  One2Four,
  Two2Four,
  Three2Four,
  Four2Four,
  Four2Three,
  Four2Two,
  Four2One
};

enum DelayClock
{
  OneThirtySecond,
  OneSixteenth,
  TwoSixteenth,
  ThreeSixteenth,
  FourSixteenth,
  FiveSixteenth,
  SixSixteenth,
  SevenSixteenth,
  EightSixteenth,
  OneTwentyFourth,
  OneTwelfth,
  TwoTwelfth,
  FourTwelfth
};

enum WahPedalMode
{
  Off,
  Touch,
  On,
  BypassAtStop,
  BypassAtHeel,
  BypassAtToe
};


enum RotarySpeed
{
  Slow,
  Fast
};


enum StompInstance
{
  StompA,
  StompB,
  StompC,
  StompD,
  StompX,
  StompMOD
};

struct FXDefinition
{
  QString         mName;
  QString         mShort;
  unsigned char   mSysExCode;
};

Q_DECLARE_METATYPE(::FXType)
Q_DECLARE_METATYPE(::DelayType)
Q_DECLARE_METATYPE(::ReverbType)
Q_DECLARE_METATYPE(::DelayRatio)
Q_DECLARE_METATYPE(::WahPedalMode)
Q_DECLARE_METATYPE(::DelayClock)
#endif // COMMONDEFS_H

