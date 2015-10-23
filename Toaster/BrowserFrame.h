#ifndef BROWSERFRAME_H
#define BROWSERFRAME_H

#include <QFrame>
#include "Eq.h"
#include "Profile.h"
#include "ExtParam.h"
#include "Stomp.h"
#include "Delay.h"
#include "Reverb.h"

namespace Ui {
  class BrowserFrame;
}

class BrowserFrame : public QFrame
{
  Q_OBJECT

public:
  explicit BrowserFrame(QWidget *parent = 0);
  ~BrowserFrame();


private slots:
  // stomps
  // kpa => ui
  void onStompAOnOff(bool onOff);
  void onStompBOnOff(bool onOff);
  void onStompCOnOff(bool onOff);
  void onStompDOnOff(bool onOff);
  void onStompXOnOff(bool onOff);
  void onStompModOnOff(bool onOff);
  void onStompAType(::FXType type);
  void onStompBType(::FXType type);
  void onStompCType(::FXType type);
  void onStompDType(::FXType type);
  void onStompXType(::FXType type);
  void onStompModType(::FXType type);

  // delay
  // kpa => ui
  void onDelayOnOff(bool onOff);

  // reverb
  // kpa => ui
  void onReverbOnOff(bool onOff);

  // eq
  // ui => kpa
  void on_eqBassDial_valueChanged(double value);
  void on_eqBassDial_valueChanged(const QString &value);
  void on_eqMiddleDial_valueChanged(double value);
  void on_eqMiddleDial_valueChanged(const QString &value);
  void on_eqTrebleDial_valueChanged(double value);
  void on_eqTrebleDial_valueChanged(const QString &value);
  void on_eqPresenceDial_valueChanged(double value);
  void on_eqPresenceDial_valueChanged(const QString &value);
  // kpa => ui
  void onEqBass(double bass);
  void onEqMiddle(double middle);
  void onEqTreble(double treble);
  void onEqPresence(double presence);

  // profile
  // ui => kpa
  // kpa => ui
  void onRigName(const QString& rigName);
  void onRigAuthor(const QString& rigAuthor);
  void onAmpName(const QString& ampName);

  // extended parameter
  // ui => kpa
  void on_browseModeDial_valueChanged(int view);
  //void on_lcdDisplay_browserModeViewChanged(int view);
  // kpa => ui
  void onBrowserView(unsigned int view);

private:
  Ui::BrowserFrame *ui;

  Stomp         mStompA;
  Stomp         mStompB;
  Stomp         mStompC;
  Stomp         mStompD;
  Stomp         mStompX;
  Stomp         mStompMod;
  Delay         mDelay;
  Reverb        mReverb;
  Eq            mEq;
  Profile       mProfile;
  ExtParam      mExtParam;
};

#endif // BROWSERFRAME_H
