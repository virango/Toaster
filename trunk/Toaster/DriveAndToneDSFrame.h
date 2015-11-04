#ifndef DRIVEANDTONEDSFRAME_H
#define DRIVEANDTONEDSFRAME_H
#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
class DriveAndToneDSFrame;
}

class DriveAndToneDSFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit DriveAndToneDSFrame(QWidget *parent = 0);
  ~DriveAndToneDSFrame();
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
  void on_driveDial_valueChanged(double value);
  void on_toneDial_valueChanged(double value);
  // kpa => ui
  void onVolume(double value);
  void onDrive(double value);
  void onTone(double value);

private:
  Ui::DriveAndToneDSFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // DRIVEANDTONEDSFRAME_H
