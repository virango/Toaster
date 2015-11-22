#ifndef PEDALPITCHFRAME_H
#define PEDALPITCHFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Global.h"

namespace Ui {
class PedalPitchFrame;
}


class PedalPitchFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit PedalPitchFrame(QWidget *parent = 0);
  ~PedalPitchFrame();
  // IStompEditorPage
  virtual void activate(Stomp& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpStomp != nullptr; }
  virtual FXType getFXType() const { return mFXType; }
  virtual void setFXType(FXType fxType);

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString&  ampName);
private slots:
  void on_pageDial_valueChanged(int valueIndex);

  // ui => kpa
  void on_heelPitchDial_valueChanged(double value);
  void on_toePitchDial_valueChanged(double value);
  void on_formantShiftDial_valueChanged(double value);
  void on_mixDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_wahPedalToPitchDial_valueChanged(int valueIndex);
  void on_smoothChordsDial_valueChanged(int valueIndex);
  void on_pureTuningDial_valueChanged(int valueIndex);
  void on_formantShiftOnOffDial_valueChanged(int valueIndex);
  // kpa => ui
  void onHeelPitch(double value);
  void onToePitch(double value);
  void onFormantShift(double value);
  void onMix(double value);
  void onVolume(double value);
  void onDucking(double value);
  void onWahPedalToPitch(bool onOff);
  void onSmoothChords(bool onOff);
  void onPureTuning(bool onOff);
  void onFormantShiftOnOff(bool onOff);



private:
  Ui::PedalPitchFrame *ui;

  Stomp* mpStomp;
  Global mGlobal;

  FXType mFXType;
};

#endif // PEDALPITCHFRAME_H
