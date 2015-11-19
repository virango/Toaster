#ifndef VINTAGECHORUSFRAME_H
#define VINTAGECHORUSFRAME_H
#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
class VintageChorusFrame;
}

class VintageChorusFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit VintageChorusFrame(QWidget *parent = 0);
  ~VintageChorusFrame();
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
  void on_mixDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  // kpa => ui
  void onRate(double value, unsigned short);
  void onDepth(double value);
  void onCrossover(double value);
  void onMix(double value);
  void onVolume(double value);
  void onDucking(double value);
private:
  Ui::VintageChorusFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // VINTAGECHORUSFRAME_H
