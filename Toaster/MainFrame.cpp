#include "MainFrame.h"
#include "ui_MainFrame.h"
#include "DebugMidi.h"

MainFrame::MainFrame(QWidget *parent)
  : QFrame(parent)
  , ui(new Ui::MainFrame)
  , mStompA(StompA)
  , mStompB(StompB)
  , mStompC(StompC)
  , mStompD(StompD)
  , mStompX(StompX)
  , mStompMod(StompMOD)
  , mStompACtxMenu(mStompA)
  , mStompBCtxMenu(mStompB)
  , mStompCCtxMenu(mStompC)
  , mStompDCtxMenu(mStompD)
  , mStompXCtxMenu(mStompX)
  , mStompModCtxMenu(mStompMod)
  , mOperationMode(Browser)
  , mPreviousOperationMode(Browser)
  , mEditModeButton(NULL)
{
  ui->setupUi(this);

  // notifications
  // stomps
  //qRegisterMetaType<::FXType>("::FXType");
  connect(&mStompA, SIGNAL(onOffReceived(bool)), this, SLOT(onStompAOnOff(bool)));
  connect(&mStompB, SIGNAL(onOffReceived(bool)), this, SLOT(onStompBOnOff(bool)));
  connect(&mStompC, SIGNAL(onOffReceived(bool)), this, SLOT(onStompCOnOff(bool)));
  connect(&mStompD, SIGNAL(onOffReceived(bool)), this, SLOT(onStompDOnOff(bool)));
  connect(&mStompX, SIGNAL(onOffReceived(bool)), this, SLOT(onStompXOnOff(bool)));
  connect(&mStompMod, SIGNAL(onOffReceived(bool)), this, SLOT(onStompModOnOff(bool)));
  connect(&mStompA, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompAType(::FXType)));
  connect(&mStompB, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompBType(::FXType)));
  connect(&mStompC, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompCType(::FXType)));
  connect(&mStompD, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompDType(::FXType)));
  connect(&mStompX, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompXType(::FXType)));
  connect(&mStompMod, SIGNAL(typeReceived(::FXType)), this, SLOT(onStompModType(::FXType)));
  // delay
  connect(&mDelay, SIGNAL(onOffCutsTailReceived(bool)), this, SLOT(onDelayOnOff(bool)));
  connect(&mDelay, SIGNAL(feedbackReceived(double)), this, SLOT(onDelayFeedback(double)));
  connect(&mDelay, SIGNAL(mixReceived(double)), this, SLOT(onDelayMix(double)));
  // reverb
  connect(&mReverb, SIGNAL(onOffCutsTailReceived(bool)), this, SLOT(onReverbOnOff(bool)));
  connect(&mReverb, SIGNAL(timeReceived(double)), this, SLOT(onReverbTime(double)));
  connect(&mReverb, SIGNAL(mixReceived(double)), this, SLOT(onReverbMix(double)));
  // amp
  connect(&mAmp, SIGNAL(onOffReceived(bool)), this, SLOT(onAmpOnOff(bool)));
  connect(&mAmp, SIGNAL(gainReceived(double)), this, SLOT(onAmpGain(double)));
  // eq
  connect(&mEq, SIGNAL(onOffReceived(bool)), this, SLOT(onEqOnOff(bool)));
  // cab
  connect(&mCab, SIGNAL(onOffReceived(bool)), this, SLOT(onCabOnOff(bool)));
  // rig
  //connect(&mRig, SIGNAL(tempoReceived(double)), this, SLOT(onRigTempo(double)));
  connect(&mRig, SIGNAL(volumeReceived(double)), this, SLOT(onRigVolume(double)));
  //connect(&mRig, SIGNAL(tempoEnableReceived(bool)), this, SLOT(onRigTempoEnable(bool)));
  connect(&mRig, SIGNAL(stompsEnableReceived(bool)), this, SLOT(onRigStompsEnable(bool)));
  connect(&mRig, SIGNAL(stackEnableReceived(bool)), this, SLOT(onRigStackEnable(bool)));
  connect(&mRig, SIGNAL(effectsEnableReceived(bool)), this, SLOT(onRigEffectsEnable(bool)));
  // global
  connect(&mGlobal, SIGNAL(operationModeReceived(unsigned short)), this, SLOT(onGlobalOperationMode(unsigned short)));
  connect(&mGlobal, SIGNAL(mainOutputVolumeReceived(double)), this, SLOT(onGlobalMainVolume(double)));
  connect(&mGlobal, SIGNAL(headphoneOutputVolumeReceived(double)), this, SLOT(onGlobalHeadphoneVolume(double)));
  connect(&mGlobal, SIGNAL(monitorOutputVolumeReceived(double)), this, SLOT(onGlobalMonitorVolume(double)));
  connect(&mGlobal, SIGNAL(directOutputVolumeReceived(double)), this, SLOT(onGlobalDirectVolume(double)));
  // input
  connect(&mInput, SIGNAL(noiseGateReceived(double)), this, SLOT(onInputNoiseGate(double)));
  connect(&mInput, SIGNAL(distortionSenseReceived(double)), SLOT(onInputDistortionSense(double)));
  connect(&mInput, SIGNAL(cleanSenseReceived(double)), SLOT(onInputCleanSense(double)));

  ui->stompAButton->setCtxMenuProvider(&mStompACtxMenu);
  ui->stompBButton->setCtxMenuProvider(&mStompBCtxMenu);
  ui->stompCButton->setCtxMenuProvider(&mStompCCtxMenu);
  ui->stompDButton->setCtxMenuProvider(&mStompDCtxMenu);
  ui->stompXButton->setCtxMenuProvider(&mStompXCtxMenu);
  ui->stompModButton->setCtxMenuProvider(&mStompModCtxMenu);
}

