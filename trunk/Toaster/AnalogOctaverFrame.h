#ifndef ANALOGOCTAVERFRAME_H
#define ANALOGOCTAVERFRAME_H
#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
class AnalogOctaverFrame;
}

class AnalogOctaverFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit AnalogOctaverFrame(QWidget *parent = 0);
  ~AnalogOctaverFrame();
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
  void on_duckingDial_valueChanged(double value);
  void on_voiceMixDial_valueChanged(double value);
  void on_mixDial_valueChanged(double value);
  void on_lowCutDial_valueChanged(double value);
  // kpa => ui
  void onVolume(double value);
  void onDucking(double value);
  void onVoiceMix(double value);
  void onMix(double value);
  void onLowCut(double value);
private:
  Ui::AnalogOctaverFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // ANALOGOCTAVERFRAME_H
