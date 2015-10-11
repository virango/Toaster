#ifndef QTOASTERLCD_H
#define QTOASTERLCD_H

#include <QStackedWidget>
#include "Commons.h"
#include "ToasterWidgetsLib.h"

namespace Ui {
class QToasterLCD;
}

struct ICtxMenuProvider;

class TOASTERWIDGETS_EXPORT QToasterLCD : public QStackedWidget
{
  Q_OBJECT
  Q_ENUMS(Mode)
  Q_ENUMS(Color)
  Q_PROPERTY(Mode mode READ mode WRITE setMode)
  Q_PROPERTY(Color color READ color WRITE setColor)

public:
  explicit QToasterLCD(QWidget *parent = 0);
  ~QToasterLCD();

  enum Mode
  {
    Browser,
    Perform,
    Profiler,
    StompEdit
  };

  enum Color
  {
    Standard    = 0,
    Orange      = 1,
    Red         = 2,
    Yellow      = 3,
    Cyan        = 4,
    Blue        = 5,
    Purple      = 6,
    White       = 7,
    Green       = 8,
    NoOfColors  = 9      // must be always last
  };

  //enum StompOInstance

  Mode mode() const { return mMode; }
  Color color() const { return mColor; }
  void setCtxMenuProvider(ICtxMenuProvider* ctxMenuProvider) { mpCtxMenuProvider = ctxMenuProvider; }

  QStringList getBrowserModeViews();

signals:
  void browserModeViewChanged(int view);

public slots:
  void setMode(QToasterLCD::Mode mode);
  void setColor(QToasterLCD::Color color);

  void setStompAFXType(FXType fxType);
  void setStompBFXType(FXType fxType);
  void setStompCFXType(FXType fxType);
  void setStompDFXType(FXType fxType);
  void setStompXFXType(FXType fxType);
  void setStompModFXType(FXType fxType);

  void setStompAEnabled(bool enabled);
  void setStompBEnabled(bool enabled);
  void setStompCEnabled(bool enabled);
  void setStompDEnabled(bool enabled);
  void setStompXEnabled(bool enabled);
  void setStompModEnabled(bool enabled);
  void setDelayEnabled(bool enabled);
  void setReverbEnabled(bool enabled);

  void setBrowserModeBassValueText(const QString& value);
  void setBrowserModeMiddleValueText(const QString& value);
  void setBrowserModeTrebleValueText(const QString& value);
  void setBrowserModePresenceValueText(const QString& value);

  void setBrowserModeRigName(const QString& value);
  void setBrowserModeRigAuthor(const QString& value);
  void setBrowserModeAmpName(const QString& value);

  void setBrowserModeView(int view);

protected:
  void createSkin();
  void paintEvent(QPaintEvent* pe);
  void contextMenuEvent(QContextMenuEvent * cme);

  void setEnabled(QWidget& w, bool enabled);

private slots:
  void on_browserViewComboBox_currentIndexChanged(int index);

private:
  QList<QPixmap> mSkinPixmaps;

  Ui::QToasterLCD *ui;
  Mode  mMode;
  Color mColor;

  ICtxMenuProvider* mpCtxMenuProvider;

  class FXType2ShortNameMap : public std::map<FXType, QString>
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

  static FXType2ShortNameMap sFXType2ShortNameMap;
};

#endif // QTOASTERLCD_H
