#ifndef OUTPUTFRAME_H
#define OUTPUTFRAME_H
#include <QWidget>
#include <QVector>
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
  void on_mainVolumeDial_valueChanged(int value);
  void on_monitorVolumeDial_valueChanged(int value);
  void on_directVolumeDial_valueChanged(int value);
  void on_headphoneVolumeDial_valueChanged(int value);
  void on_monitorOutputEQBassDial_valueChanged(double value);
  void on_monitorOutputEQMiddleDial_valueChanged(double value);
  void on_monitorOutputEQTrebleDial_valueChanged(double value);
  void on_monitorOutputEQPresenceDial_valueChanged(double value);
  void on_monitorCabOffDial_valueChanged(int valueIndex);
  void on_mainOutputEQBassDial_valueChanged(double value);
  void on_mainOutputEQMiddleDial_valueChanged(double value);
  void on_mainOutputEQTrebleDial_valueChanged(double value);
  void on_mainOutputEQPresenceDial_valueChanged(double value);
  void on_spdifVolumeDial_valueChanged(int value);
  void on_pureCabinetDial_valueChanged(double value);
  void on_spaceDial_valueChanged(double value);
  void on_spdifOutLinkDial_valueChanged(int valueIndex);
  void on_pureCabinetOnOffDial_valueChanged(int valueIndex);
  void on_headphoneSpaceDial_valueChanged(int valueIndex);
  void on_auxInMainDial_valueChanged(double value);
  void on_auxInHeadphoneDial_valueChanged(double value);
  void on_constantLatencyDial_valueChanged(int valueIndex);

  // kpa => ui
  void OnMainOutputSource(int valueIndex);
  void OnMonitorOutputSource(int valueIndex);
  void OnDirectOutputSource(int valueIndex);
  void OnSPDIFOutputSource(int valueIndex);
  void OnMainVolume(int value);
  void OnMonitorVolume(int value);
  void OnDirectVolume(int value);
  void OnHeadphoneVolume(int value);
  void OnMonitorOutputEQBass(double value);
  void OnMonitorOutputEQMiddle(double value);
  void OnMonitorOutputEQTreble(double value);
  void OnMonitorOutputEQPresence(double value);
  void OnMonitorCabOff(int valueIndex);
  void OnMainOutputEQBass(double value);
  void OnMainOutputEQMiddle(double value);
  void OnMainOutputEQTreble(double value);
  void OnMainOutputEQPresence(double value);
  void OnSPDIFVolume(int value);
  void OnPureCabinet(double value);
  void OnSpace(double value);
  void OnSPDIFOutLink(int value);
  void OnPureCabinetOnOff(int valueIndex);
  void OnHeadphoneSpace(int valueIndex);
  void OnAuxInMain(double value);
  void OnAuxInHeadphone(double value);
  void OnConstantLatency(int valueIndex);

private:
  Ui::OutputFrame *ui;
  Global* mpGlobal;
  const QVector<QString> mPageTitles = { "Output Source",
                                         "Output Volumes",
                                         "Monitor Output EQ",
                                         "Main Output EQ",
                                         "Output AddOns",
                                         "Aux In" };
};

#endif // OUTPUTFRAME_H