MainFrame::~MainFrame()
{
    delete ui;
}
//------------------------------------------------------------------------------------------

// global communication
void MainFrame::connect2KPA(const QString& connectName)
{
  mGlobal.connect2KPA(connectName);
}

void MainFrame::disconnectFromKPA()
{
  mGlobal.disconnectFromKPA();
}

void MainFrame::requestValues()
{
  mStompA.requestAllValues();
  mStompB.requestAllValues();
  mStompC.requestAllValues();
  mStompD.requestAllValues();
  mStompX.requestAllValues();
  mStompMod.requestAllValues();
  mDelay.requestAllValues();
  mReverb.requestAllValues();
  mAmp.requestAllValues();
  mEq.requestAllValues();
  mCab.requestAllValues();
  mRig.requestAllValues();
  mGlobal.requestAllValues();
  mInput.requestAllValues();
  mProfile.requestAllValues();

  //DebugMidi::get().debugScanRequest(0x04, 0x00, 0x7F);
  //DebugMidi::get().debugScanRequest(0x00, 0x0, 0x7F);
  //DebugMidi::get().debugScanRequest(0x01, 0x00, 0x7F);
}

// stomps
// ui => kpa
void MainFrame::on_stompAButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(mStompA, bt, longClick);
}

void MainFrame::on_stompBButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(mStompB, bt, longClick);
}

void MainFrame::on_stompCButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(mStompC, bt, longClick);
}

void MainFrame::on_stompDButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(mStompD, bt, longClick);
}

void MainFrame::on_stompXButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(mStompX, bt, longClick);
}

void MainFrame::on_stompModButton_clicked(QToasterButton& bt, bool longClick)
{
  handleStompButtonClick(mStompMod, bt, longClick);
}

// kpa => ui
void MainFrame::onStompAOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->stompAButton->setState(state);
    update();
  }
}

void MainFrame::onStompBOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->stompBButton->setState(state);
    update();
  }
}

void MainFrame::onStompCOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->stompCButton->setState(state);
    update();
  }
}

void MainFrame::onStompDOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->stompDButton->setState(state);
    update();
  }
}

void MainFrame::onStompXOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->stompXButton->setState(state);
    update();
  }
}

void MainFrame::onStompModOnOff(bool onOff)
{
  if(mOperationMode != StompEdit)
  {
    QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
    ui->stompModButton->setState(state);
    update();
  }
}

void MainFrame::onStompAType(::FXType type)
{
  // TODO: set the LED color
}

void MainFrame::onStompBType(::FXType type)
{
  // TODO: set the LED color
}

void MainFrame::onStompCType(::FXType type)
{
  // TODO: set the LED color
}

void MainFrame::onStompDType(::FXType type)
{
  // TODO: set the LED color
}

void MainFrame::onStompXType(::FXType type)
{
  // TODO: set the LED color
}

void MainFrame::onStompModType(::FXType type)
{
  // TODO: set the LED color
}
//------------------------------------------------------------------------------------------

// reverb
// ui => kpa
void MainFrame::on_reverbButton_clicked(QToasterButton& bt, bool longClick)
{
  if(longClick)
  {
    //toggleOperationMode(StompEdit, &bt);
  }
  else
  {
    mReverb.applyOnOffCutsTail(bt.toggleOnOff());
  }
  update();
}

