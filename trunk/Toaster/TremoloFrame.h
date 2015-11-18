#ifndef TREMOLOFRAME_H
#define TREMOLOFRAME_H
#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
class TremoloFrame;
}

class TremoloFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit TremoloFrame(QWidget *parent = 0);
  ~TremoloFrame();
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
  // ui => kpa
  void on_rateDial_valueChanged(double value);
  void on_depthDial_valueChanged(double value);
  void on_crossoverDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  // kpa => ui
  void onRate(double value);
  void onDepth(double value);
  void onCrossover(double value);
  void onVolume(double value);
  void onDucking(double value);
private:
  Ui::TremoloFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // TREMOLOFRAME_H
