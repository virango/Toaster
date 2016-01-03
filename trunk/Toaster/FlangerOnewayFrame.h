#ifndef FLANGERONEWAYFRAME_H
#define FLANGERONEWAYFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class FlangerOnewayFrame;
}

class FlangerOnewayFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit FlangerOnewayFrame(QWidget *parent = 0);
  ~FlangerOnewayFrame();
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
  void on_rateDial_valueChanged(double value);
  void on_depthDial_valueChanged(double value);
  void on_manualDial_valueChanged(double value);
  void on_feedbackDial_valueChanged(double value);
  void on_mixDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  // kpa => ui
  void onRate(double value);
  void onDepth(double value);
  void onManual(double value);
  void onFeedback(double value);
  void onMix(double value);
  void onDucking(double value);
  void onVolume(double value);
private:
  Ui::FlangerOnewayFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // FlangerOnewayFrame_H
