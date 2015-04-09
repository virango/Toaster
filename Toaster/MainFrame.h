#ifndef RIG_H
#define RIG_H

#include <QFrame>
#include "qtoasterbutton.h"
#include "Stomp.h"
#include "Amp.h"
#include "Eq.h"

namespace Ui {
class MainFrame;
}

class MainFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

public slots:
  void requestValues();

private slots:
  void on_qGainDial_valueChanged(double value);
  void on_qStompAButton_valueChanged(const QToasterButton::State& state);
  void on_qStompBButton_valueChanged(const QToasterButton::State& state);
  void on_qStompCButton_valueChanged(const QToasterButton::State& state);
  void on_qStompDButton_valueChanged(const QToasterButton::State& state);
  void on_qStompXButton_valueChanged(const QToasterButton::State& state);
  void on_qStompModButton_valueChanged(const QToasterButton::State& state);

  void onStompAOnOff(bool onOff);
  void onStompBOnOff(bool onOff);
  void onStompCOnOff(bool onOff);
  void onStompDOnOff(bool onOff);
  void onStompXOnOff(bool onOff);
  void onStompModOnOff(bool onOff);

  void onAmpOnOff(bool onOff);
  void onAmpGain(double val);
  void on_qAmplifierButton_valueChanged(const QToasterButton::State &arg1);

  void onEqOnOff(bool onOff);
  void onEqBass(double bass);
  void onEqMiddle(double middle);
  void onEqTreble(double treble);
  void onEqPresence(double presence);

private:
    Ui::MainFrame *ui;

    Stomp mStompA;
    Stomp mStompB;
    Stomp mStompC;
    Stomp mStompD;
    Stomp mStompX;
    Stomp mStompMod;

    Amp   mAmp;

    Eq    mEq;
};

#endif // RIG_H
