#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QFrame>
#include "qtoasterbutton.h"
#include "Stomp.h"
#include "Amp.h"
#include "Eq.h"
#include "Rig.h"

namespace Ui {
class MainFrame;
}

class MainFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

public slots:
  void requestValues();

private slots:
  // stomps
  // ui => kpa
  void on_qStompAButton_valueChanged(const QToasterButton::State& state);
  void on_qStompBButton_valueChanged(const QToasterButton::State& state);
  void on_qStompCButton_valueChanged(const QToasterButton::State& state);
  void on_qStompDButton_valueChanged(const QToasterButton::State& state);
  void on_qStompXButton_valueChanged(const QToasterButton::State& state);
  void on_qStompModButton_valueChanged(const QToasterButton::State& state);
  // kpa => ui
  void onStompAOnOff(bool onOff);
  void onStompBOnOff(bool onOff);
  void onStompCOnOff(bool onOff);
  void onStompDOnOff(bool onOff);
  void onStompXOnOff(bool onOff);
  void onStompModOnOff(bool onOff);

  // amp
  // ui => kpa
  void on_qAmplifierButton_valueChanged(const QToasterButton::State &arg1);
  void on_qGainDial_valueChanged(double value);
  // kpa => ui
  void onAmpOnOff(bool onOff);
  void onAmpGain(double val);

  // eq
  // ui => kpa
  void on_qBigMulti1Dial_valueChanged(double physVal);
  void on_qBigMulti2Dial_valueChanged(double physVal);
  void on_qBigMulti3Dial_valueChanged(double physVal);
  void on_qBigMulti4Dial_valueChanged(double physVal);
  // kpa => ui
  void onEqOnOff(bool onOff);
  void onEqBass(double bass);
  void onEqMiddle(double middle);
  void onEqTreble(double treble);
  void onEqPresence(double presence);

  // rig
  // ui => kpa
  void on_qVolumeDial_valueChanged(double volume);
  // kpa => ui
  void onRigVolume(double volume);

private:
    Ui::MainFrame *ui;

    Stomp mStompA;
    Stomp mStompB;
    Stomp mStompC;
    Stomp mStompD;
    Stomp mStompX;
    Stomp mStompMod;
    Amp   mAmp;
    Eq    mEq;
    Rig   mRig;
};

#endif // MAINFRAME_H
