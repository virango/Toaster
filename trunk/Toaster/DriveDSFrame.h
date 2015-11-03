#ifndef DRIVEDSFRAME_H
#define DRIVEDSFRAME_H
#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
class DriveDSFrame;
}

class DriveDSFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit DriveDSFrame(QWidget *parent = 0);
  ~DriveDSFrame();
  // IStompEditorPage
  virtual void activate(Stomp& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpStomp != nullptr; }
  virtual FXType getFXType() const { return mFXType; }
  virtual void setFXType(FXType fxType) { mFXType = fxType; }

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString&  ampName);

private slots:
  void on_volumeDial_valueChanged(double value);
  void on_driveDial_valueChanged(double value);
  // kpa => ui
  void onVolume(double value);
  void onDrive(double value);


private:
  Ui::DriveDSFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // DRIVEDSFRAME_H
