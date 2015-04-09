#include "MainFrame.h"
#include "ui_MainFrame.h"

MainFrame::MainFrame(QWidget *parent)
  : QFrame(parent)
  , ui(new Ui::MainFrame)
  , mStompA(StompMidi::A)
  , mStompB(StompMidi::B)
  , mStompC(StompMidi::C)
  , mStompD(StompMidi::D)
  , mStompX(StompMidi::X)
  , mStompMod(StompMidi::MOD)
{
    ui->setupUi(this);

    // notifications
    // stomps
    connect(&mStompA, SIGNAL(onOffReceived(bool)), this, SLOT(onStompAOnOff(bool)));
    connect(&mStompB, SIGNAL(onOffReceived(bool)), this, SLOT(onStompBOnOff(bool)));
    connect(&mStompC, SIGNAL(onOffReceived(bool)), this, SLOT(onStompCOnOff(bool)));
    connect(&mStompD, SIGNAL(onOffReceived(bool)), this, SLOT(onStompDOnOff(bool)));
    connect(&mStompX, SIGNAL(onOffReceived(bool)), this, SLOT(onStompXOnOff(bool)));
    connect(&mStompMod, SIGNAL(onOffReceived(bool)), this, SLOT(onStompModOnOff(bool)));
    // amp
    connect(&mAmp, SIGNAL(onOffReceived(bool)), this, SLOT(onAmpOnOff(bool)));
    connect(&mAmp, SIGNAL(gainReceived(double)), this, SLOT(onAmpGain(double)));
    //eq
    connect(&mEq, SIGNAL(onOffReceived(bool)), this, SLOT(onEqOnOff(bool)));
    connect(&mEq, SIGNAL(bassReceived(double)), this, SLOT(onEqBass(double)));
    connect(&mEq, SIGNAL(middleReceived(double)), this, SLOT(onEqMiddle(double)));
    connect(&mEq, SIGNAL(trebleReceived(double)), this, SLOT(onEqTreble(double)));
    connect(&mEq, SIGNAL(presenceReceived(double)), this, SLOT(onEqPresence(double)));
}

MainFrame::~MainFrame()
{
    delete ui;
}

void MainFrame::requestValues()
{
  mStompA.requestAllValues();
  mStompB.requestAllValues();
  mStompC.requestAllValues();
  mStompD.requestAllValues();
  mStompX.requestAllValues();
  mStompMod.requestAllValues();
  mAmp.requestAllValues();
  mEq.requestAllValues();
}

void MainFrame::on_qGainDial_valueChanged(double gain)
{
  mAmp.applyGain(gain);
}


void MainFrame::on_qAmplifierButton_valueChanged(const QToasterButton::State& state)
{
  if(state == QToasterButton::On)
    mAmp.applyOnOff(true);
  else if(state == QToasterButton::Off)
    mAmp.applyOnOff(false);
  // else ==> edit TODO
}

void MainFrame::on_qStompAButton_valueChanged(const QToasterButton::State& state)
{
  if(state == QToasterButton::On)
    mStompA.applyOnOff(true);
  else if(state == QToasterButton::Off)
    mStompA.applyOnOff(false);
  // else ==> edit TODO
}

void MainFrame::on_qStompBButton_valueChanged(const QToasterButton::State& state)
{
  if(state == QToasterButton::On)
    mStompB.applyOnOff(true);
  else if(state == QToasterButton::Off)
    mStompB.applyOnOff(false);
  // else ==> edit TODO
}

void MainFrame::on_qStompCButton_valueChanged(const QToasterButton::State& state)
{
  if(state == QToasterButton::On)
    mStompC.applyOnOff(true);
  else if(state == QToasterButton::Off)
    mStompC.applyOnOff(false);
  // else ==> edit TODO
}

void MainFrame::on_qStompDButton_valueChanged(const QToasterButton::State& state)
{
  if(state == QToasterButton::On)
    mStompD.applyOnOff(true);
  else if(state == QToasterButton::Off)
    mStompD.applyOnOff(false);
  // else ==> edit TODO
}

void MainFrame::on_qStompXButton_valueChanged(const QToasterButton::State& state)
{
  if(state == QToasterButton::On)
    mStompX.applyOnOff(true);
  else if(state == QToasterButton::Off)
    mStompX.applyOnOff(false);
  // else ==> edit TODO
}

void MainFrame::on_qStompModButton_valueChanged(const QToasterButton::State& state)
{
  if(state == QToasterButton::On)
    mStompMod.applyOnOff(true);
  else if(state == QToasterButton::Off)
    mStompMod.applyOnOff(false);
  // else ==> edit TODO
}

void MainFrame::onStompAOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qStompAButton->setState(state);
  update();
}

void MainFrame::onStompBOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qStompBButton->setState(state);
  update();
}

void MainFrame::onStompCOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qStompCButton->setState(state);
  update();
}

void MainFrame::onStompDOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qStompDButton->setState(state);
  update();
}

void MainFrame::onStompXOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qStompXButton->setState(state);
  update();
}

void MainFrame::onStompModOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qStompModButton->setState(state);
  update();
}

void MainFrame::onAmpOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qAmplifierButton->setState(state);
  update();
}

void MainFrame::onAmpGain(double val)
{
  ui->qGainDial->setValue(val);
  update();
}

void MainFrame::onEqOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->qEQButton->setState(state);
  update();
}

void MainFrame::onEqBass(double bass)
{
  ui->qBigMulti1Dial->setValue(bass);
  update();
}

void MainFrame::onEqMiddle(double middle)
{
  ui->qBigMulti2Dial->setValue(middle);
  update();
}

void MainFrame::onEqTreble(double treble)
{
  ui->qBigMulti3Dial->setValue(treble);
  update();
}

void MainFrame::onEqPresence(double presence)
{
  ui->qBigMulti4Dial->setValue(presence);
  update();
}
