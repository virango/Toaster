#ifndef AMPFRAME_H
#define AMPFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Amp.h"

namespace Ui {
class AmpFrame;
}

class AmpFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit AmpFrame(QWidget *parent = 0);
  ~AmpFrame();

  // IStompEditorPage
  virtual void activate(QObject& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpAmp != nullptr; }
  virtual QObject* getStomp()  { return mpAmp; }

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString&  ampName);

private slots:
  void on_definitionDial_valueChanged(double value);
  void on_powerSaggingDial_valueChanged(double value);
  void on_pickDial_valueChanged(double value);
  void on_compressorDial_valueChanged(double value);
  void on_clarityDial_valueChanged(double value);
  void on_tubeShapeDial_valueChanged(double value);
  void on_tubeBiasDial_valueChanged(double value);
  void on_directMixDial_valueChanged(double value);

  void onDefinition(double value);
  void onPowerSagging(double value);
  void onPick(double value);
  void onCompressor(double value);
  void onClarity(double value);
  void onTubeShape(double value);
  void onTubeBias(double value);
  void onDirectMix(double value);

private:
  Ui::AmpFrame *ui;

  Amp* mpAmp;
};

#endif // AMPFRAME_H
