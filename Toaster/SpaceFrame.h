#ifndef SPACEFRAME_H
#define SPACEFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

namespace Ui {
class SpaceFrame;
}

class SpaceFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit SpaceFrame(QWidget *parent = 0);
  ~SpaceFrame();
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
  // kpa => ui
  void onIntensity(double value);

private:
  Ui::SpaceFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // SPACEFRAME_H
