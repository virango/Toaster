#ifndef GATEFRAME_H
#define GATEFRAME_H
#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
class GateFrame;
}

class GateFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit GateFrame(QWidget *parent = 0);
  ~GateFrame();
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
  void on_thresholdDial_valueChanged(double value);
  // kpa => ui
  void onThreshold(double value);

private:
  Ui::GateFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // GATEFRAME_H
