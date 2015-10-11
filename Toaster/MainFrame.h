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
#include "Input.h"
#include "Delay.h"
#include "Reverb.h"
#include "Profile.h"
#include "ExtParam.h"
#include "StompCtxMenu.h"

namespace Ui {
class MainFrame;
}

//class QToasterButton;

class MainFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

public slots:
  void connect2KPA(const QString& connectName);
  void disconnectFromKPA();
  void requestValues();

private slots:
  // stomps
  // ui => kpa
  void on_qStompAButton_clicked(QToasterButton& bt, bool longClick);
  void on_qStompBButton_clicked(QToasterButton& bt, bool longClick);
  void on_qStompCButton_clicked(QToasterButton& bt, bool longClick);
  void on_qStompDButton_clicked(QToasterButton& bt, bool longClick);
  void on_qStompXButton_clicked(QToasterButton& bt, bool longClick);
  void on_qStompModButton_clicked(QToasterButton& bt, bool longClick);
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

  // reverb
  // ui => kpa
  void on_qStompReverbButton_clicked(QToasterButton &bt, bool longClick);
  void on_qReverbTimeDial_valueChanged(double arg1);
  void on_qReverbMixDial_valueChanged(double arg1);
  // kpa => ui
  void onStompReverbOnOff(bool onOff);
  void onStompReverbTime(double time);
  void onStompReverbMix(double mix);

  // delay
  // ui => kpa
  void on_qStompDelayButton_clicked(QToasterButton &bt, bool longClick);
  void on_qDelayFeedbackDial_valueChanged(double arg1);
  void on_qDelayMixDial_valueChanged(double arg1);
  // kpa => ui
  void onStompDelayOnOff(bool onOff);
  void onStompDelayFeedback(double feedback);
  void onStompDelayMix(double mix);

  // amp
  // ui => kpa
  void on_qAmplifierButton_clicked(QToasterButton& bt, bool longClick);
  void on_qGainDial_valueChanged(double value);
  // kpa => ui
  void onAmpOnOff(bool onOff);
  void onAmpGain(double val);

  // eq
  // ui => kpa
  void on_qEQButton_clicked(QToasterButton& bt, bool longClick);
  void on_qEqBassDial_valueChanged(double physVal);
  void on_qEqMiddleDial_valueChanged(double physVal);
  void on_qEqTrebleDial_valueChanged(double physVal);
  void on_qEqPresenceDial_valueChanged(double physVal);
  void on_qEqBassDial_valueChanged(const QString& value);
  void on_qEqMiddleDial_valueChanged(const QString& value);
  void on_qEqTrebleDial_valueChanged(const QString& value);
  void on_qEqPresenceDial_valueChanged(const QString& value);
  // kpa => ui
  void onEqOnOff(bool onOff);
  void onEqBass(double bass);
  void onEqMiddle(double middle);
  void onEqTreble(double treble);
  void onEqPresence(double presence);

  // cab
  // ui => kpa
  void on_qCabinetButton_clicked(QToasterButton& bt, bool longClick);
  // kpa => ui
  void onCabOnOff(bool onOff);

  // rig
  // ui => kpa
  void on_qVolumeDial_valueChanged(double volume);
  void on_qStompsButton_clicked(QToasterButton& bt, bool longClick);
  void on_qStackButton_clicked(QToasterButton& bt, bool longClick);
  void on_qEffectsButton_clicked(QToasterButton& bt, bool longClick);
  // kpa => ui
  void onRigVolume(double volume);
  void onRigStompsEnable(bool stompsEnable);
  void onRigStackEnable(bool stackEnable);
  void onRigEffectsEnable(bool effectsEnable);

  // global
  // ui => kpa
  void on_qChickenHeadDial_valueChanged(const QChickenHeadDial::State& state);
  void on_qMonitorVolumeDial_valueChanged(double volume);
  void on_qHeadphoneVolumeDial_valueChanged(double volume);
  // kpa => ui
  void onGlobalOperationMode(unsigned short opMode);
  void onGlobalMainVolume(double volume);
  void onGlobalHeadphoneVolume(double volume);
  void onGlobalMonitorVolume(double volume);
  void onGlobalDirectVolume(double volume);

  // input
  // ui => kpa
  void on_qNoiseGateDial_valueChanged(double noiseGate);
  void on_qDistortionSenseDial_valueChanged(double distortionSense);
  void on_qCleanSenseDial_valueChanged(double cleanSense);
  // kpa => ui
  void onInputNoiseGate(double noiseGate);
  void onInputDistortionSense(double distortionSense);
  void onInputCleanSense(double cleanSense);

  // profile
  // ui => kpa
  // kpa => ui
  void onRigName(const QString& rigName);
  void onRigAuthor(const QString& rigAuthor);
  void onAmpName(const QString& ampName);





  void on_qRigPrevButton_clicked(QToasterButton &bt, bool longClick);

  void on_qRigNextButton_clicked(QToasterButton &bt, bool longClick);

  // extended parameter
  // ui => kpa
  void on_qLCDDisplay_browserModeViewChanged(int view);
  // kpa => ui
  void onBrowserView(unsigned int view);


private:
  enum OperationMode
  {
    Tuner,
    Browser,
    Perform,
    Profiler,
    StompEdit,
    AmpEdit,
    EQEdit,
    CabEdit,
    DelayEdit,
    ReverbEdit
  };

  // utility methods
  void handleStompButtonClick(Stomp& stomp, QToasterButton& stompBt, bool longClick);
  void toggleOperationMode(OperationMode opMode, QToasterButton* bt);

private:
  Ui::MainFrame *ui;

  Stomp         mStompA;
  Stomp         mStompB;
  Stomp         mStompC;
  Stomp         mStompD;
  Stomp         mStompX;
  Stomp         mStompMod;
  Delay         mDelay;
  Reverb        mReverb;
  Amp           mAmp;
  Eq            mEq;
  Cab           mCab;
  Rig           mRig;
  Global        mGlobal;
  Input         mInput;
  Profile       mProfile;
  ExtParam      mExtParam;

  StompCtxMenu  mStompACtxMenu;
  StompCtxMenu  mStompBCtxMenu;
  StompCtxMenu  mStompCCtxMenu;
  StompCtxMenu  mStompDCtxMenu;
  StompCtxMenu  mStompXCtxMenu;
  StompCtxMenu  mStompModCtxMenu;

  OperationMode mOperationMode;
  QToasterButton* mEditModeButton;
};

#endif // MAINFRAME_H