void MainFrame::on_reverbTimeDial_valueChanged(double arg1)
{
  mReverb.applyTime(arg1);
}

void MainFrame::on_reverbMixDial_valueChanged(double arg1)
{
  mReverb.applyMix(arg1);
}

// kpa => ui
void MainFrame::onReverbOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->reverbButton->setState(state);
  update();
}

void MainFrame::onReverbTime(double time)
{
  ui->reverbTimeDial->setValue(time);
}

void MainFrame::onReverbMix(double mix)
{
  ui->reverbMixDial->setValue(mix);
}
//------------------------------------------------------------------------------------------

// delay
// ui => kpa
void MainFrame::on_delayButton_clicked(QToasterButton& bt, bool longClick)
{
  if(longClick)
  {
    //toggleOperationMode(StompEdit, &bt);
  }
  else
  {
    mDelay.applyOnOffCutsTail(bt.toggleOnOff());
  }
  update();
}

void MainFrame::on_delayFeedbackDial_valueChanged(double arg1)
{
  mDelay.applyFeedback(arg1);
}

void MainFrame::on_delayMixDial_valueChanged(double arg1)
{
    mDelay.applyMix(arg1);
}

// kpa => ui
void MainFrame::onDelayOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->delayButton->setState(state);
  update();
}

void MainFrame::onDelayFeedback(double feedback)
{
  ui->delayFeedbackDial->setValue(feedback);
  update();
}

void MainFrame::onDelayMix(double mix)
{
  ui->delayMixDial->setValue(mix);
  update();
}
//------------------------------------------------------------------------------------------


// amp
// ui => kpa
void MainFrame::on_amplifierButton_clicked(QToasterButton& bt, bool longClick)
{
  //if(longClick)
  //  toggleOperationMode(AmpEdit, &bt);
  //else
    mAmp.applyOnOff(bt.toggleOnOff());
  update();
}

void MainFrame::on_gainDial_valueChanged(double gain)
{
  mAmp.applyGain(gain);
}

// kpa => ui
void MainFrame::onAmpOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->amplifierButton->setState(state);
  update();
}

void MainFrame::onAmpGain(double val)
{
  ui->gainDial->setValue(val);
  update();
}
//------------------------------------------------------------------------------------------

// eq
// ui => kpa
void MainFrame::on_eqButton_clicked(QToasterButton& bt, bool longClick)
{
  //if(longClick)
  //  toggleOperationMode(EQEdit, &bt);
  //else
    mEq.applyOnOff(bt.toggleOnOff());
  update();
}

// kpa => ui
void MainFrame::onEqOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->eqButton->setState(state);
  update();
}
//------------------------------------------------------------------------------------------

// cab
// ui => kpa
void MainFrame::on_cabinetButton_clicked(QToasterButton& bt, bool longClick)
{
  //if(longClick)
    //toggleOperationMode(CabEdit, &bt);
  //else
    mCab.applyOnOff(bt.toggleOnOff());
  update();
}

// kpa => ui
void MainFrame::onCabOnOff(bool onOff)
{
  QToasterButton::State state = onOff ? QToasterButton::On : QToasterButton::Off;
  ui->cabinetButton->setState(state);
  update();
}
//------------------------------------------------------------------------------------------

// rig
// ui => kpa
void MainFrame::on_volumeDial_valueChanged(double physVal)
{
  mRig.applyVolume(physVal);
}

void MainFrame::on_stompsButton_clicked(QToasterButton& bt, bool longClick)
{
  mRig.applyStompsEnable(bt.toggleOnOff());
  update();
}

void MainFrame::on_stackButton_clicked(QToasterButton& bt, bool longClick)
{
  mRig.applyStackEnable(bt.toggleOnOff());
  update();
}

void MainFrame::on_effectsButton_clicked(QToasterButton& bt, bool longClick)
{
  mRig.applyEffectsEnable(bt.toggleOnOff());
  update();
}

// kpa => ui
void MainFrame::onRigVolume(double volume)
{
  ui->volumeDial->setValue(volume);
  update();
}

void MainFrame::onRigStompsEnable(bool stompsEnable)
{
  QToasterButton::State state = stompsEnable ? QToasterButton::On : QToasterButton::Off;
  ui->stompsButton->setState(state);
  update();
}

void MainFrame::onRigStackEnable(bool stackEnable)
{
  QToasterButton::State state = stackEnable ? QToasterButton::On : QToasterButton::Off;
  ui->stackButton->setState(state);
  update();
}

