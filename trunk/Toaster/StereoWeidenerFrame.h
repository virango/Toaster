#ifndef STEREOWEIDENERFRAME_H
#define STEREOWEIDENERFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class StereoWeidenerFrame;
}

class StereoWeidenerFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit StereoWeidenerFrame(QWidget *parent = 0);
  ~StereoWeidenerFrame();
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
  void on_intensityDial_valueChanged(double value);
  void on_tuneDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  // kpa => ui
  void onIntensity(double value);
  void onTune(double value, unsigned short);
  void onDucking(double value);

private:
  Ui::StereoWeidenerFrame *ui;
  Stomp* mpStomp;

  FXType mFXType;
};

#endif // STEREOWEIDENERFRAME_H
