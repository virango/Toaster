#ifndef PHASERONEWAYFRAME_H
#define PHASERONEWAYFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class PhaserOnewayFrame;
}

class PhaserOnewayFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit PhaserOnewayFrame(QWidget *parent = 0);
  ~PhaserOnewayFrame();
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
  void on_rateDial_valueChanged(double value);
  void on_depthDial_valueChanged(double value);
  void on_manualDial_valueChanged(double value);
  void on_feedbackDial_valueChanged(double value);
  void on_peakSpreadDial_valueChanged(double value);
  void on_stagesDial_valueChanged(double value);
  void on_mixDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  void on_stereoDial_valueChanged(double value);
  // kpa => ui
  void onRate(double value);
  void onDepth(double value);
  void onManual(double value);
  void onFeedback(double value);
  void onPeakSpread(double value);
  void onStages(double value);
  void onMix(double value);
  void onDucking(double value);
  void onVolume(double value);
  void onStereo(double value);

private:
  Ui::PhaserOnewayFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // PhaserOnewayFrame_H
