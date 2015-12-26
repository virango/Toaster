#ifndef VIBRATOFRAME_H
#define VIBRATOFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class VibratoFrame;
}

class VibratoFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit VibratoFrame(QWidget *parent = 0);
  ~VibratoFrame();
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
  void on_crossoverDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  // kpa => ui
  void onRate(double value, unsigned short);
  void onDepth(double value);
  void onCrossover(double value);
  void onVolume(double value);

private:
  Ui::VibratoFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // VIBRATOFRAME_H
