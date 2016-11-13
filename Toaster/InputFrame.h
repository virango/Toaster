#ifndef INPUTFRAME_H
#define INPUTFRAME_H

#include <QWidget>
#include "StompEditorPage.h"
#include "Input.h"

namespace Ui {
class InputFrame;
}

class InputFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit InputFrame(QWidget *parent = 0);
  ~InputFrame();
  // IStompEditorPage
  virtual void activate(QObject& module);
  virtual void deactivate();
  virtual bool isActive() { return mpInput != nullptr; }
  virtual QObject* getStomp()  { return mpInput; }
  virtual QToasterLCD::Page getMaxDisplayPage();
  virtual QToasterLCD::Page getCurrentDisplayPage();
  virtual void setCurrentDisplayPage(QToasterLCD::Page page);

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString&  ampName);
private slots:
  // ui => kpa
  void on_cleanSensDial_valueChanged(double value);
  void on_distortionSensDial_valueChanged(double value);
  void on_inputSourceDial_valueChanged(int valueIndex);
  void on_reampSensDial_valueChanged(double value);
  // kpa => ui
  void OnCleanSens(double value);
  void OnDistortionSens(double value);
  void OnInputSource(int valueIndex);
  void OnReampSens(double value);

private:
  Ui::InputFrame *ui;
  Input* mpInput;
  QToasterLCD::Page mCurrentPage = QToasterLCD::Page1;
};

#endif // INPUTFRAME_H
