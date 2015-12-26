#ifndef TRANSPOSEFRAME_H
#define TRANSPOSEFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class TransposeFrame;
}

class TransposeFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit TransposeFrame(QWidget *parent = 0);
  ~TransposeFrame();
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
  void on_pitchDial_valueChanged(double value);
  void on_smoothChordsDial_valueChanged(int valueIndex);
  // kpa => ui
  void onPitch(double value);
  void onSmoothChords(bool onOff);

private:
  Ui::TransposeFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // TRANSPOSEFRAME_H
