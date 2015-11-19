#ifndef PHASERFRAME_H
#define PHASERFRAME_H
#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
class PhaserFrame;
}

class PhaserFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit PhaserFrame(QWidget *parent = 0);
  ~PhaserFrame();
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
  void on_rateDial_valueChanged(double value);
  void on_depthDial_valueChanged(double value);
  void on_manualDial_valueChanged(double value);
  void on_feedbackDial_valueChanged(double value);
  void on_peakSpreadDial_valueChanged(double value);
  void on_stagesDial_valueChanged(double value);
  void on_mixDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  // kpa => ui
  void onRate(double value, unsigned short rawVal);
  void onDepth(double value);
  void onManual(double value);
  void onFeedback(double value);
  void onPeakSpread(double value);
  void onStages(double value);
  void onMix(double value);
  void onDucking(double value);
  void onVolume(double value);

private:
  Ui::PhaserFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // PHASERFRAME_H
