#ifndef TONEANDDUCKINGDSFRAME_H
#define TONEANDDUCKINGDSFRAME_H
#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
class ToneAndDuckingDSFrame;
}

class ToneAndDuckingDSFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit ToneAndDuckingDSFrame(QWidget *parent = 0);
  ~ToneAndDuckingDSFrame();
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
  void on_toneDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  // kpa => ui
  void onVolume(double value);
  void onTone(double value);
  void onDucking(double value);

private:
  Ui::ToneAndDuckingDSFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // TONEANDDUCKINGDSFRAME_H
