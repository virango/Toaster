#ifndef REVERBFRAME_H
#define REVERBFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Reverb.h"

namespace Ui {
class ReverbFrame;
}

class Reverb;
class ReverbFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit ReverbFrame(QWidget *parent = 0);
  ~ReverbFrame();

  // IStompEditorPage
  virtual void activate(QObject& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpReverb != nullptr; }
  virtual QObject* getStomp()  { return mpReverb; }

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString&  ampName);

private slots:
  // ui => kpa
  void on_predelayDial_valueChanged(double value);
  void on_bandwidthDial_valueChanged(double value);
  void on_frequencyDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_delRevBalanceDial_valueChanged(double value);
  void on_dampingDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  // kpa => ui
  void onPredaly(double value);
  void onBandwidth(double value);
  void onFrequency(double value);
  void onDucking(double value);
  void onDelRevBalance(double value);
  void onDamping(double value);
  void onVolume(double value);
private:
  Ui::ReverbFrame *ui;
  Reverb* mpReverb;
};

#endif // REVERBFRAME_H
