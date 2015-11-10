#include <QWidget>
#include <QPixmap>
#include "QToasterLCD.h"

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
                                                           {StereoWeidener,         "WIDE"},
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
  QString skin = ":/resources/LCD.png";

  QPixmap masterPixmap(skin);

  int width = masterPixmap.width();
  int height = masterPixmap.height() / (NoOfColors + 1); // to compansate a bug in JKnobMan:
                                                         // as JKnobMan doesn't create the last frame properly
                                                         // there must be an additional one
  if(!masterPixmap.isNull())
  {
    int x = 0;
    int y = 0;
    for(int i = 0; i < NoOfColors; i++)
    {
      y = i * height;
      mSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
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