void MainFrame::onRigEffectsEnable(bool effectsEnable)
{
  QToasterButton::State state = effectsEnable ? QToasterButton::On : QToasterButton::Off;
  ui->effectsButton->setState(state);
  update();
}
//------------------------------------------------------------------------------------------

// global
// ui => kpa
void MainFrame::on_chickenHeadDial_valueChanged(const QChickenHeadDial::State& state)
{
  mGlobal.applyOperationMode((Global::OperationMode) state);
}

void MainFrame::on_monitorVolumeDial_valueChanged(double volume)
{
  mGlobal.applyMonitorOutputVolume(volume);
}

void MainFrame::on_headphoneVolumeDial_valueChanged(double volume)
{
  mGlobal.applyHeadphoneOutputVolume(volume);
}

// kpa => ui
void MainFrame::onGlobalOperationMode(unsigned short opMode)
{
  ui->chickenHeadDial->setState((QChickenHeadDial::State)opMode);
  if(mOperationMode != StompEdit)
    ui->modeFrames->setCurrentIndex(opMode-1);
  update();
}

void MainFrame::onGlobalMainVolume(double volume)
{
  update();
}

void MainFrame::onGlobalHeadphoneVolume(double volume)
{
  ui->headphoneVolumeDial->setValue(volume);
  update();
}

void MainFrame::onGlobalMonitorVolume(double volume)
{
  ui->monitorVolumeDial->setValue(volume);
  update();
}

void MainFrame::onGlobalDirectVolume(double volume)
{
  update();
}
//------------------------------------------------------------------------------------------

// input
// ui => kpa
void MainFrame::on_noiseGateDial_valueChanged(double noiseGate)
{
  mInput.applyNoiseGate(noiseGate);
}

void MainFrame::on_distortionSenseDial_valueChanged(double distortionSense)
{
  mInput.applyDistortionSense(distortionSense);
}

void MainFrame::on_cleanSenseDial_valueChanged(double cleanSense)
{
  mInput.applyCleanSense(cleanSense);
}

// kpa => ui
void MainFrame::onInputNoiseGate(double noiseGate)
{
  ui->noiseGateDial->setValue(noiseGate);
  update();
}

void MainFrame::onInputDistortionSense(double distortionSense)
{
  ui->distortionSenseDial->setValue(distortionSense);
  update();
}

void MainFrame::onInputCleanSense(double cleanSense)
{
  ui->cleanSenseDial->setValue(cleanSense);
  update();
}
//------------------------------------------------------------------------------------------

// profile
// ui => kpa
void MainFrame::on_rigPrevButton_clicked(QToasterButton &bt, bool longClick)
{
  if(bt.state() == QToasterButton::On)
  {
    mProfile.applyRigPrev();
    requestValues(); // todo: request just the required values
  }
}

void MainFrame::on_rigNextButton_clicked(QToasterButton &bt, bool longClick)
{
  if(bt.state() == QToasterButton::On)
  {
    mProfile.applyRigNext();
    requestValues(); // todo: request just the required values
  }
}
// kpa => ui
//------------------------------------------------------------------------------------------

// utility methods
void MainFrame::handleStompButtonClick(Stomp& stomp, QToasterButton& stompBt, bool longClick)
{
  if(longClick)
  {
    toggleOperationMode(stomp, StompEdit, &stompBt);
  }
  else
  {
    stomp.applyOnOff(stompBt.toggleOnOff());
    stomp.requestOnOff();
  }
  update();
}

void MainFrame::toggleOperationMode(Stomp& stomp, OperationMode opMode, QToasterButton* bt)
{
  if(bt != NULL)
  {
    if(mEditModeButton != NULL && bt != mEditModeButton)
      mEditModeButton->resetToOnOffState();

    if(bt->state() == QToasterButton::Blinking)
    {
      bt->resetToOnOffState();
      mEditModeButton = NULL;
      ui->modeFrames->setCurrentIndex(1); // todo
      ui->stompEditor->deactivate();
      mOperationMode = mPreviousOperationMode;
    }
    else
    {
      bt->setState(QToasterButton::Blinking);
      mEditModeButton = bt;
      ui->modeFrames->setCurrentIndex(4);
      ui->stompEditor->activate(stomp.getInstance());
      mOperationMode = opMode;
    }
  }
  else if(mEditModeButton != NULL)
  {
    mEditModeButton->resetToOnOffState();
    mEditModeButton = NULL;
  }
}
//------------------------------------------------------------------------------------------

