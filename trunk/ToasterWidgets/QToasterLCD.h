#ifndef QTOASTERLCD_H
#define QTOASTERLCD_H

#include <QMap>
#include "Commons.h"

#define ENABLED "background-color: rgb(50,50,50);color: rgb(255, 255, 255);border-color: rgb(0, 0, 0);border-radius: 3px;"
#define DISABLED "background-color: rgb(128,128,128);color: rgb(192, 192, 192);border-color: rgb(0, 0, 0);border-radius: 3px;"

class FXType2ShortNameMap : public QMap<FXType, QString>
{
public:
  FXType2ShortNameMap()
  {
    (*this)[None] =                   "-";
    (*this)[WahWah] =                 "WWAH";
    (*this)[WahLowPass] =             "WLPF";
    (*this)[WahHighPass] =            "WHPF";
    (*this)[WahVowelFilter] =         "WVOW";
    (*this)[WahPhaser] =              "WPHA";
    (*this)[WahFlanger] =             "WFLA";
    (*this)[WahRateReducer] =         "WRR";
    (*this)[WahRingModulator] =       "WRM";
    (*this)[WahFrequencyShifter] =    "W FS";
    (*this)[WahFormantShifter] =      "WFORM";
    (*this)[BitShaper] =              "BIT";
    (*this)[RectiShaper] =            "RECT";
    (*this)[SoftShaper] =             "SHAPR";
    (*this)[HardShaper] =             "SHAPR";
    (*this)[WaveShaper] =             "SHAPR";
    (*this)[GreenScream] =            "DIST";
    (*this)[PlusDS] =                 "DIST";
    (*this)[OneDS] =                  "DIST";
    (*this)[Muffin] =                 "DIST";
    (*this)[MouseDS] =                "DIST";
    (*this)[FuzzDS] =                 "DIST";
    (*this)[MetalDS] =                "DIST";
    (*this)[TrebleBooster] =          "BOOST";
    (*this)[LeadBooster] =            "BOOST";
    (*this)[PureBooster] =            "BOOST";
    (*this)[WahPedalBooster] =        "BOOST";
    (*this)[GraphicEqualizer] =       "EQ";
    (*this)[StudioEqualizer] =        "EQ";
    (*this)[MetalEqualizer] =         "EQ";
    (*this)[StereoWeidener] =         "WIDE";
    (*this)[Compressor] =             "COMP";
    (*this)[NoiseGate21] =            "GATE";
    (*this)[NoiseGate41] =            "GATE";
    (*this)[VintageChorus] =          "CHO";
    (*this)[HyperChorus] =            "CHO";
    (*this)[AirChorus] =              "CHO";
    (*this)[MicroPitch] =             "µPTC";
    (*this)[Vibrato] =                "VIB";
    (*this)[RotarySpeaker] =          "ROT";
    (*this)[Tremolo] =                "TREM";
    (*this)[Phaser] =                 "PHA";
    (*this)[PhaserVibe] =             "PHA";
    (*this)[PhaserOneway] =           "PHA";
    (*this)[Flanger] =                "FLA";
    (*this)[FlangerOneway] =          "FLA";
    (*this)[Space] =                  "SPCE";
    (*this)[Transpose] =              "TRP";
    (*this)[PedalPitch] =             "PPTC";
    (*this)[PedalVinylStop] =         "PVSP";
    (*this)[ChromaticPitch] =         "CHROM";
    (*this)[HarmonicPitch] =          "HARM";
    (*this)[AnalogOctaver] =          "OCT";
    (*this)[LoopMono] =               "LOOP";
    (*this)[LoopStereo] =             "LOOP";
    (*this)[LoopDistortion] =         "LOOP";
  }

  ~FXType2ShortNameMap() { clear(); }


};

extern FXType2ShortNameMap sFXType2ShortNameMap;


#endif // QTOASTERLCD_H
