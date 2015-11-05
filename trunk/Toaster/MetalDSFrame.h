#ifndef METALDSFRAME_H
#define METALDSFRAME_H
#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
class MetalDSFrame;
}

class MetalDSFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit MetalDSFrame(QWidget *parent = 0);
  ~MetalDSFrame();
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
  void on_volumeDial_valueChanged(double value);
  void on_driveDial_valueChanged(double value);
  void on_lowDial_valueChanged(double value);
  void on_middleDial_valueChanged(double value);
  void on_midFreqDial_valueChanged(double value);
  void on_highDial_valueChanged(double value);
  // kpa => ui
  void onVolume(double value);
  void onDrive(double value);
  void onLowDial(double value);
  void onMiddleDial(double value);
  void onMidFreqDial(double value);
  void onHighDial(double value);

private:
  Ui::MetalDSFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // METALDSFRAME_H
