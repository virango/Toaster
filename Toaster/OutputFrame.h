#ifndef OUTPUTFRAME_H
#define OUTPUTFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Global.h"

namespace Ui {
class OutputFrame;
}

class OutputFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit OutputFrame(QWidget *parent = 0);
  ~OutputFrame();
  // IStompEditorPage
  virtual void activate(QObject& module);
  virtual void deactivate();
  virtual bool isActive() { return mpGlobal != nullptr; }
  virtual QObject* getStomp()  { return mpGlobal; }
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
  void on_mainOutputSourceDial_valueChanged(int valueIndex);
  void on_monitorOutputSourceDial_valueChanged(int valueIndex);
  void on_directOutputSourceDial_valueChanged(int valueIndex);
  void on_spdifOutputSourceDial_valueChanged(int valueIndex);

  // kpa => ui
  void OnMainOutputSource(int valueIndex);
  void OnMonitorOutputSource(int valueIndex);
  void OnDirectOutputSource(int valueIndex);
  void OnSpdifOutputSource(int valueIndex);

private:
  Ui::OutputFrame *ui;

  Global* mpGlobal;
};

#endif // OUTPUTFRAME_H
