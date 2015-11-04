#ifndef WAHPEDALBOOSTERFRAME_H
#define WAHPEDALBOOSTERFRAME_H
#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
class WahPedalBoosterFrame;
}

class WahPedalBoosterFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit WahPedalBoosterFrame(QWidget *parent = 0);
  ~WahPedalBoosterFrame();
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
  void on_pedalRangeDial_valueChanged(double value);
  // kpa => ui
  void onVolume(double value);
  void onPedalRange(double value);

private:
  Ui::WahPedalBoosterFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // WAHPEDALBOOSTERFRAME_H
