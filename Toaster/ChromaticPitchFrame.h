#ifndef CHROMATICPITCHFRAME_H
#define CHROMATICPITCHFRAME_H
#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
class ChromaticPitchFrame;
}

class ChromaticPitchFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit ChromaticPitchFrame(QWidget *parent = 0);
  ~ChromaticPitchFrame();
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
  void on_voice1PitchDial_valueChanged(double value);
  void on_voice2PitchDial_valueChanged(double value);
  void on_formantShiftDial_valueChanged(double value);
  void on_detuneDial_valueChanged(double value);
  void on_voiceMixDial_valueChanged(double value);
  void on_mixDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  void on_smoothChordsDial_valueChanged(int valueIndex);
  void on_pureTuningDial_valueChanged(int valueIndex);
  void on_formantShiftOnOffDial_valueChanged(int valueIndex);
  // kpa => ui
  void onVoice1Pitch(double value);
  void onVoice2Pitch(double value);
  void onFormantShift(double value);
  void onDetune(double value);
  void onVoiceMix(double value);
  void onMix(double value);
  void onDucking(double value);
  void onVolume(double value);
  void onSmoothChords(bool onOff);
  void onPureTuning(bool onOff);
  void onFormantShiftOnOff(bool onOff);

private:
  Ui::ChromaticPitchFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // CHROMATICPITCHFRAME_H
