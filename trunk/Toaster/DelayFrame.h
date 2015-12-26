#ifndef DELAYFRAME_H
#define DELAYFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Delay.h"

namespace Ui {
class DelayFrame;
}

class Delay;

class DelayFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit DelayFrame(QWidget *parent = 0);
  ~DelayFrame();

  // IStompEditorPage
  virtual void activate(QObject& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpDelay != nullptr; }
  virtual QObject* getStomp()  { return mpDelay; }

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString&  ampName);

private slots:
  // ui => kpa
  void on_bandwidthDial_valueChanged(double value);
  void on_centerFrequencyDial_valueChanged(double value);
  void on_modulationDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_timeDial_valueChanged(double value);
  void on_ratioDial_valueChanged(int valueIndex);
  void on_volumeDial_valueChanged(double value);
  // kpa => ui
  void onBandwidth(double value);
  void onCenterFrequency(double value);
  void onModulation(double value);
  void onDucking(double value);
  void onTime(double value);
  void onRatio(::DelayRatio ratio);
  void onVolume(double value);

private:
  Ui::DelayFrame *ui;

  Delay* mpDelay;
};

#endif // DELAYFRAME_H
