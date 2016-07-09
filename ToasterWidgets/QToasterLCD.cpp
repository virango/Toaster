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
#include <QWidget>
#include <QPixmap>
#include "QToasterLCD.h"

QList<QPixmap> QToasterLCD::sSkinPixmaps;

QMap<FXType, QString> QToasterLCD::sFXType2ShortNameMap = {{None,                   "-"},
                                                           {WahWah,                 "WWAH"},
                                                           {WahLowPass,             "WLPF"},
                                                           {WahHighPass,            "WHPF"},
                                                           {WahVowelFilter,         "WVOW"},
                                                           {WahPhaser,              "WPHA"},
                                                           {WahFlanger,             "WFLA"},
                                                           {WahRateReducer,         "WRR"},
                                                           {WahRingModulator,       "WRM"},
                                                           {WahFrequencyShifter,    "W FS"},
                                                           {WahFormantShifter,      "WFORM"},
                                                           {BitShaper,              "BIT"},
                                                           {RectiShaper,            "RECT"},
                                                           {SoftShaper,             "SHAPR"},
                                                           {HardShaper,             "SHAPR"},
                                                           {WaveShaper,             "SHAPR"},
                                                           {GreenScream,            "DIST"},
                                                           {PlusDS,                 "DIST"},
                                                           {OneDS,                  "DIST"},
                                                           {Muffin,                 "DIST"},
                                                           {MouseDS,                "DIST"},
                                                           {FuzzDS,                 "DIST"},
                                                           {MetalDS,                "DIST"},
                                                           {TrebleBooster,          "BOOST"},
                                                           {LeadBooster,            "BOOST"},
                                                           {PureBooster,            "BOOST"},
                                                           {WahPedalBooster,        "BOOST"},
                                                           {GraphicEqualizer,       "EQ"},
                                                           {StudioEqualizer,        "EQ"},
                                                           {MetalEqualizer,         "EQ"},
                                                           {StereoWidener,          "WIDE"},
                                                           {Compressor,             "COMP"},
                                                           {NoiseGate21,            "GATE"},
                                                           {NoiseGate41,            "GATE"},
                                                           {VintageChorus,          "CHO"},
                                                           {HyperChorus,            "CHO"},
                                                           {AirChorus,              "CHO"},
                                                           {MicroPitch,             "µPTC"},
                                                           {Vibrato,                "VIB"},
                                                           {RotarySpeaker,          "ROT"},
                                                           {Tremolo,                "TREM"},
                                                           {Phaser,                 "PHA"},
                                                           {PhaserVibe,             "PHA"},
                                                           {PhaserOneway,           "PHA"},
                                                           {Flanger,                "FLA"},
                                                           {FlangerOneway,          "FLA"},
                                                           {Space,                  "SPCE"},
                                                           {LegacyDelay,            "LDLY"},
                                                           {Transpose,              "TRP"},
                                                           {PedalPitch,             "PPTC"},
                                                           {PedalVinylStop,         "PVSP"},
                                                           {ChromaticPitch,         "CHROM"},
                                                           {HarmonicPitch,          "HARM"},
                                                           {AnalogOctaver,          "OCT"},
                                                           {LoopMono,               "LOOP"},
                                                           {LoopStereo,             "LOOP"},
                                                           {LoopDistortion,         "LOOP"}};

QMap<QToasterLCD::Color, QString> QToasterLCD::sColor2StyleSheetsMap = {{Standard    , COLOR_STANDARD},
                                                                        {Orange      , COLOR_ORANGE},
                                                                        {Red         , COLOR_RED},
                                                                        {Yellow      , COLOR_YELLOW},
                                                                        {Cyan        , COLOR_CYAN},
                                                                        {Blue        , COLOR_BLUE},
                                                                        {Purple      , COLOR_PURPLE},
                                                                        {White       , COLOR_WHITE},
                                                                        {Green       , COLOR_GREEN}};


QToasterLCD::QToasterLCD(QWidget* parent)
  : QWidget(parent)
  , mColor(Standard)
  , mMaxPage(Page2)
  , mCurrentPage(Page1)
  , mpCtxMenuProvider(NULL)
{
}

QToasterLCD::~QToasterLCD()
{
}

void QToasterLCD::createSkin()
{
  if(sSkinPixmaps.isEmpty())
  {
    QString skin = ":/resources/LCD.png";

    QPixmap masterPixmap(skin);

    int width = masterPixmap.width();
    int height = masterPixmap.height() / (NoOfColors);
    
    if(!masterPixmap.isNull())
    {
      int x = 0;
      int y = 0;
      for(int i = 0; i < NoOfColors; i++)
      {
        y = i * height;
        sSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
      }
    }
  }
}

void QToasterLCD::displayStompEnabled(QWidget& w, bool enabled)
{
  QString textColor = sColor2StyleSheetsMap[mColor];
  if(enabled)
    w.setStyleSheet(QString(ENABLED).arg(textColor));
  else
    w.setStyleSheet(QString(DISABLED).arg(textColor));
}

void QToasterLCD::setColor(Color color)
{
  mColor = color;
  update();
}

void QToasterLCD::setCurrentPage(Page page)
{
  if(page <= mMaxPage)
    mCurrentPage = page;
}

void QToasterLCD::setMaxPage(Page page)
{
  mMaxPage = page;
}
