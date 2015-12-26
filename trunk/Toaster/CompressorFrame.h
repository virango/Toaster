#ifndef COMPRESSORFRAME_H
#define COMPRESSORFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class CompressorFrame;
}

class CompressorFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit CompressorFrame(QWidget *parent = 0);
  ~CompressorFrame();
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
  void on_intensityDial_valueChanged(double value);
  void on_attackDial_valueChanged(double value);
  void on_squashDial_valueChanged(double value);
  void on_mixDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  // kpa => ui
  void onIntensity(double value);
  void onAttack(double value);
  void onSquash(double value);
  void onMix(double value);
  void onVolume(double value);

private:
  Ui::CompressorFrame *ui;
  Stomp* mpStomp;

  FXType mFXType;
};

#endif // COMPRESSORFRAME_H
