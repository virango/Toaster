#ifndef PUREBOOSTERFRAME_H
#define PUREBOOSTERFRAME_H
#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
class PureBoosterFrame;
}

class PureBoosterFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit PureBoosterFrame(QWidget *parent = 0);
  ~PureBoosterFrame();

  // IStompEditorPage
  virtual void activate(Stomp& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpStomp != nullptr; }
  virtual FXType getFXType() const { return PureBooster; }
  virtual void setFXType(FXType fxType) { mFXType = fxType; }

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
  Ui::PureBoosterFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // PUREBOOSTERFRAME_H
