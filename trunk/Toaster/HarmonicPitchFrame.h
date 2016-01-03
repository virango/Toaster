#ifndef HARMONICPITCHFRAME_H
#define HARMONICPITCHFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class HarmonicPitchFrame;
}

class HarmonicPitchFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit HarmonicPitchFrame(QWidget *parent = 0);
  ~HarmonicPitchFrame();
  // IStompEditorPage
  virtual void activate(QObject& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpStomp != nullptr; }
  virtual QObject* getStomp()  { return mpStomp; }

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString&  ampName);
private slots:
  void on_pageDial_valueChanged(int valueIndex);

  // ui => kpa
  void on_voice1IntervalDial_valueChanged(int value);
  void on_voice2IntervalDial_valueChanged(int value);
  void on_formantShiftDial_valueChanged(double value);
  void on_keyDial_valueChanged(int valueIndex);
  void on_voiceMixDial_valueChanged(double value);
  void on_mixDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  void on_pureTuningDial_valueChanged(int valueIndex);
  void on_formantShiftOnOffDial_valueChanged(int valueIndex);
  // kpa => ui
  void onVoice1Interval(int value);
  void onVoice2Interval(int value);
  void onFormantShift(double value);
  void onKey(int value);
  void onVoiceMix(double value);
  void onMix(double value);
  void onDucking(double value);
  void onVolume(double value);
  void onPureTuning(bool onOff);
  void onFormantShiftOnOff(bool onOff);

private:
  Ui::HarmonicPitchFrame *ui;

  Stomp* mpStomp;
};

#endif // HARMONICPITCHFRAME_H
