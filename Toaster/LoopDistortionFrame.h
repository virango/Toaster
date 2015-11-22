#ifndef LOOPDISTORTIONFRAME_H
#define LOOPDISTORTIONFRAME_H
#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
class LoopDistortionFrame;
}

class LoopDistortionFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit LoopDistortionFrame(QWidget *parent = 0);
  ~LoopDistortionFrame();

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
  void on_volumeDial_valueChanged(double value);
  // kpa => ui
  void onVolume(double value);

private:
  Ui::LoopDistortionFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // LOOPDISTORTIONFRAME_H
