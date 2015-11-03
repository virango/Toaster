#ifndef WahWahFrame_H
#define WahWahFrame_H
#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
  class WahWahFrame;
}

class WahWahFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit WahWahFrame(QWidget *parent = 0);
  ~WahWahFrame();

  // IStompEditorPage
  virtual void activate(Stomp& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpStomp != nullptr; }
  virtual FXType getFXType() const { return mFXType; }
  virtual void setFXType(FXType fxType) { mFXType = fxType; }

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString&  ampName);

private slots:
  void on_pageDial_valueChanged(int valueIndex);

  // ui => kpa
  void on_manualDial_valueChanged(double value);
  void on_peakDial_valueChanged(double value);
  void on_pedalRangeDial_valueChanged(double value);
  void on_peakRangeDial_valueChanged(double value);
  void on_pedalModeDial_valueChanged(int valueIndex);
  void on_mixDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  void on_touchAttackDial_valueChanged(double value);
  void on_touchReleaseDial_valueChanged(double value);
  void on_touchBoostDial_valueChanged(double value);
  // kpa => ui
  void onManual(double value);
  void onPeak(double value);
  void onPedalRange(double value);
  void onPeakRange(double value);
  void onPedalMode(::WahPedalMode value);
  void onMix(double value);
  void onDucking(double value);
  void onVolume(double value);
  void onTouchAttack(double value);
  void onTouchRelease(double value);
  void onTouchBoost(double value);

private:
  Ui::WahWahFrame *ui;

  Stomp* mpStomp;
  FXType mFXType;
};

#endif // WahWahFrame_H
