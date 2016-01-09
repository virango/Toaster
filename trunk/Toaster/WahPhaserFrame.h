#ifndef WAHPHASERFRAME_H
#define WAHPHASERFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class WahPhaserFrame;
}

class WahPhaserFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit WahPhaserFrame(QWidget *parent = 0);
  ~WahPhaserFrame();

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
  void on_spreadDial_valueChanged(double value);
  void on_stagesDial_valueChanged(double value);
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
  void onSpread(double value);
  void onStages(double value);

private:
  Ui::WahPhaserFrame *ui;
  Stomp* mpStomp;
  FXType mFXType;
};

#endif // WAHPHASERFRAME_H