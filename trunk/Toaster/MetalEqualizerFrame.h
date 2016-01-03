#ifndef METALEQUALIZERFRAME_H
#define METALEQUALIZERFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class MetalEqualizerFrame;
}

class MetalEqualizerFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit MetalEqualizerFrame(QWidget *parent = 0);
  ~MetalEqualizerFrame();
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
  void on_lowDial_valueChanged(double value);
  void on_middleDial_valueChanged(double value);
  void on_midFreqDial_valueChanged(int value);
  void on_highDial_valueChanged(double value);
  void on_lowCutDial_valueChanged(int value);
  void on_highCutDial_valueChanged(int value);
  void on_mixDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  // kpa => ui
  void onLowDial(double value);
  void onMiddleDial(double value);
  void onMidFreqDial(int value);
  void onHighDial(double value);
  void onLowCut(int value);
  void onHighCut(int value);
  void onMix(double value);
  void onDucking(double value);
  void onVolume(double value);

private:
  Ui::MetalEqualizerFrame *ui;
  Stomp* mpStomp;

  FXType mFXType;
};

#endif // METALEQUALIZERFRAME_H
