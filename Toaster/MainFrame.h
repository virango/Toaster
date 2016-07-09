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
#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QFrame>
#include "qtoasterbutton.h"
#include "qchickenheaddial.h"
#include "qmulticolorled.h"
#include "StompCtxMenu.h"
#include "DelayCtxMenu.h"
#include "ReverbCtxMenu.h"

namespace Ui {
class MainFrame;
}

struct IStompEditorPage;

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
  void on_stompAButton_clicked(QToasterButton& bt, bool longClick);
  void on_stompBButton_clicked(QToasterButton& bt, bool longClick);
  void on_stompCButton_clicked(QToasterButton& bt, bool longClick);
  void on_stompDButton_clicked(QToasterButton& bt, bool longClick);
  void on_stompXButton_clicked(QToasterButton& bt, bool longClick);
  void on_stompModButton_clicked(QToasterButton& bt, bool longClick);
  void on_modRateDial_valueChanged(double value);
  void on_modIntensityDial_valueChanged(double value);
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
  void onStompDelayType(::FXType type);
  void onModRate(int value);
  void onModIntensity(double value);

  // reverb
  // ui => kpa
  void on_reverbButton_clicked(QToasterButton &bt, bool longClick);
  void on_reverbTimeDial_valueChanged(double arg1);
  void on_reverbMixDial_valueChanged(int value);
  // kpa => ui
  void onReverbOnOff(bool onOff);
  void onReverbTime(double time);
  void onReverbMix(int mix);

  // delay
  // ui => kpa
  void on_delayButton_clicked(QToasterButton &bt, bool longClick);
  void on_delayFeedbackDial_valueChanged(double arg1);
  void on_delayMixDial_valueChanged(int value);
  // kpa => ui
  void onDelayOnOff(bool onOff);
  void onDelayFeedback(double feedback);
  void onDelayMix(int mix);

  // amp
  // ui => kpa
  void on_amplifierButton_clicked(QToasterButton& bt, bool longClick);
  void on_gainDial_valueChanged(double value);
  // kpa => ui
  void onAmpOnOff(bool onOff);
  void onAmpGain(double val);

  // eq
  // ui => kpa
  void on_eqButton_clicked(QToasterButton& bt, bool longClick);
  // kpa => ui
  void onEqOnOff(bool onOff);

  // cab
  // ui => kpa
  void on_cabinetButton_clicked(QToasterButton& bt, bool longClick);
  // kpa => ui
  void onCabOnOff(bool onOff);

  // rig
  // ui => kpa
  void on_rigVolumeDial_valueChanged(int value);
  void on_stompsButton_clicked(QToasterButton& bt, bool longClick);
  void on_stackButton_clicked(QToasterButton& bt, bool longClick);
  void on_effectsButton_clicked(QToasterButton& bt, bool longClick);
  // kpa => ui
  void onRigVolume(int volume);
  void onRigStompsEnable(bool stompsEnable);
  void onRigStackEnable(bool stackEnable);
  void onRigEffectsEnable(bool effectsEnable);

  // global
  // ui => kpa
  void on_chickenHeadDial_valueChanged(const QChickenHeadDial::State& state);
  // kpa => ui
  void onGlobalOperationMode(unsigned short opMode);
  void onGlobalMainVolume(int volume);
  void onGlobalHeadphoneVolume(int volume);
  void onGlobalMonitorVolume(int volume);
  void onGlobalDirectVolume(double volume);

  // input
  // ui => kpa
  void on_noiseGateDial_valueChanged(double noiseGate);
  void on_distortionSenseDial_valueChanged(double distortionSense);
  void on_cleanSenseDial_valueChanged(double cleanSense);
  // kpa => ui
  void onInputNoiseGate(double noiseGate);
  void onInputDistortionSense(double distortionSense);
  void onInputCleanSense(double cleanSense);

  // profile
  // ui => kpa
  void on_rigPrevButton_clicked(QToasterButton &bt, bool);
  void on_rigNextButton_clicked(QToasterButton &bt, bool);
  // kpa => ui
  // currently none, TODO tempo stuff



  void on_exitButton_clicked(QToasterButton &bt, bool);

  void on_prevPageButton_clicked(QToasterButton &bt, bool longClick);

  void on_nextPageButton_clicked(QToasterButton &bt, bool longClick);

  void onEditorPageChanged(IStompEditorPage* editorPage);

  void on_inputButton_clicked(QToasterButton &bt, bool longClick);

  void on_outputButton_clicked(QToasterButton &bt, bool longClick);

  void on_masterVolumeDBDial_valueChanged(int value);

  void on_masterVolumeDial_valueChanged(double value);

  void on_tapButton_clicked(QToasterButton &bt, bool longClick);

  void onRigNameReveived(const QString& rigName);

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
  void handleStompButtonClick(QObject& module, QToasterButton& stompBt, bool longClick);
  void toggleOperationMode(QObject& module, OperationMode opMode, QToasterButton* bt);
  void setStompLedColor(::FXType type, QMultiColorLed* ledWidget);

private:
  Ui::MainFrame *ui;

  StompCtxMenu  mStompACtxMenu;
  StompCtxMenu  mStompBCtxMenu;
  StompCtxMenu  mStompCCtxMenu;
  StompCtxMenu  mStompDCtxMenu;
  StompCtxMenu  mStompXCtxMenu;
  StompCtxMenu  mStompModCtxMenu;
  StompCtxMenu  mStompDelayCtxMenu;
  DelayCtxMenu  mDelayCtxMenu;
  ReverbCtxMenu mReverbCtxMenu;

  OperationMode mOperationMode;
  OperationMode mPreviousOperationMode;
  QToasterButton* mEditModeButton;
  QObject*      mEditModeModule;

  QString       mCurrRigName;

  // TODO: put this methods in a separate header
  unsigned short phys2Raw(double physVal, double deltaMinMax, double min, unsigned short maxRawVal = 0x3FFF)
  {
    unsigned short rawVal = ((physVal - min) * maxRawVal) / deltaMinMax;
    return rawVal;
  }

  double raw2Phys(unsigned short rawVal, double deltaMinMax, double min)
  {
    double physVal = ((rawVal * deltaMinMax) / 0x3FFF) + min;
    return physVal;
  }
};

#endif // MAINFRAME_H
