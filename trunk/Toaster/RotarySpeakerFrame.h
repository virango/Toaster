#ifndef ROTARYSPEAKERFRAME_H
#define ROTARYSPEAKERFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class RotarySpeakerFrame;
}

class RotarySpeakerFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit RotarySpeakerFrame(QWidget *parent = 0);
  ~RotarySpeakerFrame();
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
  // ui => kpa
  void on_distanceDial_valueChanged(int value);
  void on_lowHighBalanceDial_valueChanged(double value);
  void on_rotarySpeedDial_valueChanged(int speed);
  void on_volumeDial_valueChanged(double value);
  void on_mixDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  // kpa => ui
  void onDistance(int value);
  void onLowHighBalance(double value);
  void onRotarySpeed(::RotarySpeed value);
  void onVolume(double value);
  void onMix(double value);
  void onDucking(double value);
private:
  Ui::RotarySpeakerFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // ROTARYSPEAKERFRAME_H