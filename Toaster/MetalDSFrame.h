#ifndef METALDSFRAME_H
#define METALDSFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

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
  void on_volumeDial_valueChanged(double value);
  void on_driveDial_valueChanged(double value);
  void on_lowDial_valueChanged(double value);
  void on_middleDial_valueChanged(double value);
  void on_midFreqDial_valueChanged(double value);
  void on_highDial_valueChanged(double value);
  // kpa => ui
  void onVolume(double value);
  void onDrive(double value);
  void onLow(double value);
  void onMiddle(double value);
  void onMidFreq(double value);
  void onHigh(double value);

private:
  Ui::MetalDSFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // METALDSFRAME_H
