#ifndef CABFRAME_H
#define CABFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Cab.h"

namespace Ui {
class CabFrame;
}

class CabFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit CabFrame(QWidget *parent = 0);
  ~CabFrame();

  // IStompEditorPage
  virtual void activate(QObject& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpCab != nullptr; }
  virtual QObject* getStomp()  { return mpCab; }

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString&  ampName);

private slots:
  void on_highShiftDial_valueChanged(double value);
  void on_lowShiftDial_valueChanged(double value);
  void on_characterDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  void onHighShift(double value);
  void onLowShift(double value);
  void onCharacter(double value);
  void onVolume(double value);

private:
  Ui::CabFrame *ui;

  Cab* mpCab;
};

#endif // CABFRAME_H
