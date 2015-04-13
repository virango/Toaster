#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QFrame>
#include "qtoasterbutton.h"
#include "qchickenheaddial.h"
#include "Stomp.h"
#include "Amp.h"
#include "Eq.h"
#include "Cab.h"
#include "Rig.h"
#include "Global.h"

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
  void on_qEQButton_valueChanged(const QToasterButton::State& state);
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

  // cab
  // ui => kpa
  void on_qCabinetButton_valueChanged(const QToasterButton::State& state);
  // kpa => ui
  void onCabOnOff(bool onOff);

  // rig
  // ui => kpa
  void on_qVolumeDial_valueChanged(double volume);
  void on_qStompsButton_valueChanged(const QToasterButton::State& state);
  void on_qStackButton_valueChanged(const QToasterButton::State& state);
  void on_qEffectsButton_valueChanged(const QToasterButton::State& state);
  // kpa => ui
  void onRigVolume(double volume);
  void onRigStompsEnable(bool stompsEnable);
  void onRigStackEnable(bool stackEnable);
  void onRigEffectsEnable(bool effectsEnable);

  // global
  // ui => kpa
  void on_qChickenHeadDial_valueChanged(const QChickenHeadDial::State& arg1);
  // kpa => ui
  void onGlobalOperationMode(unsigned short opMode);

private:
    Ui::MainFrame *ui;

    Stomp         mStompA;
    Stomp         mStompB;
    Stomp         mStompC;
    Stomp         mStompD;
    Stomp         mStompX;
    Stomp         mStompMod;
    Amp           mAmp;
    Eq            mEq;
    Cab           mCab;
    Rig           mRig;
    Global        mGlobal;
};

#endif // MAINFRAME_H
