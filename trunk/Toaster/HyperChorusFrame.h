#ifndef HYPERCHORUSFRAME_H
#define HYPERCHORUSFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class HyperChorusFrame;
}

class HyperChorusFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit HyperChorusFrame(QWidget *parent = 0);
  ~HyperChorusFrame();
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
  void on_depthDial_valueChanged(double value);
  void on_amountDial_valueChanged(double value);
  void on_crossoverDial_valueChanged(int value);
  void on_mixDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  // kpa => ui
  void onDepth(double value);
  void onAmount(double value);
  void onCrossover(int value);
  void onMix(double value);
  void onVolume(double value);
  void onDucking(double value);
private:
  Ui::HyperChorusFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // HYPERCHORUSFRAME_H
