#ifndef PEDALVINYLSTOPFRAME_H
#define PEDALVINYLSTOPFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"
#include "Global.h"

namespace Ui {
class PedalVinylStopFrame;
}

class PedalVinylStopFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit PedalVinylStopFrame(QWidget *parent = 0);
  ~PedalVinylStopFrame();

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
  void on_volumeDial_valueChanged(double value);
  void on_mixDial_valueChanged(double value);
  void on_wahPedalToPitchDial_valueChanged(int valueIndex);
  // kpa => ui
  void onVolume(double value);
  void onMix(double value);
  void onWahPedalToPitch(bool onOff);

private:
  Ui::PedalVinylStopFrame *ui;

  Stomp* mpStomp;
  Global mGlobal;

  FXType mFXType;
};

#endif // PEDALVINYLSTOPFRAME_H
