#ifndef RECTISHAPERFRAME_H
#define RECTISHAPERFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class RectiShaperFrame;
}

class RectiShaperFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit RectiShaperFrame(QWidget *parent = 0);
  ~RectiShaperFrame();
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
  void on_volumeDial_valueChanged(double value);
  void on_driveDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  // kpa => ui
  void onVolume(double value);
  void onDrive(double value);
  void onDucking(double value);

private:
  Ui::RectiShaperFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // RECTISHAPERFRAME_H
